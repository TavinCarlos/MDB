#ifndef MDB_UART_H
#define	MDB_UART_H

#include <stdint.h>
#include <stdbool.h>

void UART_Helper_Init(void);
uint8_t UART_Helper_BytesAvailable(void);
void UART_Helper_Flush(void);
uint8_t UART_Helper_Read(uint8_t *byte, uint8_t *bit9);

void UART1_Init(uint32_t baud);

#endif	/* MDB_UART_H */

