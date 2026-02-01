#include <xc.h>
#include <string.h>
#include "program.h"
#include "app.h"
#include "timers.h"
#include "mdb_core.h"
#include "mdb_status.h"
#include "mdb_link.h"
#include "hal_uart.h"
#include "saldo.h"
#include "dispatcher.h"
#include "ui.h"
#include "checksum.h"

#define MDB_TIMEOUT_RESET 5
#define MDB_TIMEOUT_ENABLE 15
#define MDB_TIMEOUT_POLL 10
#define MDB_TIMEOUT_SETUP 40
#define MDB_TIMEOUT_TUBE 70
#define MDB_TIMEOUT_IDENT 70
#define MDB_TIMEOUT_DIAG 80

#define MDB_DIAG_STATUS_CMD 0x05
#define MDB_DIAG_DATA_LEN 16
#define MDB_DIAG_TOTAL_LEN (MDB_DIAG_DATA_LEN + 1) // + checksum

typedef struct
{
    uint16_t value;
    uint8_t HasValue;
} RefundValue_t;

static void TransitionTo(MDB_Link_State_t next, uint16_t delay_ms);
static void send_command(uint8_t command, uint8_t subCommand);

static RefundValue_t RefundValue = {0, 0};


TimerNB_t NB_ResetTimeOut;
TimerNB_t NB_JustResetTimeout;
TimerNB_t NB_SetupTimeOut;
TimerNB_t NB_EXPIDTimeOut;
TimerNB_t NB_EXPFEATURETimeOut;
TimerNB_t NB_EXP_DIAG_TimeOut;
TimerNB_t NB_TubeStatusTimeOut;
TimerNB_t NB_EnableCoinsTimeOut;
TimerNB_t NB_PollTimeOut;
TimerNB_t mdbWaitTimer;


static uint8_t is_coinco;
static MDB_Log_t mdb_log;

static uint8_t polls_buenos;

static CoinChanger_Info_t coin_changer_info = {0, 0, 0, 0,
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0};

