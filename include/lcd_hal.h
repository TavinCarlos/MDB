#ifndef LCD_HAL_H
#define LCD_HAL_H

#include <stdint.h>

void LCD_HAL_Init(void);
void LCD_HAL_SendCommand(uint8_t cmd);
void LCD_HAL_SendData(uint8_t data);

#endif
