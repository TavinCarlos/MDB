#ifndef FSM_COIN_LOGIC_H
#define	FSM_COIN_LOGIC_H

#include "events.h" //  mdb_event_t para Entrada

void Credit_Dispatch(Credit_Event_t evt, uint16_t value);

const uint8_t Credit_GetInactivity(void);

const char* Credit_GetState(void);

void Credit_Init(void);

void Credit_Task(void);




#endif	

