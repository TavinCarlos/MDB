#include <xc.h>
#include "app.h"
#include "utils.h"
#include "botones.h"
#include "timers.h"
#include "events.h"
#include "saldo.h"
#include "vend.h"
#include "credit.h"
#include "dispatcher.h"
#include "datos_venta.h"

/* ================== Estados ================== */

typedef enum
{
    ST_VEND_IDLE = 0, // Esperando cliente
    ST_VEND_READY, // Dinero ingresado, esperando más o selección
    ST_VEND_DISPENSING, // Motor/Actuador en movimiento
    ST_VEND_ERROR // Bloqueo por fallo técnico
} Vend_State_t;

/* ================== Productos ================== */

typedef enum
{
    PROD_NONE = 0,
    PROD_GALLON,
    PROD_CARBOY
} Producto_t;

/* ================== Variables internas ================== */

static Vend_State_t current_state = ST_VEND_IDLE;

static struct
{
    uint16_t segundos_restantes;
    Producto_t producto;
} vend_ctx;

static TimerNB_t dispense_timer;

/* ================== Utilidades internas ================== */


static uint8_t VentaIsDone = 0;

//static Vend_State_t Vend_Get_State(void) {
//    return current_state;
//}

//int8_t Vend_IsDone(void) {
//    if (VentaIsDone == 1) {
//        VentaIsDone = 0;
//        return 1;
//    }
//    return 0;
//}

//uint16_t Vend_GetSecondsLeft(void) {
//    return vend_ctx.segundos_restantes;
//}
static void TransitionTo(Vend_State_t next) {
    if (current_state == next)
        return;

    current_state = next;

    //    switch (current_state) {
    //        case ST_VEND_IDLE:
    //            Dispatcher_Post(SRC_VEND, EVT_VEND_CREDIT_EMPTY, 0);
    //            break;
    //
    //        case ST_VEND_READY:
    //            break;
    //
    //        case ST_VEND_DISPENSING:
    //            Dispatcher_Post(SRC_VEND, EVT_VEND_SELECT_PRODUCT, 0);
    //            break;
    //
    //        case ST_VEND_DONE:
    //            Dispatcher_Post(SRC_VEND, EVT_VEND_DONE, 0);
    //            current_state = ST_VEND_IDLE;
    //            break;
    //
    //        case ST_VEND_ERROR:
    //            Dispatcher_Post(SRC_VEND, EVT_APP_ERROR, 0);
    //            break;
    //
    //        default:
    //            break;
    //    }

}

void StartDispense(Producto_t prod) {
    const DATOS_VENTA_t *dv = DatosVenta_Get();

    switch (prod) {
        case PROD_GALLON:
            vend_ctx.segundos_restantes = dv->Tiempo1;
            vend_ctx.producto = PROD_GALLON;
            Credit_Dispatch(EVT_CREDIT_CONSUME_PRICE_P1, dv->Precio1);
            RELAY_R0_ON();
            break;

        case PROD_CARBOY:
            vend_ctx.segundos_restantes = dv->Tiempo2;
            vend_ctx.producto = PROD_CARBOY;
            Credit_Dispatch(EVT_CREDIT_CONSUME_PRICE_P2, dv->Precio2);
            RELAY_R1_ON();
            break;

        default:
            break;
    }
    TimerNB_Start(&dispense_timer, 1000);
    TransitionTo(ST_VEND_DISPENSING);
}

void FinishDispense() {
    RELAY_R0_OFF();
    RELAY_R1_OFF();

    if (vend_ctx.producto == PROD_GALLON)
        DatosVenta_IncContador1();
    else if (vend_ctx.producto == PROD_CARBOY)
        DatosVenta_IncContador2();

    DatosVenta_Save();

    vend_ctx.producto = PROD_NONE;
    TransitionTo(ST_VEND_IDLE);
}



/* ================== API pública ================== */


void Vend_Init(void) {
    vend_ctx.segundos_restantes = 0;
    vend_ctx.producto = PROD_NONE;
    current_state = ST_VEND_IDLE;
}

void Vend_Dispatch(Vend_Event_t evt) {
    switch (current_state) {

        case ST_VEND_IDLE:
            if (evt == EVT_VEND_COIN_INSERTED)
                TransitionTo(ST_VEND_READY);
            break;

        case ST_VEND_READY:
            if (evt == EVT_VEND_CREDIT_EMPTY) {
                TransitionTo(ST_VEND_IDLE);
            }
            break;

        case ST_VEND_DISPENSING:
            break; 

        case ST_VEND_ERROR:
            // espera reset
            break; // Bloqueo por fallo técnico
    }
}

void Vend_Task(void) {

    switch (current_state) {

        case ST_VEND_IDLE:
            BtnA0_Event = BtnA1_Event = BtnA2_Event = 0;
            break;

        case ST_VEND_READY:
        {
            const DATOS_VENTA_t *dv = DatosVenta_Get();

            if (BtnA0_Event && Saldo_CanAfford(dv->Precio1)) {
                BtnA0_Event = 0;
                StartDispense(PROD_GALLON);
            }
            else if (BtnA1_Event && Saldo_CanAfford(dv->Precio2)) {
                BtnA1_Event = 0;
                StartDispense(PROD_CARBOY);
            }
            else if (BtnA2_Event) { // DEVOLUCION MANUAL (Boton A2)
                BtnA2_Event = 0;
                Dispatcher_Post(SRC_VEND, EVT_VEND_REFUND_REQUEST, Saldo_Get());
                TransitionTo(ST_VEND_IDLE);
            }
        }
            break;

        case ST_VEND_DISPENSING:
            if (TimerNB_Expired(&dispense_timer)) {
                if (vend_ctx.segundos_restantes > 0) {
                    vend_ctx.segundos_restantes--;
                    TimerNB_Start(&dispense_timer, 1000);
                }
                else {
                    FinishDispense();
                }
            }
            break;

        case ST_VEND_ERROR:
            break;
    }
}

/* ================== Debug ================== */

const char* Vend_GetState(void) {
    switch (current_state) {
        case ST_VEND_IDLE: return "I";
        case ST_VEND_READY: return "R";
        case ST_VEND_DISPENSING: return "D";
        case ST_VEND_ERROR: return "E";
        default: return "?";
    }
}

