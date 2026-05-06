#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "saldo.h"
#include "mdb_link.h"
#include "credit.h"
#include "vend.h"
#include "timers.h"
#include "dispatcher.h"
#include "datos_venta.h"

/* ================== Configuración ================== */

#define CREDIT_INACTIVITY_TIMEOUT_MS 30000UL

/* ================== Estados ================== */

typedef enum
{
    ST_CREDIT_EMPTY = 0, // Balance = 0; sin credito
    ST_CREDIT_ACTIVE // hay credito acumulado
} Credit_State_t;

/* ================== Variables internas ================== */

static Credit_State_t current_state = ST_CREDIT_EMPTY;
static uint32_t last_activity_ms;


// static void Saldo_Add(const uint16_t value);
// static void OnTimeOut(void);
// static void RequestRefund(void);
// static void TransitionTo(Credit_State_t next);


static uint8_t credit_amount;

/* ================== Utilidades internas ================== */

static void TransitionTo(Credit_State_t next) {
    if (current_state == next)
        return;

    current_state = next;

    switch (current_state) {
        case ST_CREDIT_EMPTY:
            Saldo_Clear();
            Dispatcher_Post(SRC_CREDIT, EVT_CREDIT_NONE, 0);
            break;

        case ST_CREDIT_ACTIVE:
            Dispatcher_Post(SRC_CREDIT, EVT_CREDIT_AVAILABLE, 0);
            break;
    }
}

static void TouchActivity(void) {
    last_activity_ms = Millis();
}

static void RequestRefund(void) {
    uint16_t credit = Saldo_Get();
    if (credit > 0) {
        MDB_Link_Dispatch(EVT_MDB_ESCROW_REQUEST, credit);
        Saldo_Clear();
    }
}

//static void Saldo_Add(const uint16_t value) {
//    last_activity_ms = Millis();
//    Saldo_Add(value); // Acumular creditodepositado.
//}

/* ================== API pública ================== */

void Credit_Init(void) {
    Saldo_Clear();
    current_state = ST_CREDIT_EMPTY;
}

void Credit_Dispatch(Credit_Event_t evt, uint16_t value) {

    switch (current_state) {

        case ST_CREDIT_EMPTY:
            if (evt == EVT_CREDIT_ACCEPTED && value > 0) {
                Saldo_Add(value); // Acumular el credito
                TouchActivity();
                TransitionTo(ST_CREDIT_ACTIVE);
            }
            break;

        case ST_CREDIT_ACTIVE:
            switch (evt) {
                case EVT_CREDIT_ACCEPTED:
                    if (value > 0) {
                        Saldo_Add(value);
                        TouchActivity();
                        Dispatcher_Post(SRC_CREDIT, EVT_CREDIT_UPDATED, Saldo_Get());
                    }
                    break;

                case EVT_CREDIT_CONSUME_PRICE_P1:
                case EVT_CREDIT_CONSUME_PRICE_P2:
                    Saldo_Deduct(value);
                    RequestRefund(); /* devuelve cambio si hay */
                    TransitionTo(ST_CREDIT_EMPTY);
                    break;

                case EVT_CREDIT_TIMEOUT:
                case EVT_CREDIT_RESET:
                    RequestRefund(); /* devuelve cambio si hay */
                    TransitionTo(ST_CREDIT_EMPTY);
                    break;

                default:
                    break;
            }
            break;
    }
}

void Credit_Task(void) {
    if (current_state == ST_CREDIT_ACTIVE) {        
        if ((Millis() - last_activity_ms) >= CREDIT_INACTIVITY_TIMEOUT_MS) {
            Credit_Dispatch(EVT_CREDIT_TIMEOUT, 0);
        }
    }
}

//---  Public API -- ===========================================================

const char* Credit_GetState(void) {
    switch (current_state) {
        case ST_CREDIT_EMPTY: return "E";
        case ST_CREDIT_ACTIVE: return "A";
        default: return "?";
    }
}

const uint8_t Credit_GetInactivity(void) {
    // 1. Verificación de estado
    if (current_state != ST_CREDIT_ACTIVE) {
        return 0;
    }

    // 2. Snapshot de la variable para evitar inconsistencias durante el cálculo
    uint32_t t_snap = Millis() - last_activity_ms;
    uint32_t t_max = CREDIT_INACTIVITY_TIMEOUT_MS; // Supongamos 30000

    // 3. Verificación de límite
    if (t_snap >= t_max) {
        return 0;
    }

    // 4. Cálculo de segundos restantes (30 -> 0)
    // Usamos (distancia + 999) / 1000 para que el "30" se mantenga 
    // hasta que realmente haya pasado el primer segundo.
    return (uint8_t) ((t_max - t_snap + 999) / 1000);
}









//static void AddCredit(const uint16_t param0) {
//    uint8_t event_byte_1 = frame[0];
//    if (!MDB_IS_COIN(event_byte_1))
//        return;
//    credit_last_activity_ms = Millis();
//    uint8_t coin_routing = (event_byte_1 >> 4) & 0x03;
//    uint8_t CoinTypeDeposited = event_byte_1 & 0x0F; // tipo de moneda depositado .
//    CoinRouting = coin_routing;
//    uint16_t CoinValue =
//            coin_changer_info.CoinTypeCredit[CoinTypeDeposited] *
//            coin_changer_info.CoinScalingFactor;
//    Credit_Add(CoinValue); // Acumular creditodepositado.
//}






