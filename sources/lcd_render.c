#include "lcd_render.h"
#include "lcd_hal.h"

static char lcd_buffer[4][20];
static uint8_t lcd_dirty = 1;

typedef enum {
    LCD_FSM_IDLE,
    LCD_FSM_SET_ADDR,
    LCD_FSM_SEND_CHAR
} lcd_fsm_state_t;

static lcd_fsm_state_t state;
static uint8_t r, c;

void LCD_Clear_Buffer(void)
{
    for(uint8_t i=0;i<4;i++)
        for(uint8_t j=0;j<20;j++)
            lcd_buffer[i][j] = ' ';

    lcd_dirty = 1;
}

void LCD_Write_Buffer(uint8_t row, uint8_t col, const char *str)
{
    if(row < 1 || row > 4) return;

    uint8_t rr = row - 1;
    uint8_t cc = col - 1;

    while(*str && cc < 20)
        lcd_buffer[rr][cc++] = *str++;

    lcd_dirty = 1;
}

void LCD_FSM_Init(void)
{
    LCD_Clear_Buffer(); // <--- CRÍTICO: Llena el buffer con espacios
    state = LCD_FSM_IDLE;
    r = c = 0;
}

void LCD_Render_Task(void)
{
    uint8_t addr;

    if(!lcd_dirty)
        return;

    switch(state)
    {
        case LCD_FSM_IDLE:
            if(r == 0) addr = 0x80 + c;
            else if(r == 1) addr = 0xC0 + c;
            else if(r == 2) addr = 0x94 + c;
            else addr = 0xD4 + c;

            LCD_HAL_SendCommand(addr);
            state = LCD_FSM_SEND_CHAR;
            break;

        case LCD_FSM_SEND_CHAR:
            LCD_HAL_SendData(lcd_buffer[r][c]);

            c++;
            if(c >= 20)
            {
                c = 0;
                r++;
            }
            if(r >= 4)
            {
                r = 0;
                lcd_dirty = 0;   // refresco completo
            }

            state = LCD_FSM_IDLE;
            break;
        case LCD_FSM_SET_ADDR:
            break;
    }
}
