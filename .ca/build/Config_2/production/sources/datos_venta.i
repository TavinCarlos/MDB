# 1 "sources/datos_venta.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 295 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include/language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "sources/datos_venta.c" 2
# 1 "Include/datos_venta.h" 1







# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdint.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/musl_xc8.h" 1 3
# 5 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdint.h" 2 3
# 26 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 1 3
# 133 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef unsigned __int24 uintptr_t;
# 148 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef __int24 intptr_t;
# 164 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef signed char int8_t;




typedef short int16_t;




typedef __int24 int24_t;




typedef long int32_t;





typedef long long int64_t;
# 194 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef long long intmax_t;





typedef unsigned char uint8_t;




typedef unsigned short uint16_t;




typedef __uint24 uint24_t;




typedef unsigned long uint32_t;





typedef unsigned long long uint64_t;
# 235 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/alltypes.h" 3
typedef unsigned long long uintmax_t;
# 27 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdint.h" 2 3

typedef int8_t int_fast8_t;

typedef int64_t int_fast64_t;


typedef int8_t int_least8_t;
typedef int16_t int_least16_t;

typedef int24_t int_least24_t;
typedef int24_t int_fast24_t;

typedef int32_t int_least32_t;

typedef int64_t int_least64_t;


typedef uint8_t uint_fast8_t;

typedef uint64_t uint_fast64_t;


typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;

typedef uint24_t uint_least24_t;
typedef uint24_t uint_fast24_t;

typedef uint32_t uint_least32_t;

typedef uint64_t uint_least64_t;
# 148 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/bits/stdint.h" 1 3
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 149 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdint.h" 2 3
# 9 "Include/datos_venta.h" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdbool.h" 1 3
# 10 "Include/datos_venta.h" 2


typedef struct {
    uint16_t Precio1;
    uint16_t Precio2;
    uint16_t Tiempo1;
    uint16_t Tiempo2;
    uint16_t Contador1;
    uint16_t Contador2;
} DATOS_VENTA_t;




void DatosVenta_Init(void);


const DATOS_VENTA_t* DatosVenta_Get(void);


_Bool DatosVenta_SetPrecio1(uint16_t v);
_Bool DatosVenta_SetPrecio2(uint16_t v);
_Bool DatosVenta_SetTiempo1(uint16_t v);
_Bool DatosVenta_SetTiempo2(uint16_t v);


void DatosVenta_IncContador1(void);
void DatosVenta_IncContador2(void);


void DatosVenta_Save(void);


void DatosVenta_ResetDefaults(void);
# 2 "sources/datos_venta.c" 2
# 1 "Include/eeprom_hw.h" 1
# 13 "Include/eeprom_hw.h"
uint8_t EEPROM_Read(uint16_t address);


void EEPROM_Write(uint16_t address, uint8_t data, uint8_t wait);
# 3 "sources/datos_venta.c" 2
# 19 "sources/datos_venta.c"
static DATOS_VENTA_t g_datos;
static uint16_t g_magic;


static _Bool DatosVenta_Valid(const DATOS_VENTA_t *d) {
    if (d->Precio1 == 0 || d->Precio2 == 0)
        return 0;
    if (d->Tiempo1 == 0 || d->Tiempo2 == 0)
        return 0;
    return 1;
}


static void DatosVenta_LoadDefaults(void) {
    g_datos.Precio1 = 800;
    g_datos.Precio2 = 1800;
    g_datos.Tiempo1 = 20;
    g_datos.Tiempo2 = 60;
    g_datos.Contador1 = 0;
    g_datos.Contador2 = 0;
}

static void EEPROM_ReadBlock(uint16_t addr, void *dst, uint16_t len) {
    uint8_t *p = (uint8_t *) dst;
    while (len--) {
        *p++ = EEPROM_Read(addr++);
    }
}

static void EEPROM_WriteBlock(uint16_t addr, const void *src, uint16_t len) {
    const uint8_t *p = (const uint8_t *) src;
    while (len--) {
        EEPROM_Write(addr++, *p++, 1);
    }
}



void DatosVenta_Init(void) {
    uint16_t magic;

    EEPROM_ReadBlock(0x0000, &magic, sizeof (magic));

    if (magic != 0xA55A) {
        DatosVenta_LoadDefaults();
        magic = 0xA55A;
        EEPROM_WriteBlock(0x0002, &g_datos, sizeof (g_datos));
        EEPROM_WriteBlock(0x0000, &magic, sizeof (magic));
    }
    else {
        EEPROM_ReadBlock(0x0002, &g_datos, sizeof (g_datos));
    }
}

const DATOS_VENTA_t* DatosVenta_Get(void) {
    return &g_datos;
}



_Bool DatosVenta_SetPrecio1(uint16_t v) {
    if (v == 0) return 0;
    g_datos.Precio1 = v;
    return 1;
}

_Bool DatosVenta_SetPrecio2(uint16_t v) {
    if (v == 0) return 0;
    g_datos.Precio2 = v;
    return 1;
}

_Bool DatosVenta_SetTiempo1(uint16_t v) {
    if (v == 0) return 0;
    g_datos.Tiempo1 = v;
    return 1;
}

_Bool DatosVenta_SetTiempo2(uint16_t v) {
    if (v == 0) return 0;
    g_datos.Tiempo2 = v;
    return 1;
}



void DatosVenta_IncContador1(void) {
    if (g_datos.Contador1 < 0xFFFF)
        g_datos.Contador1++;
}

void DatosVenta_IncContador2(void) {
    if (g_datos.Contador2 < 0xFFFF)
        g_datos.Contador2++;
}



void DatosVenta_Save(void) {
    if (DatosVenta_Valid(&g_datos))
        EEPROM_WriteBlock(0x0002, &g_datos, sizeof (g_datos));
}