static Tube_Status_t tube_status = {0,
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

static MDB_Link_State_t current_state = ST_MDB_RESET; // CurrentState
static MDB_Link_State_t next_state; // NextState

static uint8_t StatusFlag = 0;

MDB_Link_State_t MDB_Link_GetState(void) {
    return next_state;
}


static void log_tx(uint8_t cmd, uint8_t sub, uint8_t len) {
    memset(&mdb_log, 0, sizeof (mdb_log));
    if (len > 2)
        len = 2;
    mdb_log.Tx[0] = cmd;
    mdb_log.Tx[1] = sub;
    mdb_log.Tx_len = len;
}


static void log_rx(const uint8_t *dta, uint8_t len) {
    if (len > MDB_LOG_MAX)
        len = MDB_LOG_MAX;
    for (uint8_t i = 0; i < len; i++)
        mdb_log.Rx[i] = dta[i];
    mdb_log.Rx_len = len;
    mdb_log.Valid = 1;

    UI_Show_MDB_Rx_Line4(mdb_log.Tx, mdb_log.Rx, len);
}

static void send_ACK(void) {
    hal_UART_SendACK();
}

static void send_command_refund(uint16_t value) {
    if (value >= 1) {
        const uint8_t monedas = (uint8_t) (value / coin_changer_info.CoinScalingFactor);
        uint8_t cmd[4] = {0x0F, 0x02, monedas, 0};
        cmd[3] = CalculateChecksum(cmd, 4);
        hal_UART_Write_Cmd(cmd, 4);
    }
}

static void send_command(uint8_t command, uint8_t subCommand) {
    switch (command) {
        case MDB_CMD_RESET_08:
        {
            const uint8_t cmd[] = {0x08, 0x08};
            hal_UART_Write_Cmd(cmd, 2);
        }
            break;
            
        case MDB_CMD_SETUP_09:
        { // Request for changer setup information
            const uint8_t cmd[] = {0x09, 0x09};
            hal_UART_Write_Cmd(cmd, 2);
        }
            break;
            
        case MDB_CMD_TUBE_STATUS_0A:
        { // Request for changer tube status
            const uint8_t cmd[] = {0x0A, 0x0A};
            hal_UART_Write_Cmd(cmd, 2);
        }
            break;
            
        case MDB_CMD_POLL_0B:
        {
            const uint8_t cmd[] = {0x0B, 0x0B};
            hal_UART_Write_Cmd(cmd, 2);
        }
            break;
            
        case MDB_CMD_COIN_TYPE_0C:
        {
            if (subCommand == 0x00) {
                const uint8_t cmd[] = {0x0C, 0x00, 0x00, 0x00, 0x00, 0x0C};
                hal_UART_Write_Cmd(cmd, 6);
            }
            else {
                const uint8_t cmd[] = {0x0C, 0xFF, 0xFF, 0xFF, 0xFF, 0x08};
                hal_UART_Write_Cmd(cmd, 6);
            }
        }
            break;
            
        case MDB_CMD_EXPANSION_0F:
        {
            switch (subCommand) {
                case 0x00:
                {
                    const uint8_t cmd[] = {0x0F, 0x00, 0x0F};
                    hal_UART_Write_Cmd(cmd, 3);
                }
                    break;
                case 0x01:
                {
                    const uint8_t cmd[] = {0x0F, 0x01, 0x0C, 0x00, 0x00, 0x00, 0x1C};
                    hal_UART_Write_Cmd(cmd, 7);
                }
                    break;
                case 0x05: // Send Current Diagnostic Status
                {
                    const uint8_t cmd[] = {0x0F, 0x05, 0x14};
                    hal_UART_Write_Cmd(cmd, 3);
                }
                    break;
            }
        }
            break;
    }

    uint8_t lenLog = (command == MDB_CMD_COIN_TYPE_0C) || (command == MDB_CMD_EXPANSION_0F) ? 2 : 1;
    log_tx(command, subCommand, lenLog);
}


void MDB_Link_Dispatch(MDB_Event_t evt, uint16_t value) {

    switch (current_state) {
        case ST_MDB_POLL:
        case ST_MDB_POLL_WAIT:
        case ST_MDB_WAIT:
            if (evt == EVT_MDB_ESCROW_REQUEST) {
                if (value > 1) {
                    RefundValue.value = value;
                    RefundValue.HasValue = 1;
                }
            }
            if (evt == EVT_MDB_DIAG_REQUEST) {
                // Solo si el monedero soporta expansión
                if (coin_changer_info.CoinChangerFeatureLevel >= 3) {
                    StatusFlag = 1;
                }
            }
            else {
                StatusFlag = 0;
            }

            break;
        default:
            break;
    }
}


void MDB_Link_Init(void) {
    send_command(MDB_CMD_RESET_08, 0);
    TransitionTo(ST_MDB_RESET, 1000);
}


static MDB_Event_t parse_poll(const uint8_t *buf, uint8_t len) {
    /* ---------------- ACK ---------------- */
    if (len == 1 && buf[0] == MDB_MSG_ACK)
        return EVT_MDB_ACK;

    /* ---------------- COIN ---------------- */
    if (len == 3 && MDB_IS_COIN(buf[0])) {
        if (((buf[0] + buf[1]) & 0xFF) == buf[2])
            return EVT_MDB_COIN_VALID;
        else
            return EVT_MDB_COIN_INVALID;
    }

    /* ---------------- STATUS ---------------- */
    if ((len & 1) == 0 && !MDB_IS_COIN(buf[0])) {
        uint8_t i;

        /* validar pares */
        for (i = 0; i < len; i += 2) {
            if (buf[i] != buf[i + 1])
                return EVT_MDB_NONE;
        }

        /* interpretar cada status */
        for (i = 0; i < len; i += 2) {
            UI_MDB_MapStatus(buf[i]);
        }

        return EVT_MDB_STATUS_CODE;
    }

    return EVT_MDB_NONE;
}


static void TransitionTo(MDB_Link_State_t next, uint16_t delay_ms) {
    current_state = ST_MDB_WAIT;
    next_state = next;
    TimerNB_Start(&mdbWaitTimer, delay_ms);
}


void MDB_Link_Task_Command(void) // Enviar comando
{
    switch (current_state) {

        case ST_MDB_RESET: // 0X08   Timeout: 200-500ms    recomendado 50ms
            polls_buenos = 0;
            Dispatcher_Post(SRC_MDB, EVT_MDB_CHANGER_RESET, 0);
            send_command(MDB_CMD_RESET_08, 0);            
            TimerNB_Start(&NB_ResetTimeOut, MDB_TIMEOUT_RESET);
            TransitionTo(ST_MDB_RESET_WAIT, 5);            
            break;

        case ST_MDB_JUST_RESET: // 0X0B .
            send_command(MDB_CMD_POLL_0B, 0);
            TimerNB_Start(&NB_JustResetTimeout, 5);
            TransitionTo(ST_MDB_JUST_RESET_WAIT, 5);
            break;

        case ST_MDB_SETUP:
            // 0x09 // Timeout  30-50ms    recomendado 50ms
            send_command(MDB_CMD_SETUP_09, 0);            
            TimerNB_Start(&NB_SetupTimeOut, MDB_TIMEOUT_SETUP);
            TransitionTo(ST_MDB_SETUP_WAIT, 60);
            break;

        case ST_MDB_EXP_ID: // 0F 00 Expansion Identification 0F 00h (Level 03+ only)
            if (coin_changer_info.CoinChangerFeatureLevel >= 3) {
                send_command(MDB_CMD_EXPANSION_0F, 0x00);
                TimerNB_Start(&NB_EXPIDTimeOut, MDB_TIMEOUT_IDENT);
                TransitionTo(ST_MDB_EXP_ID_WAIT, 100); // 100 ms, el comando es lento
            }
            else {
                TransitionTo(ST_MDB_TUBE_STATUS, 200);
            }
            break;

        case ST_MDB_EXP_FEATURE:
            if (coin_changer_info.CoinChangerFeatureLevel >= 3) {
                send_command(MDB_CMD_EXPANSION_0F, 0x01);
                TimerNB_Start(&NB_EXPFEATURETimeOut, 5);
                TransitionTo(ST_MDB_EXP_FEATURE_WAIT, 5);
            }
            else
                TransitionTo(ST_MDB_TUBE_STATUS, 200);
            break;

        case ST_MDB_EXP_DIAG_STATUS:
            if (coin_changer_info.CoinChangerFeatureLevel >= 3) {
                send_command(MDB_CMD_EXPANSION_0F, MDB_DIAG_STATUS_CMD);
                TimerNB_Start(&NB_EXP_DIAG_TimeOut, MDB_TIMEOUT_DIAG);
                TransitionTo(ST_MDB_EXP_DIAG_STATUS_WAIT, MDB_TIMEOUT_DIAG);
            }
            else
                TransitionTo(ST_MDB_TUBE_STATUS, 200);
            break;

        case ST_MDB_TUBE_STATUS:
            send_command(MDB_CMD_TUBE_STATUS_0A, 0);
            TimerNB_Start(&NB_TubeStatusTimeOut, MDB_TIMEOUT_TUBE);
            TransitionTo(ST_MDB_TUBE_STATUS_WAIT, 50); // para recepcion completa            
            break;

        case ST_MDB_ENABLE_COINS:            
            send_command(MDB_CMD_COIN_TYPE_0C, 0x01);
            TimerNB_Start(&NB_EnableCoinsTimeOut, 15);
            TransitionTo(ST_MDB_ENABLE_COINS_WAIT, 15);
            break;

         case ST_MDB_DISBLE_COINS:            
            send_command(MDB_CMD_COIN_TYPE_0C, 0x00);
            TimerNB_Start(&NB_EnableCoinsTimeOut, 5);
            TransitionTo(ST_MDB_DISABLE_COINS_WAIT, 5);
            break;

        case ST_MDB_POLL:
            send_command(MDB_CMD_POLL_0B, 0x00);            
            TimerNB_Start(&NB_PollTimeOut, MDB_TIMEOUT_POLL); // Timeout 10ms
            TransitionTo(ST_MDB_POLL_WAIT, 10); // tiempo de respuesta
            break;

        case ST_MDB_REFUND:
            if (RefundValue.HasValue && RefundValue.value > 1) {
                RefundValue.HasValue = 0;
                send_command_refund(RefundValue.value);
            }
            TransitionTo(ST_MDB_POLL, 500);
            break;

        case ST_MDB_EXP_DIAGNOSTIC:
            if (coin_changer_info.CoinChangerFeatureLevel >= 3) {
                send_command(MDB_CMD_EXPANSION_0F, MDB_DIAG_STATUS_CMD);
                TimerNB_Start(&NB_EXP_DIAG_TimeOut, MDB_TIMEOUT_DIAG);
                TransitionTo(ST_MDB_EXP_DIAGNOSTIC_WAIT, MDB_TIMEOUT_DIAG);
            }
            else 
                TransitionTo(ST_MDB_POLL, 200);
            break;
            
        default:
            break;
    }
}


void MDB_Link_Task_Response(void) // Enviar comando
{
    mdb_frame_t *f;

    switch (current_state) {
        
            // Respuesta esperada: El periférico responde con un ACK (Acknowledge) 
            // y entra en una fase de autodiagnóstico.
        case ST_MDB_RESET_WAIT: // ESPERO ACK , despues del RESET 0x08
            if (MDB_Core_FrameAvailable()) {
                f = MDB_Core_GetFrame();
                log_rx(f->rxdata, f->len);
                if (f->len == 1 && f->rxdata[0] == MDB_MSG_ACK) {
                    send_ACK();
                    TransitionTo(ST_MDB_JUST_RESET, 200);
                }
                MDB_Core_ReleaseFrame();
            }
            else if (TimerNB_Expired(&NB_ResetTimeOut)) {
                TransitionTo(ST_MDB_RESET, 200);
            }
            break;

        case ST_MDB_JUST_RESET_WAIT: // ESPERO ACK
            if (MDB_Core_FrameAvailable()) {
                f = MDB_Core_GetFrame();
                MDB_Status_Clear();
                log_rx(f->rxdata, f->len);
                if (f->len == 1 && f->rxdata[0] == MDB_MSG_ACK) {
                    send_ACK();
                    TransitionTo(ST_MDB_SETUP, 200);
                }
                else if ((f->len & 1) == 0) {
                    send_ACK(); //TransitionTo(ST_MDB_SETUP, 200);
                    TransitionTo(ST_MDB_JUST_RESET, 200);
                }
                MDB_Core_ReleaseFrame();
            }
            else if (TimerNB_Expired(&NB_JustResetTimeout)) {
                TransitionTo(ST_MDB_JUST_RESET, 200);
            }
            break;

            // SETUP 0x09.  23 Bytes + Checsum = 24 bytes    (17+1) ?    
        case ST_MDB_SETUP_WAIT:
            if (MDB_Core_FrameAvailable()) {
                f = MDB_Core_GetFrame();
                log_rx(f->rxdata, f->len);
                if (f->len == 24 && ValidateChecksum(f->rxdata, f->len)) {
                    uint16_t temp;
                    uint8_t k;
                    send_ACK();
                    // Z1 -      Changer Feature Level - 1 byte
                    // Level: El nivel del protocolo (Level 1, 2 o el actual Level 3/4).
                    coin_changer_info.CoinChangerFeatureLevel = f->rxdata[0];
                    // Z2 - Z3   Country / Currency Code - 2 bytes
                    coin_changer_info.CountryOrCurrencyCode =
                            ((uint16_t) f->rxdata[1] << 8) | f->rxdata[2];
                    // Z4 -      Coin Scaling Factor - 1 byte
                    // Scaling Factor: Define cuántos decimales tiene la moneda 
                    // (ej. si el factor es 100, el valor "5" representa $0.05).
                    coin_changer_info.CoinScalingFactor = f->rxdata[3];

                    // Z5 -      Decimal Places - 1 byte
                    // Decimal Places: Cuántos decimales mostrar en la pantalla.
                    coin_changer_info.DecimalPlaces = f->rxdata[4];

                    // Z6 - Z7   Coin Type Routing - 2 bytes
                    // Ruta de las monedas en los tubos
                    temp = ((uint16_t) f->rxdata[5] << 8) | f->rxdata[6];
                    for (k = 0; k < 16; k++)
                        coin_changer_info.CoinsRouteable[k] = (temp >> k) & 0x01;
                    // Bit_convert_bit(temp, k);

                    // Cantidad de monedas validas    (primeros 8 bytes + checksum)
                    // Z8 - Z23  Coin Type Credit - 16 bytes
                    coin_changer_info.NumCoinTypes = received_data - 8;
                    if (coin_changer_info.NumCoinTypes > 16)
                        coin_changer_info.NumCoinTypes = 16;

                    for (k = 0; k < coin_changer_info.NumCoinTypes; k++)
                        coin_changer_info.CoinTypeCredit[k] = f->rxdata[7 + k];

                    // Limpia los no usados
                    for (k = coin_changer_info.NumCoinTypes; k < 16; k++)
                        coin_changer_info.CoinTypeCredit[k] = 0;

                    TransitionTo(ST_MDB_EXP_ID, 200);
                }
                else { // Invalid checksum, request again
                    TransitionTo(ST_MDB_SETUP, 200);
                }
                MDB_Core_ReleaseFrame();
            }
            else if (TimerNB_Expired(&NB_SetupTimeOut)) {
                log_rx(f->rxdata, f->len);
                TransitionTo(ST_MDB_SETUP, 200);
            }
            break;


        case ST_MDB_EXP_ID_WAIT: // 33 bytes + 1 checksum = 34
            if (MDB_Core_FrameAvailable()) {
                f = MDB_Core_GetFrame();
                log_rx(f->rxdata, f->len);
                if (f->len == 34) {
                    is_coinco = (f->rxdata[0] == 'C' && f->rxdata[1] == 'A' && f->rxdata[2] == 'I');
                    send_ACK();
                    TransitionTo(ST_MDB_EXP_FEATURE, 200);
                }
                MDB_Core_ReleaseFrame();
            }
            else if (TimerNB_Expired(&NB_EXPIDTimeOut)) {
                TransitionTo(ST_MDB_EXP_ID, 200);
            }
            break;

        case ST_MDB_EXP_FEATURE_WAIT: // 0x0F 0x01  - esperar ACK
            if (MDB_Core_FrameAvailable()) {
                f = MDB_Core_GetFrame();
                if ((f->len == 1) && (f->rxdata[0] == MDB_MSG_ACK)) {
                    log_rx(f->rxdata, f->len);
                    TransitionTo(ST_MDB_EXP_DIAG_STATUS, 200);
                }
                MDB_Core_ReleaseFrame();
            }
            else if (TimerNB_Expired(&NB_EXPFEATURETimeOut)) {
                TransitionTo(ST_MDB_EXP_FEATURE, 200);
            }
            break;

        case ST_MDB_EXP_DIAG_STATUS_WAIT:
            if (MDB_Core_FrameAvailable()) {
                f = MDB_Core_GetFrame();
                log_rx(f->rxdata, f->len);
                if (f->len >= 2) {
                    send_ACK();
                    TransitionTo(ST_MDB_TUBE_STATUS, 500);
                }
                MDB_Core_ReleaseFrame();
            }
            else if (TimerNB_Expired(&NB_EXP_DIAG_TimeOut)) {
                TransitionTo(ST_MDB_EXP_DIAG_STATUS, 200);
            }
            break;


            /*
                Z1-Z2  Tube Full Status
                Z3-Z18 Tube Status - 16 bytes
             */
        case ST_MDB_TUBE_STATUS_WAIT:
        {
            //uint8_t espero_bytes;

            // num_tubes = CoinChangerInfo.NumCoinTypes;
            // full status (2bytes) + tubes (1..16) + checksum (1byte)
            // espero_bytes = CoinChangerInfo.NumCoinTypes + 2 + 1;
            log_rx(f->rxdata, f->len);
            if (MDB_Core_FrameAvailable()) {
                f = MDB_Core_GetFrame();
                log_rx(f->rxdata, f->len);

                if (ValidateChecksum(f->rxdata, f->len)) {
                    send_ACK();



                    // 1. Los primeros 2 bytes son el Full Status (MSB first)
                    tube_status.Full_Status = ((uint16_t) f->rxdata[0] << 8) + f->rxdata[1];

                    // 2. Los siguientes bytes son el conteo de monedas por tubo
                    // MDB define hasta 16 tubos, pero len nos dice cu?ntos envi? realmente el monedero
                    // menos los 2 primeros bytes, menos el checksum
                    tube_status.Total_Tubes = f->len - 2 - 1;

                    for (uint8_t i = 0; i < coin_changer_info.NumCoinTypes; i++) {
                        tube_status.Status[i] = f->rxdata[i + 2];
                        // ByteToStr(tube_status.status[i], buff);
                    }

                    // Limpia tubos no usados
                    for (uint8_t i = coin_changer_info.NumCoinTypes; i < 16; i++) {
                        tube_status.Status[i] = 0;
                    }

                    TransitionTo(ST_MDB_ENABLE_COINS, 200);
                }
                else {
                    // Invalid Checksum
                    TransitionTo(ST_MDB_TUBE_STATUS, 200);
                }

                MDB_Core_ReleaseFrame();
            }
            else if (TimerNB_Expired(&NB_TubeStatusTimeOut)) {
                TransitionTo(ST_MDB_TUBE_STATUS, 200);
            }
        }
            break;

        case ST_MDB_ENABLE_COINS_WAIT:
            if (MDB_Core_FrameAvailable()) {
                f = MDB_Core_GetFrame();
                log_rx(f->rxdata, f->len);
                if (f->len == 1 && f->rxdata[0] == MDB_MSG_ACK) {
                    send_ACK();
                    polls_buenos = 0;
                    StatusFlag = 0;
                    TransitionTo(ST_MDB_POLL, 200);
                    Dispatcher_Post(SRC_MDB, EVT_MDB_CHANGER_READY, 0);
                }
                MDB_Core_ReleaseFrame();
            }
            else if (TimerNB_Expired(&NB_EnableCoinsTimeOut)) {
                TransitionTo(ST_MDB_ENABLE_COINS, 200);
            }
            break;

        case ST_MDB_DISABLE_COINS_WAIT:
            if (MDB_Core_FrameAvailable()) {
                f = MDB_Core_GetFrame();
                log_rx(f->rxdata, f->len);
                if (f->len == 1 && f->rxdata[0] == MDB_MSG_ACK) {
                    send_ACK();
                    TransitionTo(ST_MDB_POLL, 200);
                }
                MDB_Core_ReleaseFrame();
            }
            else if (TimerNB_Expired(&NB_EnableCoinsTimeOut)) {
                TransitionTo(ST_MDB_ENABLE_COINS, 200);
            }
            break;



            //--------------------------------------------------------------------
            // El VMC envía un comando POLL constantemente (intervalos de entre 25ms y 200ms).
            // Sondeo MDB para saver que actividad realiza el monedero
            // Al enviar 0x0B  y no tiene nada que reportar responde con 0x00 ACK
            // Timeout: Respuesta normal 5?10 ms -- M?ximo seguro  15 ms , recomendado 10
            // Respuestas ACK (0x00): "Todo bien, no hay novedades".
            // Changer Reset: Indica que el monedero se reinició inesperadamente 
            // (el VMC debe volver al estado 1).
            // Coin Deposited: Indica que el usuario insertó dinero. 
            // El VMC suma esto a su contador interno de crédito.

            // Si no tiene nada que enviar al maestro responderá con 0x00 ACK
            // Si no recibe lo que esperaba responderá con 0xFF  NAK.
            // Z1 - Z16    Changer Activity - 16 bytes
        case ST_MDB_POLL_WAIT:
        {
            if (MDB_Core_FrameAvailable()) {
                f = MDB_Core_GetFrame();
                MDB_Status_Clear();
                MDB_Event_t evt = parse_poll(f->rxdata, f->len);
                // LATAbits.LA5 = ~LATAbits.LA5;
                switch (evt) {
                    case EVT_MDB_ACK: // recibi un byte y es ACK.
                        // Más claro que POLL_ACK (indica que hay datos esperando)

                        if (RefundValue.HasValue && RefundValue.value) {
                            send_command_refund(RefundValue.value);
                            RefundValue.HasValue = RefundValue.value = 0;
                            TransitionTo(ST_MDB_POLL, 500);
                        }
                        else {
                            TransitionTo(ST_MDB_POLL, 200);
                        }

                        if (StatusFlag) {
                            StatusFlag = 0;
                            TransitionTo(ST_MDB_EXP_DIAGNOSTIC, 200);
                        }

                        //                        if (polls_buenos != 0xff) {
                        //                            if (polls_buenos < 10)
                        //                                polls_buenos++;
                        //                            else {
                        //                                polls_buenos = 0xff;
                        //                                FSM_Global_Dispatch(EVT_GLOBAL_SERVICE_RESET);
                        //                            }
                        //                        }
                        // FSM_Global_Dispatch(EVT_GLOBAL_SERVICE_RESET);
                        break;

                    case EVT_MDB_COIN_VALID:
                        // asumir que es un depesito de moneda (formato 2 bytes + checksum)
                        // --- Parsing de Depesito de Moneda (4xH - 7xH) ---
                        // El bit 7 del primer byte indica si es un evento (0) o un depesito/payout (1)
                        // valido checksum -> validar moneda  ejemplo --->   42 15 56
                        if (((f->rxdata[0] + f->rxdata[1]) & 0xFF) == f->rxdata[2]) {
                            send_ACK();

                            // uint8_t event_byte_1 = f->rxdata[0];
                            // uint8_t CoinTypeDeposited = event_byte_1 & 0x0F; // tipo de moneda depositado 
                            uint8_t CoinTypeDeposited = f->rxdata[0] & 0x0F; // tipo de moneda depositado 

                            // Calculamos el valor escalado para el comando MDB
                            uint16_t CoinValue =
                                    coin_changer_info.CoinTypeCredit[CoinTypeDeposited] *
                                    coin_changer_info.CoinScalingFactor;

                            Dispatcher_Post(SRC_MDB, EVT_MDB_COIN_VALID, CoinValue);

                            TransitionTo(ST_MDB_POLL, 200);
                        }
                        else { // invalid checksum
                            send_ACK();
                            TransitionTo(ST_MDB_POLL, 200);
                        }
                        log_rx(f->rxdata, f->len);
                        break;

                    case EVT_MDB_STATUS_CODE:
                        send_ACK();
                        // El usuario presionó la palanca de devolución.
                        if (mdb_status.escrow_req) { // 0x01
                            uint16_t credit = Saldo_Get();
                            MDB_Link_Dispatch(EVT_MDB_ESCROW_REQUEST, credit);
                            TransitionTo(ST_MDB_POLL, 200);
                        }
                        if (mdb_status.busy) { // 0x02 
                            // TransitionTo(ST_MDB_REFUND, 200);
                        }
                        if (mdb_status.no_credit) // 0x03
                        {
                        }
                        // El monedero se reinició. Debes reconfigurarlo.
                        // Importante: re-inicializar el monedero
                        if (mdb_status.reset) {
                            send_ACK();
                            TransitionTo(ST_MDB_RESET, 200);
                        }

                        // ERROR
                        // case 0x04: mdb_status.tube_sensor_err = 1;
                        // case 0x06: mdb_status.acceptor_removed = 1;
                        // case 0x07: mdb_status.tube_jam = 1;
                        // case 0x08: mdb_status.rom_error = 1;
                        // case 0x0C: mdb_status.coin_jam = 1;

                        // WARNING            
                        // case 0x05: mdb_status.double_coin = 1;
                        // case 0x09: mdb_status.routing_error = 1;
                        // case 0x0D: mdb_status.fraud = 1;

                        // case 0x0A: mdb_status.busy = 1;

                        MDB_Status_Clear();
                        TransitionTo(ST_MDB_POLL, 200);
                        break;

                        // Status de Error Mecanico

                    default:
                        log_rx(f->rxdata, f->len);
                        break;
                }


                //            } else if (f->len >= 2) {
                //                uint8_t j;
                //                MDB_SendACK();
                //                MDB_To_PC(f->rxdata, f->len);
                //                for (j = 0; j < received_data; j += 2) {
                //                    if (f->rxdata[j] == f->rxdata[j + 1]) {
                //                        //  MDB_ParsePoll_Status(f->rxdata, f->len);
                //                    }
                //                }
                //                MDB_GotoWait(MDB_RESET, 200);
                //            }
                MDB_Core_ReleaseFrame();
            }
            else if (TimerNB_Expired(&NB_PollTimeOut)) {
                TransitionTo(ST_MDB_POLL, 200);
            }
        }
            break;

        case ST_MDB_EXP_DIAGNOSTIC_WAIT:
            if (MDB_Core_FrameAvailable()) {
                f = MDB_Core_GetFrame();
                log_rx(f->rxdata, f->len);
                if (f->len >= 2) {
                    send_ACK();
                    TransitionTo(ST_MDB_POLL, 500);
                }
                MDB_Core_ReleaseFrame();
            }
            else if (TimerNB_Expired(&NB_EXP_DIAG_TimeOut)) {
                TransitionTo(ST_MDB_EXP_DIAG_STATUS, 200);
            }
            break;

        case ST_MDB_WAIT:
        {
            if (TimerNB_Expired(&mdbWaitTimer)) {
                current_state = next_state;
            }
        }
            break;

        case ST_MDB_ERROR:
            break;
            
        default:
            break;
    }
}



























/*
    else if ((received_data % 2) && (received_data <= 16))
    {
      MDB_SendACK();
      for (_i = 0; _i < received_data; _i += 2)
        {
            _b = Rx_data[_i];
            if (Rx_data[_i] == Rx_data[_i + 1])
            {
                // 2. Otros estados mediante Switch
                switch (_b) {
                    case 0x01: //Petici?n de Escrow: Se activ? la palanca de devoluci?n.
                        break;
                    case 0x02: // Pagador ocupado: El monedero est? dispensando cambio.
                        break;
                    case 0x03: // Sin cr?dito: Moneda validada pero no lleg? al ?rea de cr?dito.
                        break;
                    case 0x04: // Sensor de tubo defectuoso: Fallo en sensores de nivel.
                        break;
                    case 0x05: // Doble llegada: Dos monedas detectadas demasiado juntas.
                        break;
                    case 0x06: // Aceptador desenchufado: Se ha desconectado el cabezal.
                        break;
                    case 0x07: // Atasco en tubo: Moneda trabada durante el pago.
                        break;
                    case 0x08: // Error de ROM: Error interno de memoria (Checksum).
                        break;
                    case 0x09: // Error de ruta: La moneda no sigui? el camino previsto.
                        break;
                    case 0x0A: // Monedero ocupado: No puede responder comandos ahora.
                        break;
                    case 0x0B: // Reinicio: El monedero se ha reseteado (Reset).
                        break;
                    case 0x0C: // Atasco de moneda: Moneda trabada en la entrada.
                        break;
                    case 0x0D: // Extracci?n de moneda: Intento de fraude/pesca detectado.
                        break;
                }
            }
        }
      MDB_To_PC((uint8_t *)Rx_data, received_data);
      MDB_GotoWait(ESTADO_POLL, 200);
    }
    else if (TimerNB_Expired(&NB_PollTimeOut))
    {
      MDB_GotoWait(ESTADO_POLL, 200);
    }
  }
  break;
 */

/*switch (CoinRouting)
  {
  case 0x00:
    // Lcd_Out(4, 1, "Caja de Efectivo");
    SoftUart_PrintString("Caja de Efectivo");
    break;
  case 0x01:
    // Lcd_Out(4, 1, "Tubos");
    SoftUart_PrintString("Tubos");
    break;
  case 0x02:
    // Lcd_Out(4, 1, "SIN USO");
    SoftUart_PrintString("Tubos");
  break;
  case 0x03:
    // Lcd_Out(4, 1, "Moneda Rechazada");
    SoftUart_PrintString("Moneda Rechazada");
    break;
  }*/


// uint8_t MDB_ParsePoll_Status(const uint8_t *buf, uint8_t len) {
//    uint8_t byte1 = buf[0];
//    switch (byte1) {
//            // Status de Control / Monedero en operacion
//        case 0x01: // Evento: Solicitud de Escrow (devoluci?n)
//            // UART_Write(MDB_MSG_ACK);
//            //SoftUart_PrintString("Palanca de devoluci?n.");
//            //  Aqu? decidir si aceptar el vend o devolver la moneda
//            break;
//        case 0x02: // Evento: Dispensando cambio (Ocupado)
//            // No enviar comandos de payout hasta que cese este Estado
//            // UART_Write(MDB_MSG_ACK);
//            //SoftUart_PrintString("El monedero est? dispensando cambio.\r\n");
//            break;
//        case 0x03: // No Credit
//            //SoftUart_PrintString("Se insert? una moneda pero no se pudo validar.\r\n");
//            break;
//        case 0x0A: // Changer Error
//            //SoftUart_PrintString("Monedero ocupado: No puede responder comandos ahora.\r\n");
//            break;
//        case 0x0B: //  Evento: Just Reset (reci?n reiniciado)
//            // Importante: Marcar flag para re-inicializar el monedero
//            // mdb_status_reset_flag = 1;
//            //SoftUart_PrintString("El monedero se reinici?.");
//            break;
//
//            // Status de Error Mecanico
//        case 0x04: // Defective Tube Sensor
//            //SoftUart_PrintString("Sensor de tubo defectuoso: Fallo en sensores de nivel.\r\n");
//            break;
//        case 0x05: // Double Arrival
//            //SoftUart_PrintString("Dos monedas pasaron demasiado r?pido por el sensor.\r\n");
//            break;
//        case 0x07: // Tube Jam
//            //SoftUart_PrintString("Atasco en tubo: Moneda trabada durante el pago.\r\n");
//            break;
//        case 0x09: // Coin Routing Error
//            //SoftUart_PrintString("Error de ruta: La moneda no sigui? el camino previsto.\r\n");
//            break;
//        case 0x0C: // Coin Ship
//            //SoftUart_PrintString("Atasco de moneda: Moneda trabada en la entrada.\r\n");
//            break;
//
//            // Status de Hardware
//        case 0x06: // Acceptor Unplugged
//            //SoftUart_PrintString("Aceptador desenchufado: Se ha desconectado el cabezal.\r\n");
//            break;
//        case 0x08: // ROM Checksum Error     >>>>>> requiere restart
//            //SoftUart_PrintString("Error de ROM: Error interno de memoria (Checksum).\r\n");
//            break;
//        case 0x0D: // Payout Stopped
//            //SoftUart_PrintString("Extracci?n de moneda: Intento de fraude/pesca detectado.\r\n");
//            break;
//        case 0x0E: // Rejecter Code
//            //SoftUart_PrintString("Error en modulo rechazo\r\n");
//            break;
//        default:
//            // C?digo desconocido o reservado
//            break;
//    }
//    return byte1;
//}




// Es un depésito o payout (Byte 1: Ruta | Byte 2: Cantidad)
// Coin deposited
// 01yyxxxx zzzzzzzz -> 01 yy = coin routing    0x42  01-00-0010
// 00 cash box,  01 tubes, 10 not used,  11 rejected
// Extraer el estado de rutado (bits 4-6)
// 00-cash box, 01-tubes, 10-not used,  11 rejected
// Extraer el tipo de moneda (bits 0-3)
// coin_tube_inventory[coin_type] = coin_count;
// El segundo byte es la cantidad actual en el tubo
// event_byte_2


