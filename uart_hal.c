#include <xc.h>
#include <builtins.h>
#include <pic18f4550.h>
#include "program.h"


// Configuraci?n del UART



//void UART_Write9_Old(const uint8_t data, uint8_t mode)
//{
//    while (!PIR1bits.TXIF);   // Esperar TXREG vacío
//
//    TXSTAbits.TX9D = (mode ? 1 : 0);  // 9th bit (MDB mode)
//    TXREG = data;
//}

void UART_Write9(uint8_t data, uint8_t mode) // new
{
    while (!PIR1bits.TXIF);
    TXSTAbits.TX9D = mode;
    TXREG = data;
    while (!TXSTAbits.TRMT);
}


void hal_UART_SendACK(void)
{
    UART_Write9(0x00, 0);
}


void hal_UART_Write_Cmd_old(const uint8_t *datos, uint8_t longitudDatos)
{
  while (!TXIF)
    ;               // espera que se transmita lo pendientee
  TXSTAbits.TX9D = 1;   // 9no bit activado
  TXREG = datos[0]; // transmite direccion
  TXSTAbits.TX9D = 0;   // 9no bit activado
  for (uint8_t i = 1; i < longitudDatos; i++)
      UART_Write9(datos[i], 0);
}

void hal_UART_Write_Cmd(const uint8_t *datos, uint8_t len)
{
    UART_Write9(datos[0], 1);
    for (uint8_t i = 1; i < len; i++)
        UART_Write9(datos[i], 0);
    __delay_us(50);   // Prueba: pequeño espacio post-frame
}







/*static void MDB_SendCmd(uint8_t cmd, uint8_t sub,
        MDB_MACHINE_STATE next_resp,
        TimerNB_t *timeout, uint16_t ms,
        uint8_t waitTime)
{
  uint8_t k;
  MDB_Send_Command(cmd, sub);    // Enviar comando al MDB.
  k = (cmd == 0x0c) || (cmd == 0x0f) ? 2 : 1;
  MDB_Log_TX(&cmd, k);                  // Registrar log
  TimerNB_Start(timeout, ms);           // timer para TimeOut
  myMachine.estado_actual = next_resp;  // Estado siguiente
  if (waitTime > 0)
     MDB_GotoWait(next_resp, 200);
}*/

