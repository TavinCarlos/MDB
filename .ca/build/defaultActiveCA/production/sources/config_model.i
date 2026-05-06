# 1 "sources/config_model.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 295 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include/language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "sources/config_model.c" 2
# 1 "Include/config_model.h" 1



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
# 5 "Include/config_model.h" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.10\\pic\\include\\c99/stdbool.h" 1 3
# 6 "Include/config_model.h" 2



typedef enum {
    CFG_PRECIO1 = 0,
    CFG_PRECIO2,
    CFG_TIEMPO1,
    CFG_TIEMPO2
} config_param_id_t;


void ConfigModel_Init(void);


uint16_t ConfigModel_Get(config_param_id_t id);


_Bool ConfigModel_Set(config_param_id_t id, uint16_t value);


void ConfigModel_Save(void);
# 2 "sources/config_model.c" 2
# 1 "Include/datos_venta.h" 1
# 12 "Include/datos_venta.h"
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
# 3 "sources/config_model.c" 2

void ConfigModel_Init(void)
{
    DatosVenta_Init();
}

uint16_t ConfigModel_Get(config_param_id_t id)
{
    const DATOS_VENTA_t *d = DatosVenta_Get();

    switch (id) {
        case CFG_PRECIO1: return d->Precio1;
        case CFG_PRECIO2: return d->Precio2;
        case CFG_TIEMPO1: return d->Tiempo1;
        case CFG_TIEMPO2: return d->Tiempo2;
        default: return 0;
    }
}

_Bool ConfigModel_Set(config_param_id_t id, uint16_t value)
{
    switch (id) {
        case CFG_PRECIO1: return DatosVenta_SetPrecio1(value);
        case CFG_PRECIO2: return DatosVenta_SetPrecio2(value);
        case CFG_TIEMPO1: return DatosVenta_SetTiempo1(value);
        case CFG_TIEMPO2: return DatosVenta_SetTiempo2(value);
        default: return 0;
    }
}

void ConfigModel_Save(void)
{
    DatosVenta_Save();
}
