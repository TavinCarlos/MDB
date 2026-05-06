#ifndef EVENTS_H
#define	EVENTS_H
#include <stdint.h>

/* ===== Eventos GLOBAL ===== */
typedef enum {
    EVT_GLOBAL_INIT_DONE, // Sistema listo               - mdb / SISTEMA
    EVT_GLOBAL_SYSTEM_READY,
    EVT_GLOBAL_CREDIT_AVAILABLE, // Crédito pasó de 0 a >0      - CreditFSM
    EVT_GLOBAL_CREDIT_EMPTY, // Crédito volvió a 0          - CreditFSM
    EVT_GLOBAL_SELECTION, // Usuario seleccionó producto - CreditFSM
    EVT_GLOBAL_VEND_DONE, // Venta terminó               - GlobalFSM_Task
    EVT_GLOBAL_ERROR, // Error grave                 - MDB/CreditFSM
    EVT_GLOBAL_SERVICE_RESET // Servicio libera error       - UI Service
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
    EVT_MDB_ACK = 0x00, // Más claro que POLL_ACK (indica que hay datos esperando)
    EVT_MDB_ESCROW_REQUEST = 0x01,
    EVT_MDB_CHANGER_RESET = 0x0B,
    EVT_MDB_CHANGER_READY,
    EVT_MDB_COIN_VALID,
    EVT_MDB_COIN_INVALID,
    EVT_MDB_STATUS_CODE,
    EVT_MDB_DIAG_REQUEST,
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
    EVT_COIN_ACCEPTED, // Mejor que CREDIT_UPDATED (indica la acción física)
    EVT_COIN_ESCROW_RETURNED, // El usuario recuperó sus monedas físicamente
    EVT_COIN_TUBE_STATUS, // Informa si los tubos están llenos/vacíos (crítico para dar cambio)
    EVT_COIN_LOW_CHANGE, // Indica que no hay suficiente cambio para transacciones
    EVT_COIN_MANUAL_DISPENSE, // Cuando un técnico saca monedas manualmente
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

    // EVT_VENTA_COIN_ACCEPTED, // Moneda válida aceptada
    EVT_VENTA_COIN_REJECTED, // Moneda inválida / checksum error

    /* --- Estados del monedero --- */
    EVT_VENTA_CHANGER_BUSY, // 02 02
    EVT_VENTA_CHANGER_READY, // Sale de busy
    EVT_VENTA_NO_CREDIT, // 03 03

    /* --- Errores --- */
    EVT_VENTA_CHANGER_ERROR, // 0A 0A
    EVT_VENTA_ROM_ERROR, // 08 08
    EVT_VENTA_TUBE_JAM, // 07 07
    EVT_VENTA_DOUBLE_ARRIVAL, // 05 05
    EVT_VENTA_ROUTE_ERROR, // 09 09
    EVT_VENTA_COIN_JAM, // 0C 0C
    EVT_VENTA_REJECTER_ERROR, // 0E 0E

    /* --- Control interno --- */
    EVT_VENTA_ENABLE_COINS, // Monedas habilitadas
    EVT_VENTA_DISABLE_COINS // Monedas deshabilitadas

} Venta_Event_t;


#endif	/* EVENTS_H */




//        EVT_UI_INIT_SUCCESS,
//        EVT_UI_INIT_FAIL,
//        EVT_MAINTENANCE_MODE,
//        EVT_BALANCE_REACHED,
//        EVT_CANCEL_PRESSED,
//        EVT_PRODUCT_SELECTED,
//        EVT_TIMEOUT,
//        EVT_REFUND_COMPLETE,
//        EVT_DISPENSE_SUCCESS,
//        EVT_USER_TAKE_ITEM,
//        EVT_REPAIR_DONE,                
//        EVT_UI_INVALID_SEL, // Producto agotado o precio mayor al crédito
//        EVT_UI_SELECTION,        
//        EVT_UI_SHOW_SUCCESS, // Mostrar "¡Gracias!" y liberar UI
//        EVT_UI_SHOW_REFUND, // Mostrar "Devolviendo cambio..."

