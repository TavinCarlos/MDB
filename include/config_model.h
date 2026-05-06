#ifndef CONFIG_MODEL_H
#define CONFIG_MODEL_H

#include <stdint.h>
#include <stdbool.h>

#define CONFIG_PARAM_COUNT  4

typedef enum {
    CFG_PRECIO1 = 0,
    CFG_PRECIO2,
    CFG_TIEMPO1,
    CFG_TIEMPO2
} config_param_id_t;

/* Inicializa el modelo de configuración */
void ConfigModel_Init(void);

/* Obtiene valor actual */
uint16_t ConfigModel_Get(config_param_id_t id);

/* Setea valor (no guarda) */
bool ConfigModel_Set(config_param_id_t id, uint16_t value);

/* Guarda todos los valores */
void ConfigModel_Save(void);

#endif