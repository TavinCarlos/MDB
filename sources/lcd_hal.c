#include <xc.h>
#include "lcd_hal.h"
#include "program.h"   // _XTAL_FREQ

// === Pines ===
#define LCD_RS LATBbits.LATB2
#define LCD_EN LATBbits.LATB3
#define LCD_D4 LATBbits.LATB4
#define LCD_D5 LATBbits.LATB5
#define LCD_D6 LATBbits.LATB6
#define LCD_D7 LATBbits.LATB7

#define TRIS_LCD TRISB

static void LCD_PulseEN(void)
{
    LCD_EN = 1;
    __delay_us(1);   // timing garantizado
    LCD_EN = 0;
    __delay_us(50);
}

static void LCD_SendNibble(uint8_t n)
{
    LCD_D4 = (n >> 0) & 1;
    LCD_D5 = (n >> 1) & 1;
    LCD_D6 = (n >> 2) & 1;
    LCD_D7 = (n >> 3) & 1;
    LCD_PulseEN();
}

void LCD_HAL_SendCommand(uint8_t cmd)
{
    LCD_RS = 0;
    LCD_SendNibble(cmd >> 4);
    LCD_SendNibble(cmd & 0x0F);
}

void LCD_HAL_SendData(uint8_t data)
{
    LCD_RS = 1;
    LCD_SendNibble(data >> 4);
    LCD_SendNibble(data & 0x0F);
}

void LCD_HAL_Init(void)
{
    TRIS_LCD = 0x00;
    LATB = 0x00;

    __delay_ms(20);

    // Reset HD44780
    for(uint8_t i = 0; i < 3; i++)
    {
        LCD_RS = 0;
        LCD_SendNibble(0x03);
        __delay_ms(5);
    }

    LCD_SendNibble(0x02); // 4-bit

    LCD_HAL_SendCommand(0x28); // 4-bit, 2-line mode
    LCD_HAL_SendCommand(0x0C); // Display ON
    LCD_HAL_SendCommand(0x06); // Entry mode
    LCD_HAL_SendCommand(0x01); // Clear
    __delay_ms(2);
}

