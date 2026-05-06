# 1 "sources/dispatcher.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 295 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include/language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "sources/dispatcher.c" 2
# 1 "Include/dispatcher.h" 1







# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdint.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/musl_xc8.h" 1 3
# 5 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdint.h" 2 3
# 26 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 1 3
# 133 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef unsigned __int24 uintptr_t;
# 148 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef __int24 intptr_t;
# 164 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef signed char int8_t;




typedef short int16_t;




typedef __int24 int24_t;




typedef long int32_t;





typedef long long int64_t;
# 194 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef long long intmax_t;





typedef unsigned char uint8_t;




typedef unsigned short uint16_t;




typedef __uint24 uint24_t;




typedef unsigned long uint32_t;





typedef unsigned long long uint64_t;
# 235 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef unsigned long long uintmax_t;
# 27 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdint.h" 2 3

typedef int8_t int_fast8_t;

typedef int64_t int_fast64_t;


typedef int8_t int_least8_t;
typedef int16_t int_least16_t;

typedef int24_t int_least24_t;
typedef int24_t int_fast24_t;

typedef int32_t int_least32_t;

typedef int64_t int_least64_t;


typedef uint8_t uint_fast8_t;

typedef uint64_t uint_fast64_t;


typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;

typedef uint24_t uint_least24_t;
typedef uint24_t uint_fast24_t;

typedef uint32_t uint_least32_t;

typedef uint64_t uint_least64_t;
# 148 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/stdint.h" 1 3
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 149 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdint.h" 2 3
# 9 "Include/dispatcher.h" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdbool.h" 1 3
# 10 "Include/dispatcher.h" 2


typedef enum {
    SRC_NONE = 0,
    SRC_MDB,
    SRC_CREDIT,
    SRC_VEND,
    SRC_UI,
    SRC_APP
} EventSource_t;


typedef struct {
    EventSource_t src;
    uint16_t evt;
    uint16_t param;
} DispatcherEvent_t;


void Dispatcher_Init(void);
_Bool Dispatcher_Post(EventSource_t src, uint16_t evt, uint16_t param);
void Dispatcher_Task(void);
# 2 "sources/dispatcher.c" 2
# 1 "Include/global.h" 1




# 1 "Include/events.h" 1





typedef enum {
    EVT_GLOBAL_INIT_DONE,
    EVT_GLOBAL_SYSTEM_READY,
    EVT_GLOBAL_CREDIT_AVAILABLE,
    EVT_GLOBAL_CREDIT_EMPTY,
    EVT_GLOBAL_SELECTION,
    EVT_GLOBAL_VEND_DONE,
    EVT_GLOBAL_ERROR,
    EVT_GLOBAL_SERVICE_RESET
} Global_Event_t;

typedef enum {
    EVT_APP_NONE,
    EVT_APP_INIT_DONE,
    EVT_APP_START,
    EVT_APP_STOP,
    EVT_APP_ERROR
} App_Event_t;

typedef enum {
    EVT_MENU_NONE = 0,
    EVT_MENU,
    EVT_MENU_CONFIG,
    EVT_MENU_SERVICE,
    EVT_MENU_EXIT,
    EVT_EXIT_TO_VENDING
} Menu_Event_t;

typedef enum {
    EVT_MDB_ACK = 0x00,
    EVT_MDB_ESCROW_REQUEST = 0x01,
    EVT_MDB_CHANGER_RESET = 0x0B,
    EVT_MDB_CHANGER_READY,
    EVT_MDB_COIN_VALID,
    EVT_MDB_COIN_INVALID,
    EVT_MDB_STATUS_CODE,
    EVT_MDB_NONE
} MDB_Event_t;

typedef enum {
    EVT_CREDIT_NONE = 0,
    EVT_CREDIT_AVAILABLE,
    EVT_CREDIT_UPDATED,
    EVT_CREDIT_ACCEPTED,
    EVT_CREDIT_CONSUME_PRICE_P1,
    EVT_CREDIT_CONSUME_PRICE_P2,
    EVT_CREDIT_REFUND_REQUEST,
    EVT_CREDIT_TIMEOUT,
    EVT_CREDIT_RESET
} Credit_Event_t;

typedef enum {
    EVT_COIN_NONE = 0,
    EVT_COIN_ACCEPTED,
    EVT_COIN_ESCROW_RETURNED,
    EVT_COIN_TUBE_STATUS,
    EVT_COIN_LOW_CHANGE,
    EVT_COIN_MANUAL_DISPENSE,
    EVT_COIN_FAULT
} Coin_Event_t;

