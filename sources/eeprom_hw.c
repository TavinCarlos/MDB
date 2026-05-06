#include <xc.h>
#include "eeprom_hw.h"

uint8_t EEPROM_Read(uint16_t address)
{
    EEADR = (uint8_t)(address & 0xFF);

#if defined(EEDATH)
    EEDATH = (uint8_t)(address >> 8);
#endif

    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS  = 0;
    EECON1bits.RD    = 1;

    return EEDATA;
}

void EEPROM_Write(uint16_t address, uint8_t data, uint8_t wait)
{
    uint8_t gie = INTCONbits.GIE;
    INTCONbits.GIE = 0;

    EEADR = (uint8_t)(address & 0xFF);

#if defined(EEDATH)
    EEDATH = (uint8_t)(address >> 8);
#endif

    EEDATA = data;

    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS  = 0;
    EECON1bits.WREN  = 1;

    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;

    if (wait) {
        while (EECON1bits.WR);
    }

    EECON1bits.WREN = 0;
    INTCONbits.GIE = gie;
}
