#ifndef _SALDO_H_
#define _SALDO_H_

#include <stdint.h>

void Saldo_Init(void);

/* Entradas (solo desde MDB) */
void Saldo_Add(uint16_t amount);
void Saldo_Clear(void);

/* Uso (solo desde Vending FSM) */
uint8_t Saldo_CanAfford(uint16_t price);
void Saldo_Deduct(uint16_t price);

/* Lectura (UI / LCD) */
uint16_t Saldo_Get(void);

#endif	/* CREDIT_H */

