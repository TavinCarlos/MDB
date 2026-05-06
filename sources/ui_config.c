#include <stdint.h>
#include <string.h>

#include "app.h"
#include "utils.h"
#include "botones.h"
#include "ui_config.h"
#include "events.h"
#include "lcd_render.h"
#include "timers.h"
#include "global.h"

#include "config_model.h"

#define HOLD_DELAY_MS      500   // tiempo antes de repetir
#define REPEAT_FAST_MS     80
#define REPEAT_SLOW_MS    200

/* ===== Descriptor UI ===== */


typedef struct
{
    const char *label;
    config_param_id_t id;
    uint16_t min;
    uint16_t max;
    uint16_t step;
} ui_param_desc_t;

/* ===== Tabla de parámetros ===== */

static const ui_param_desc_t ui_params[] = {
    { "Precio 1:", CFG_PRECIO1, 8, 1600, 100},
    { "Precio 2:", CFG_PRECIO2, 18, 3600, 100},
    { "Tiempo 1:", CFG_TIEMPO1, 10, 50, 1},
    { "Tiempo 2:", CFG_TIEMPO2, 10, 200, 1}
};

#define NUM_PARAMS  (sizeof(ui_params) / sizeof(ui_params[0]))
#define MENU_ITEMS  (NUM_PARAMS + 2)

/* ===== Estado ===== */

static st_config_t st_config;

static uint8_t cfg_menu;
static bool cfg_edit;
static bool cfg_blink;

static uint32_t cfg_blink_timer;

static uint16_t cfg_edited[NUM_PARAMS];

typedef struct
{
    uint32_t hold_start;
    uint32_t repeat_timer;
    bool active;
} btn_repeat_t;

static btn_repeat_t rep_up;
static btn_repeat_t rep_down;

/* ===== Prototipos ===== */

static void LoadConfig(void);
static void SaveConfig(void);
static void display_config_values(void);

/* ===== Entrada ===== */

void UI_Config_Init(void) {
    st_config = ST_CONFIG_IDLE;

    ConfigModel_Init();
    LoadConfig();

    cfg_menu = 0;
    cfg_edit = false;
    cfg_blink = false;

    cfg_blink_timer = Millis();

    display_config_values();
}

/* ===== Carga ===== */

static void LoadConfig(void) {
    for (uint8_t i = 0; i < NUM_PARAMS; i++) {
        cfg_edited[i] = ConfigModel_Get(ui_params[i].id);
    }
}

/* ===== Guardado ===== */

static void SaveConfig(void) {
    for (uint8_t i = 0; i < NUM_PARAMS; i++) {
        ConfigModel_Set(ui_params[i].id, cfg_edited[i]);
    }
    ConfigModel_Save();
}

/* ===== Render ===== */




static void display_config_values(void) {
    char row = 1;
    char buff[21];
    char start = (cfg_menu > 2) ? cfg_menu - 2 : 0;

    //    for (char r = 1; r <= 4; r++) {
    //        LCD_Write_Buffer(r, 1, "                    "); // 20 espacios
    //    }

    for (char i = start; i < start + 4 && i < MENU_ITEMS; i++) {

        LCD_Write_Buffer(row, 1, (cfg_menu == i) ? ">" : " ");

        if (i < NUM_PARAMS) {

            strncpy(buff, ui_params[i].label, strlen(ui_params[i].label));
            buff[strlen(ui_params[i].label)] = '\0';
            LCD_Write_Buffer(row, 2, buff);

            if (cfg_edit && cfg_menu == i)
                LCD_Write_Buffer(row, 11, cfg_blink ? " " : "*");
            else
                LCD_Write_Buffer(row, 11, " ");

            UInt16ToStr(cfg_edited[i], buff);
            Trim(buff);
            PadLeft(buff, 6, ' ');
            LCD_Write_Buffer(row, 12, buff);
        }
        else if (i == NUM_PARAMS) {
            strncpy(buff, "Guardar", 7);
            buff[7] = '\0';
            PadRight(buff, 16, ' ');
            LCD_Write_Buffer(row, 2, buff);
        }
        else {
            strncpy(buff, "Cancelar", 8);
            buff[8] = '\0';
            PadRight(buff, 16, ' ');
            LCD_Write_Buffer(row, 2, buff);
        }

        row++;
    }
    while (row <= 4) {
        LCD_Write_Buffer(row, 1, "                    ");
        row++;
    }
}

