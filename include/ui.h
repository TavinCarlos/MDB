#ifndef UI_VENDING_H
#define	UI_VENDING_H

#include "events.h"

const char* UI_GetState(void);

void UI_Dispatch(UI_Event_t evt);

void UI_Vend_SetSelect(void);

void UI_Init(void);

void UI_View_Credit(void);

void UI_View_Task(void);

void UI_Show_MDB_Rx_Line4(const uint8_t *tx, const uint8_t *rx, uint8_t len);

void UI_Ctrl_Task(void);

// void UI_SetProgress(UI_Event_t evt, uint8_t value);



#endif	/* UI_VENDING_H */

