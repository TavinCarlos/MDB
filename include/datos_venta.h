#ifndef DATOS_VENTA_H
#define	DATOS_VENTA_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/* ===== Estructura persistente ===== */
typedef struct {
    uint16_t Precio1;     // 0..65535
    uint16_t Precio2;     // 0..65535
    uint16_t Tiempo1;     // segundos
    uint16_t Tiempo2;     // segundos
    uint16_t Contador1;   // ciclos producto 1
    uint16_t Contador2;   // ciclos producto 2
} DATOS_VENTA_t;

/* ===== API pública ===== */

/* Inicializa el módulo (carga EEPROM o defaults) */
void DatosVenta_Init(void);

/* Obtiene copia consistente */
const DATOS_VENTA_t* DatosVenta_Get(void);

/* Setters controlados */
bool DatosVenta_SetPrecio1(uint16_t v);
bool DatosVenta_SetPrecio2(uint16_t v);
bool DatosVenta_SetTiempo1(uint16_t v);
bool DatosVenta_SetTiempo2(uint16_t v);

/* Contadores (solo incremento) */
void DatosVenta_IncContador1(void);
void DatosVenta_IncContador2(void);

/* Guardado explícito */
void DatosVenta_Save(void);

/* Restaurar valores por defecto */
void DatosVenta_ResetDefaults(void);


#ifdef	__cplusplus
}
#endif

#endif	/* DATOS_VENTA_H */