/* ===== Control ===== */

static bool ButtonRepeat(bool pressed, btn_repeat_t *r) {
    uint32_t now = Millis();

    if (!pressed) {
        r->active = false;
        return false;
    }

    if (!r->active) {
        r->active = true;
        r->hold_start = now;
        r->repeat_timer = now;
        return false; // ? NO repetir todavía
    }

    if (now - r->hold_start < HOLD_DELAY_MS)
        return false;

    uint32_t period =
            (now - r->hold_start > 2000) ? REPEAT_FAST_MS : REPEAT_SLOW_MS;

    if (now - r->repeat_timer >= period) {
        r->repeat_timer = now;
        return true;
    }

    return false;
}

void UI_Config_Contrl_Task(void) {
    if (Millis() - cfg_blink_timer >= 300) {
        cfg_blink_timer = Millis();
        cfg_blink = !cfg_blink;
    }

    /* OK */
    if (BtnD0_Event) {
        BtnD0_Event = 0;

        rep_up.active = false;
        rep_down.active = false;

        if (cfg_menu < NUM_PARAMS)
            cfg_edit = !cfg_edit;
        else if (cfg_menu == NUM_PARAMS) {
            SaveConfig();
            st_config = ST_CONFIG_EXIT;
        }
        else
            st_config = ST_CONFIG_EXIT;
    }

    /* UP */
    //bool up = BtnD2_Event || ButtonRepeat(BtnD2_IsPressed(), &rep_up);
    bool up = false;
    if (BtnD2_Event) {
        BtnD2_Event = 0;
        up = true;
        rep_up.active = false; // reinicia repetición
    }
    else if (ButtonRepeat(BtnD2_IsPressed(), &rep_up)) {
        up = true;
    }
    if (up) {
        if (cfg_edit && cfg_menu < NUM_PARAMS) {
            const ui_param_desc_t *p = &ui_params[cfg_menu];
            if (cfg_edited[cfg_menu] + p->step <= p->max)
                cfg_edited[cfg_menu] += p->step;
        }
        else if (cfg_menu > 0) {
            cfg_menu--;
            rep_up.active = false;
            rep_down.active = false;
        }
    }

    /* DOWN */
    // bool down = BtnD1_Event || ButtonRepeat(BtnD1_IsPressed(), &rep_down);
    bool down = false;
    if (BtnD1_Event) {
        BtnD1_Event = 0;
        down = true;
        rep_down.active = false;
    }
    else if (ButtonRepeat(BtnD1_IsPressed(), &rep_down)) {
        down = true;
    }
    if (down) {
        if (cfg_edit && cfg_menu < NUM_PARAMS) {
            const ui_param_desc_t *p = &ui_params[cfg_menu];
            if (cfg_edited[cfg_menu] >= p->min + p->step)
                cfg_edited[cfg_menu] -= p->step;
        }
        else if (cfg_menu < MENU_ITEMS - 1) {
            cfg_menu++;
            rep_up.active = false;
            rep_down.active = false;
        }
    }
}

/* ===== Vista ===== */

void LCD_Config_View_Task(void) {
    if (st_config == ST_CONFIG_IDLE) {
        display_config_values();
    }
    else {
        LCD_Clear_Buffer();
        st_config = ST_CONFIG_IDLE;
        App_Dispatch(EVT_APP_NONE);
    }
}