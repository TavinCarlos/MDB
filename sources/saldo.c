#include "saldo.h"

static uint16_t saldo = 0;

void Saldo_Init(void)
{
    saldo = 0;
}

void Saldo_Add(uint16_t amount)
{
    saldo += amount;
}

void Saldo_Clear(void)
{
    saldo = 0;
}

uint8_t Saldo_CanAfford(uint16_t price)
{
    return (saldo >= price);
}

void Saldo_Deduct(uint16_t price)
{
    if (saldo >= price)
        saldo -= price;
}

uint16_t Saldo_Get(void)
{
    return saldo;
}

