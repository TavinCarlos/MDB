#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "eeprom.h"
#include "bytes.h"


//uint8_t EEPROM_Read(uint8_t address)
//{
//    EEADR = address;
//    EECON1bits.EEPGD = 0; // Acceder a la memoria de datos EEPROM
//    EECON1bits.CFGS  = 0; // Acceder a la EEPROM
//    EECON1bits.RD    = 1; // Iniciar lectura
//
//    // El dato está listo en el siguiente ciclo de instrucción
//    return EEDATA;
//}


//void EEPROM_Write(uint8_t address, uint8_t data)
//{
//    uint8_t gie = INTCONbits.GIE; // guardar estado IRQ
//    INTCONbits.GIE = 0;           // deshabilitar interrupciones
//
//    EEADR  = address;  // Dirección a escribir (0-255)
//    EEDATA = data;     // Dato a escribir
//    EECON1bits.EEPGD = 0; // Acceder a la memoria de datos EEPROM
//    EECON1bits.CFGS  = 0; // Acceder a la EEPROM, no a la configuración
//    EECON1bits.WREN  = 1; // Habilitar escritura
//
//    // Secuencia obligatoria
//    EECON2 = 0x55;
//    EECON2 = 0xAA;
//    EECON1bits.WR = 1;
//
//    while (EECON1bits.WR); // esperar fin escritura
//
//    EECON1bits.WREN = 0;
//    INTCONbits.GIE = gie; // restaurar IRQ
//}

 