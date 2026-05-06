#ifndef VENTA_FSM_H
#define	VENTA_FSM_H

#include "events.h"


const char* Vend_GetState(void) ;

void Vend_Dispatch(Vend_Event_t evt);

uint16_t Vend_GetSecondsLeft(void);

void Vend_Init(void);

// int8_t Vend_IsDone(void);

void Vend_Task(void);

#endif	/* VENTA_FSM_H */

