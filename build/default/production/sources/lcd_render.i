# 1 "sources/lcd_render.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 295 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include/language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "sources/lcd_render.c" 2
# 1 "Include/lcd_render.h" 1



# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdint.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/musl_xc8.h" 1 3
# 5 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdint.h" 2 3
# 26 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 1 3
# 133 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef unsigned __int24 uintptr_t;
# 148 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef __int24 intptr_t;
# 164 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef signed char int8_t;




typedef short int16_t;




typedef __int24 int24_t;




typedef long int32_t;





typedef long long int64_t;
# 194 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef long long intmax_t;





typedef unsigned char uint8_t;




typedef unsigned short uint16_t;




typedef __uint24 uint24_t;




typedef unsigned long uint32_t;





typedef unsigned long long uint64_t;
# 235 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef unsigned long long uintmax_t;
# 27 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdint.h" 2 3

typedef int8_t int_fast8_t;

typedef int64_t int_fast64_t;


typedef int8_t int_least8_t;
typedef int16_t int_least16_t;

typedef int24_t int_least24_t;
typedef int24_t int_fast24_t;

typedef int32_t int_least32_t;

typedef int64_t int_least64_t;


typedef uint8_t uint_fast8_t;

typedef uint64_t uint_fast64_t;


typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;

typedef uint24_t uint_least24_t;
typedef uint24_t uint_fast24_t;

typedef uint32_t uint_least32_t;

typedef uint64_t uint_least64_t;
# 148 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/stdint.h" 1 3
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 149 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdint.h" 2 3
# 5 "Include/lcd_render.h" 2

void LCD_FSM_Init(void);
void LCD_Render_Task(void);
void LCD_Write_Buffer(uint8_t row, uint8_t col, const char *str);
void LCD_Clear_Buffer(void);
# 2 "sources/lcd_render.c" 2
# 1 "Include/lcd_hal.h" 1





void LCD_HAL_Init(void);
void LCD_HAL_SendCommand(uint8_t cmd);
void LCD_HAL_SendData(uint8_t data);
# 3 "sources/lcd_render.c" 2

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
    LCD_Clear_Buffer();
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
                lcd_dirty = 0;
            }

            state = LCD_FSM_IDLE;
            break;
        case LCD_FSM_SET_ADDR:
            break;
    }
}
