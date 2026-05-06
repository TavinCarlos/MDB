#include "global.h"
#include "mdb_link.h"
#include "vend.h"
#include "events.h"
#include "ui.h"
#include "saldo.h"

/* ================== Estado interno ================== */

static Global_State_t g_state = ST_GLOBAL_OUT_OF_SERVICE;

/* ================== Utilidades ================== */

static void TransitionTo(Global_State_t next) {
    if (g_state == next)
        return;

    g_state = next;

    /* La UI se actualiza SOLO aquí */
    switch (g_state) {

        case ST_GLOBAL_READY:
            UI_Dispatch(EVT_UI_IDLE);
            break;

        case ST_GLOBAL_CREDIT:
            UI_Dispatch(EVT_UI_HAS_CREDIT);
            break;

        case ST_GLOBAL_VENDING:
            UI_Dispatch(EVT_UI_VENDING);
            break;

        case ST_GLOBAL_OUT_OF_SERVICE:
            UI_Dispatch(EVT_UI_OUT_OF_SERVICE);
            break;

        default:
            break;
    }
}

/* ================== API pública ================== */

void Global_Init(void) {
    g_state = ST_GLOBAL_OUT_OF_SERVICE;
    UI_Dispatch(EVT_UI_OUT_OF_SERVICE);
}

//Global_State_t Global_Get_State(void) {
//    return g_state;
//}

const char* Global_GetState(void) {
    switch (g_state) {
        case ST_GLOBAL_READY:           return "R";
        case ST_GLOBAL_CREDIT:          return "C";
        case ST_GLOBAL_VENDING:         return "V";
        case ST_GLOBAL_OUT_OF_SERVICE:  return "O";
        default:                        return "?";
    }
}

void Global_Dispatch(Global_Event_t evt) {

    switch (g_state) {

        /* ---------- OUT OF SERVICE ---------- */
        case ST_GLOBAL_OUT_OF_SERVICE:
            if (evt == EVT_GLOBAL_SYSTEM_READY) {
                TransitionTo(ST_GLOBAL_READY);
            }
            break;

        /* ---------- READY ---------- */
        case ST_GLOBAL_READY:
            switch (evt) {
                case EVT_GLOBAL_CREDIT_AVAILABLE:
                    TransitionTo(ST_GLOBAL_CREDIT);
                    break;

                case EVT_GLOBAL_ERROR:
                    TransitionTo(ST_GLOBAL_OUT_OF_SERVICE);
                    break;

                default:
                    break;
            }
            break;

        /* ---------- CREDIT ---------- */
        case ST_GLOBAL_CREDIT:
            switch (evt) {
                case EVT_GLOBAL_SELECTION:
                    TransitionTo(ST_GLOBAL_VENDING);
                    break;

                case EVT_GLOBAL_CREDIT_EMPTY:
                    TransitionTo(ST_GLOBAL_READY);
                    break;

                case EVT_GLOBAL_ERROR:
                    TransitionTo(ST_GLOBAL_OUT_OF_SERVICE);
                    break;

                default:
                    break;
            }
            break;

        /* ---------- VENDING ---------- */
        case ST_GLOBAL_VENDING:
            switch (evt) {
                case EVT_GLOBAL_VEND_DONE:
                    TransitionTo(ST_GLOBAL_READY);
                    break;

                case EVT_GLOBAL_ERROR:
                    TransitionTo(ST_GLOBAL_OUT_OF_SERVICE);
                    break;

                default:
                    break;
            }
            break;

        default:
            TransitionTo(ST_GLOBAL_OUT_OF_SERVICE);
            break;
    }
}