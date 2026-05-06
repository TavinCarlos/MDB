#include "dispatcher.h"
#include "global.h"
#include "credit.h"
#include "vend.h"
#include "mdb_link.h"
#include "events.h"
#include "ui.h"

/* ================== Configuración ================== */

#define DISPATCHER_QUEUE_SIZE 16

/* ================== Cola circular ================== */

static DispatcherEvent_t queue[DISPATCHER_QUEUE_SIZE];
static volatile uint8_t q_head = 0;
static volatile uint8_t q_tail = 0;

/* ================== Utilidades internas ================== */

static inline uint8_t NextIndex(uint8_t idx) {
    return (idx + 1) % DISPATCHER_QUEUE_SIZE;
}

static bool Queue_IsEmpty(void) {
    return q_head == q_tail;
}

static bool Queue_IsFull(void) {
    return NextIndex(q_tail) == q_head;
}

/* ================== API pública ================== */

void Dispatcher_Init(void) {
    q_head = q_tail = 0;
}

bool Dispatcher_Post(EventSource_t src, uint16_t evt, uint16_t param) {
    if (Queue_IsFull())
        return false;

    queue[q_tail].src = src;
    queue[q_tail].evt = evt;
    queue[q_tail].param = param;

    q_tail = NextIndex(q_tail);
    return true;
}

/* ================== Núcleo ================== */

static void Dispatcher_Handle(const DispatcherEvent_t *e) {

    switch (e->src) {
            /* ---------------- MDB ---------------- */
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
                    
                case EVT_MDB_DIAG_REQUEST:
                    break;

                default:
                    break;
            }
            break;

            /* ---------------- CREDIT ---------------- */
        case SRC_CREDIT:
            switch (e->evt) {
                case EVT_CREDIT_AVAILABLE:
                    Global_Dispatch(EVT_GLOBAL_CREDIT_AVAILABLE);
                    break;

                case EVT_CREDIT_UPDATED:
                    UI_Dispatch(EVT_UI_CREDIT_UPDATE); // o con param si tu UI lo usa
                    break;

                case EVT_CREDIT_NONE:
                    Global_Dispatch(EVT_GLOBAL_CREDIT_EMPTY);
                    Vend_Dispatch(EVT_VEND_CREDIT_EMPTY);
                    break;

                default:
                    break;
            }
            break;

            /* ---------------- VEND ---------------- */
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


            /* ---------------- MDB ---------------- */
        case SRC_APP:
            switch (e->evt) {
                case EVT_MDB_DIAG_REQUEST:                    
                    MDB_Link_Dispatch(EVT_MDB_DIAG_REQUEST, 0);
                    break;                
            }
            break;

            /* ------------------------------------------------ UI / APP */
        case SRC_UI:
            /* Reservado para expansión */
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

