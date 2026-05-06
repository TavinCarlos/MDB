#ifndef FSM_GLOBAL_H
#define	FSM_GLOBAL_H

#include <stdint.h>
#include "events.h"

/* ===== Estados ===== */
typedef enum {
    ST_GLOBAL_INIT = 0, // Arranque del sistema - Hardware/MDB aún no listo
    ST_GLOBAL_READY, // Máquina lista, sin crédito - Usuario puede interactuar
    ST_GLOBAL_CREDIT, // Hay crédito disponible - Usuario puede comprar
    ST_GLOBAL_VENDING, // Venta en proceso - Máquina ocupada
    ST_GLOBAL_OUT_OF_SERVICE // Fuera de servicio - Negocio bloqueado
} Global_State_t;

/* ===== API ===== */
void Global_Init(void);
void Global_Dispatch(Global_Event_t evt);
void Global_Task(void);

/* ===== Debug ===== */
// Global_State_t Global_Get_State(void);
const char* Global_GetState(void);

#endif	/* FSM_GLOBAL_H */

