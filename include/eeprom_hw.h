#ifndef EEPROM_HW_H
#define	EEPROM_HW_H

#include <stdint.h>

/* ===== Configuración EEPROM ===== */
#define EEPROM_MAGIC_ADDR  0x0000
#define EEPROM_DATA_ADDR   0x0002
#define DATOS_MAGIC        0xA55A


/* Lee 1 byte de EEPROM interna */
uint8_t EEPROM_Read(uint16_t address);

/* Escribe 1 byte en EEPROM interna */
void EEPROM_Write(uint16_t address, uint8_t data, uint8_t wait);


#endif	/* EEPROM_HW_H */

