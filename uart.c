#include <xc.h>
#include "uart.h"
#include <string.h>

/* ===== Buffers compartidos con la ISR ===== */
extern volatile uint8_t Rx_data[];
extern volatile uint8_t RX_mode[];
extern volatile uint8_t received_data;

/* ===== ?ndice de lectura (NO tocado por ISR) ===== */
static uint8_t rx_read_idx;

/* ===== Inicializaci?n ===== */
void UART_Helper_Init(void)
{
    rx_read_idx = 0;
}

/* ===== ?Hay bytes disponibles? ===== */
uint8_t UART_Helper_BytesAvailable(void)
{
    return (rx_read_idx < received_data);
}

void UART_Helper_Flush(void)
{
    rx_read_idx = 0;
    received_data = 0;
}

/* ===== Leer un byte + bit9 ===== */
uint8_t UART_Helper_Read(uint8_t *byte, uint8_t *bit9)
{
    
    if (rx_read_idx >= received_data)
        return 0;

    *byte = Rx_data[rx_read_idx];
    *bit9 = RX_mode[rx_read_idx];

    rx_read_idx++;
    
    return 1;

    /* Cuando se consumen todos los bytes, reiniciar buffer */
    if (rx_read_idx >= received_data)
    {
        rx_read_idx = 0;
        received_data = 0;
    }

    return 0;
}




