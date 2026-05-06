#ifndef BOTONES_H
#define	BOTONES_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

// ====== CONFIGURACIÓN ======
#define BTN_DEBOUNCE_MS   30   // tiempo antirrebote

// ====== EVENTOS ======
extern volatile bool BtnA0_Event;
extern volatile bool BtnA1_Event;
extern volatile bool BtnA2_Event;

extern volatile bool BtnD0_Event;
extern volatile bool BtnD1_Event;
extern volatile bool BtnD2_Event;

extern volatile bool BtnD0_LongEvent;

// ====== API ======
void Buttons_Init(void);
void Buttons_Task(void);

bool BtnD1_IsPressed(void);
bool BtnD2_IsPressed(void);


#endif	/* BOTONES_H */