typedef enum {
    EVT_VEND_CREDIT_EMPTY = 0,
    EVT_VEND_COIN_INSERTED,
    EVT_VEND_SELECT_PRODUCT,
    EVT_VEND_START_DISPENSE,
    EVT_VEND_DONE,
    EVT_VEND_REFUND_REQUEST
} Vend_Event_t;

typedef enum {
    EVT_UI_IDLE = 0,
    EVT_UI_HAS_CREDIT,
    EVT_UI_CREDIT_UPDATE,
    EVT_UI_VENDING,
    EVT_UI_OUT_OF_SERVICE
} UI_Event_t;

typedef enum {
    EVT_VENTA_NONE,


    EVT_VENTA_COIN_REJECTED,


    EVT_VENTA_CHANGER_BUSY,
    EVT_VENTA_CHANGER_READY,
    EVT_VENTA_NO_CREDIT,


    EVT_VENTA_CHANGER_ERROR,
    EVT_VENTA_ROM_ERROR,
    EVT_VENTA_TUBE_JAM,
    EVT_VENTA_DOUBLE_ARRIVAL,
    EVT_VENTA_ROUTE_ERROR,
    EVT_VENTA_COIN_JAM,
    EVT_VENTA_REJECTER_ERROR,


    EVT_VENTA_ENABLE_COINS,
    EVT_VENTA_DISABLE_COINS

} Venta_Event_t;
# 6 "Include/global.h" 2


typedef enum {
    ST_GLOBAL_INIT = 0,
    ST_GLOBAL_READY,
    ST_GLOBAL_CREDIT,
    ST_GLOBAL_VENDING,
    ST_GLOBAL_OUT_OF_SERVICE
} Global_State_t;


void Global_Init(void);
void Global_Dispatch(Global_Event_t evt);
void Global_Task(void);



const char* Global_GetState(void);
# 3 "sources/dispatcher.c" 2
# 1 "Include/credit.h" 1





void Credit_Dispatch(Credit_Event_t evt, uint16_t value);

const char* Credit_GetState(void);

void Credit_Init(void);

void Credit_Task(void);
# 4 "sources/dispatcher.c" 2
# 1 "Include/vend.h" 1






const char* Vend_GetState(void) ;

void Vend_Dispatch(Vend_Event_t evt);

uint16_t Vend_GetSecondsLeft(void);

void Vend_Init(void);



void Vend_Task(void);
# 5 "sources/dispatcher.c" 2
# 1 "Include/fsm_mdb_link.h" 1
# 10 "Include/fsm_mdb_link.h"
# 1 "Include/mdb.h" 1
# 127 "Include/mdb.h"
typedef struct
{
  uint8_t CoinChangerFeatureLevel;
  uint16_t CountryOrCurrencyCode;
  uint8_t CoinScalingFactor;
  uint8_t DecimalPlaces;
  uint8_t CoinsRouteable[16];
  uint8_t CoinTypeCredit[16];
  uint8_t NumCoinTypes;
} CoinChanger_Info_t;


typedef struct
{
  uint16_t Full_Status;
  uint8_t Status[16];
  uint8_t Total_Tubes;
} Tube_Status_t;

typedef struct
{
  unsigned int SoftwareVersion;
  unsigned char AlternativePayout;
  unsigned char ExtendedDiagnostic;
  unsigned char ControlledManualFillAndPayout;
  unsigned char FTLSupported;
  unsigned char ManufacturerCode[3];
  unsigned char SerialNumber[12];
  unsigned char ModelRevision[12];
} CCID_Data_t;
# 11 "Include/fsm_mdb_link.h" 2
# 1 "Include/mdb_core.h" 1
# 12 "Include/mdb_core.h"
typedef struct {
    uint8_t rxdata[36+10];
    uint8_t len;
    _Bool checksum_ok;
} mdb_frame_t;
# 31 "Include/mdb_core.h"
void MDB_Core_Init(void);
void MDB_Core_Task(void);
_Bool MDB_Core_FrameAvailable(void);
mdb_frame_t* MDB_Core_GetFrame(void);
void MDB_Core_ReleaseFrame(void);
# 12 "Include/fsm_mdb_link.h" 2

    typedef enum {
        ST_MDB_RESET = 0,
        ST_MDB_RESET_WAIT,
        ST_MDB_JUST_RESET,
        ST_MDB_JUST_RESET_WAIT,
        ST_MDB_SETUP,
        ST_MDB_SETUP_WAIT,
        ST_MDB_EXP_ID,
        ST_MDB_EXP_ID_WAIT,
        ST_MDB_EXP_FEATURE,
        ST_MDB_EXP_FEATURE_WAIT,
        ST_MDB_TUBE_STATUS,
        ST_MDB_TUBE_STATUS_WAIT,
        ST_MDB_ENABLE_COINS,
        ST_MDB_ENABLE_COINS_WAIT,
        ST_MDB_DISBLE_COINS,
        ST_MDB_DISABLE_COINS_WAIT,
        ST_MDB_POLL,
        ST_MDB_POLL_WAIT,
        ST_MDB_REFUND,
        ST_MDB_ERROR,
        ST_MDB_WAIT
    } MDB_Link_State_t;

    typedef struct {
        uint8_t Tx[7];
        uint8_t Tx_len;
        uint8_t Rx[ 36+10 ];
        uint8_t Rx_len;
        uint8_t Valid;
    } MDB_Log_t;

    MDB_Link_State_t MDB_Link_GetState(void);
    void MDB_Link_Dispatch(MDB_Event_t evt, uint16_t param0);
    void MDB_Link_Init(void);



    void MDB_Link_Task(void);

    extern volatile uint8_t mdb_diag_ready;
    extern volatile uint8_t mdb_diag_error;
