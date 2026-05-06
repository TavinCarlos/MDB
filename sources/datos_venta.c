#include "datos_venta.h"
#include "eeprom_hw.h"

///* ===== Configuración EEPROM ===== */
//#define EEPROM_MAGIC_ADDR  0x0000
//#define EEPROM_DATA_ADDR   0x0002
//#define DATOS_MAGIC        0xA55A


/* ===== Defaults (ajustables por país/localidad) ===== */
#define DEF_PRECIO1  800
#define DEF_PRECIO2 1800
#define DEF_TIEMPO1   20
#define DEF_TIEMPO2   60

// static void EEPROM_ReadBlock(uint16_t addr, void *dst, uint16_t len);
// static void EEPROM_WriteBlock(uint16_t addr, const void *src, uint16_t len);

static DATOS_VENTA_t g_datos;
static uint16_t g_magic;

/* ===== Validación ===== */
static bool DatosVenta_Valid(const DATOS_VENTA_t *d) {
    if (d->Precio1 == 0 || d->Precio2 == 0)
        return false;
    if (d->Tiempo1 == 0 || d->Tiempo2 == 0)
        return false;
    return true;
}

/* ===== Defaults ===== */
static void DatosVenta_LoadDefaults(void) {
    g_datos.Precio1 = DEF_PRECIO1;
    g_datos.Precio2 = DEF_PRECIO2;
    g_datos.Tiempo1 = DEF_TIEMPO1;
    g_datos.Tiempo2 = DEF_TIEMPO2;
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

/* ===== API ===== */

void DatosVenta_Init(void) {
    uint16_t magic;

    EEPROM_ReadBlock(EEPROM_MAGIC_ADDR, &magic, sizeof (magic));

    if (magic != DATOS_MAGIC) {
        DatosVenta_LoadDefaults();
        magic = DATOS_MAGIC;
        EEPROM_WriteBlock(EEPROM_DATA_ADDR, &g_datos, sizeof (g_datos));
        EEPROM_WriteBlock(EEPROM_MAGIC_ADDR, &magic, sizeof (magic));
    }
    else {
        EEPROM_ReadBlock(EEPROM_DATA_ADDR, &g_datos, sizeof (g_datos));
    }
}

const DATOS_VENTA_t* DatosVenta_Get(void) {
    return &g_datos;
}

/* ===== Setters ===== */

bool DatosVenta_SetPrecio1(uint16_t v) {
    if (v == 0) return false;
    g_datos.Precio1 = v;
    return true;
}

bool DatosVenta_SetPrecio2(uint16_t v) {
    if (v == 0) return false;
    g_datos.Precio2 = v;
    return true;
}

bool DatosVenta_SetTiempo1(uint16_t v) {
    if (v == 0) return false;
    g_datos.Tiempo1 = v;
    return true;
}

bool DatosVenta_SetTiempo2(uint16_t v) {
    if (v == 0) return false;
    g_datos.Tiempo2 = v;
    return true;
}

/* ===== Contadores ===== */

void DatosVenta_IncContador1(void) {
    if (g_datos.Contador1 < 0xFFFF)
        g_datos.Contador1++;
}

void DatosVenta_IncContador2(void) {
    if (g_datos.Contador2 < 0xFFFF)
        g_datos.Contador2++;
}

/* ===== Persistencia ===== */

void DatosVenta_Save(void) {
    if (DatosVenta_Valid(&g_datos))
        EEPROM_WriteBlock(EEPROM_DATA_ADDR, &g_datos, sizeof (g_datos));
}

//void DatosVenta_ResetDefaults(void) {
//    DatosVenta_LoadDefaults();
//    DatosVenta_Save();
//}


