#ifndef LCD_FSM_H
#define LCD_FSM_H

#include <stdint.h>

void LCD_FSM_Init(void);
void LCD_Render_Task(void);
void LCD_Write_Buffer(uint8_t row, uint8_t col, const char *str);
void LCD_Clear_Buffer(void);

#endif
