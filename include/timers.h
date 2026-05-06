#ifndef TIMERS_H
#define	TIMERS_H

typedef struct
{
  uint32_t start;
  uint32_t delay;
  uint8_t active;
} TimerNB_t;

void TimerNB_Start(TimerNB_t *t, uint32_t ms);
uint8_t TimerNB_Expired(TimerNB_t *t);

uint32_t Millis(void);

void tcDelay_ms(uint32_t ms);

#endif	/* TIMERS_H */

