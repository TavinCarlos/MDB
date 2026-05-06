/* 
 * File:   hal_uart.h
 * Author: Carlos
 *
 * Created on January 3, 2026, 8:01 PM
 */

#ifndef HAL_UART_H
#define	HAL_UART_H

#ifdef	__cplusplus
extern "C" {
#endif


void UART_Init_9600_9bit(void);

void hal_UART_SendACK(void);

void hal_UART_Write_Cmd(const uint8_t *datos, uint8_t longitudDatos);


#ifdef	__cplusplus
}
#endif

#endif	/* HAL_UART_H */

