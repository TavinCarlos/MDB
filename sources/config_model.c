#include "config_model.h"
#include "datos_venta.h"

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

bool ConfigModel_Set(config_param_id_t id, uint16_t value)
{
    switch (id) {
        case CFG_PRECIO1: return DatosVenta_SetPrecio1(value);
        case CFG_PRECIO2: return DatosVenta_SetPrecio2(value);
        case CFG_TIEMPO1: return DatosVenta_SetTiempo1(value);
        case CFG_TIEMPO2: return DatosVenta_SetTiempo2(value);
        default: return false;
    }
}

void ConfigModel_Save(void)
{
    DatosVenta_Save();
}