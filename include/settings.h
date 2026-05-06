#ifndef SETTINGS_H
#define	SETTINGS_H

#ifdef	__cplusplus
extern "C" {
#endif

void Timer0_Init(void);
void Timer1_Init(void);
void GPIO_Init(void);

void UART1_Init_a(uint32_t baud);

void UART1_Init_c(uint32_t baud);


#ifdef	__cplusplus
}
#endif

#endif	/* SETTINGS_H */