# 6 "sources/dispatcher.c" 2

# 1 "Include/ui.h" 1







const char* UI_GetState(void);

void UI_Dispatch(UI_Event_t evt);
void UI_Vend_SetSelect(void);
void UI_Init(void);
void UI_View_Task(void);

void UI_Show_MDB_Rx_Line4(const uint8_t *tx, const uint8_t *rx, uint8_t len);

void UI_Ctrl_Task(void);
# 8 "sources/dispatcher.c" 2







static DispatcherEvent_t queue[16];
static volatile uint8_t q_head = 0;
static volatile uint8_t q_tail = 0;



static __attribute__((inline)) uint8_t NextIndex(uint8_t idx) {
    return (idx + 1) % 16;
}

static _Bool Queue_IsEmpty(void) {
    return q_head == q_tail;
}

static _Bool Queue_IsFull(void) {
    return NextIndex(q_tail) == q_head;
}



void Dispatcher_Init(void) {
    q_head = q_tail = 0;
}

_Bool Dispatcher_Post(EventSource_t src, uint16_t evt, uint16_t param) {
    if (Queue_IsFull())
        return 0;

    queue[q_tail].src = src;
    queue[q_tail].evt = evt;
    queue[q_tail].param = param;

    q_tail = NextIndex(q_tail);
    return 1;
}



static void Dispatcher_Handle(const DispatcherEvent_t *e) {

    switch (e->src) {


        case SRC_MDB:
            switch (e->evt) {
                case EVT_MDB_CHANGER_READY:
                    Global_Dispatch(EVT_GLOBAL_SYSTEM_READY);
                    break;

                case EVT_MDB_CHANGER_RESET:
                    Global_Dispatch(EVT_GLOBAL_ERROR);
                    Credit_Dispatch(EVT_CREDIT_RESET, 0);
                    break;

                case EVT_MDB_COIN_VALID:
                    Credit_Dispatch(EVT_CREDIT_ACCEPTED, e->param);
                    Vend_Dispatch(EVT_VEND_COIN_INSERTED);
                    break;

                case EVT_MDB_ESCROW_REQUEST:
                    MDB_Link_Dispatch(EVT_MDB_ESCROW_REQUEST, e->param);
                    break;

                default:
                    break;
            }
            break;


        case SRC_CREDIT:
            switch (e->evt) {
                case EVT_CREDIT_AVAILABLE:
                    Global_Dispatch(EVT_GLOBAL_CREDIT_AVAILABLE);
                    break;

                case EVT_CREDIT_UPDATED:
                    UI_Dispatch(EVT_UI_CREDIT_UPDATE);
                    break;

                case EVT_CREDIT_NONE:
                    Global_Dispatch(EVT_GLOBAL_CREDIT_EMPTY);
                    Vend_Dispatch(EVT_VEND_CREDIT_EMPTY);
                    break;

                default:
                    break;
            }
            break;


        case SRC_VEND:
            switch (e->evt) {
                case EVT_VEND_DONE:
                    Global_Dispatch(EVT_GLOBAL_VEND_DONE);
                    break;

                case EVT_VEND_REFUND_REQUEST:
                    Credit_Dispatch(EVT_CREDIT_RESET, 0);
                    break;

                default:
                    break;
            }
            break;


        case SRC_UI:
        case SRC_APP:

            break;

        default:
            break;
    }
}

void Dispatcher_Task(void) {
    DispatcherEvent_t evt;

    if (Queue_IsEmpty())
        return;

    evt = queue[q_head];
    q_head = NextIndex(q_head);

    Dispatcher_Handle(&evt);
}
