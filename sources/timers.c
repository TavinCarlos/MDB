#include <xc.h>
#include <stdint.h>
#include "program.h"
#include "timers.h"
#include "utils.h"
#include "app.h"

typedef enum {
    TMR_MDB_INTERBYTE,
    TMR_MDB_MAX
} timer_id_t;




uint32_t Millis(void)
{
  uint32_t current;
  INTCONbits.GIE = 0; // GIE = 0; Deshabilitar interrupciones brevemente para lectura at�mica
  current = timer0_millis;
  INTCONbits.GIE = 1; // habilitar interrupciones
  return current;
}


void TimerNB_Start(TimerNB_t *t, uint32_t ms)
{
  t->start = Millis();
  t->delay = ms;
  t->active = 1;
}

uint8_t TimerNB_Expired(TimerNB_t *t)
{
  if (!t->active)
    return 0;

  if ((Millis() - t->start) >= t->delay)
  {
    t->active = 0;
    return 1;
  }
  return 0;
}


//void _mydelay_ms(uint32_t ms)
//{
//  uint32_t start = millis();
//  while ((millis() - start) < ms)
//      __nop();
//}


//void _delay_seconds(uint16_t x)
//{
//  uint16_t cont;
//  uint16_t mult = x * 100;
//  for (cont = 0; cont < mult; cont++) {
//    __delay_ms(10);
//  }
//}

