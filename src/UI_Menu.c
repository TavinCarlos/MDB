#include <xc.h>
#include "lcd_render.h"
#include "botones.h"
#include "ui_menu.h"
#include "app.h"
#include "ui.h"
#include "ui_service.h"
#include "global.h"
#include "events.h"

typedef enum {
    OPT_MENU_SERVICE = 0,
    OPT_MENU_CONFIG,
    OPT_MENU_INFO,
    OPT_MENU_RETURN
} menu_option_t;

static menu_option_t menu_option;
static menu_option_t menu_option_last;

static const char *menu_items[4] = {
    "Modo Servicio",
    "Config Param",
    "Info Sistema",
    "Salir"
};

void UI_Menu_OnEnter(void) {
    menu_option = OPT_MENU_SERVICE;
    menu_option_last = OPT_MENU_CONFIG;
}

void UI_Menu_Task(void) {
    // -------- Navegaci?n --------
    if (BtnD2_Event) { // Button UP
        BtnD2_Event = 0;
        if (menu_option == OPT_MENU_SERVICE)
            menu_option = OPT_MENU_RETURN;
        else
            menu_option--;
    }

    if (BtnD1_Event) { // DOWN
        BtnD1_Event = 0;
        if (menu_option == OPT_MENU_RETURN)
            menu_option = OPT_MENU_SERVICE;
        else
            menu_option++;
    }

    // -------- Selecci?n --------
    if (BtnD0_Event) {
        BtnD0_Event = 0;
        switch (menu_option) {
            case OPT_MENU_SERVICE: // Modo Servicio
// todo                FSM_App_Dispatch(EVT_MENU_SERVICE);
                break;
            case OPT_MENU_CONFIG:
// todo                FSM_App_Dispatch(EVT_MENU_CONFIG);
                break;
            case OPT_MENU_INFO: // 
                // puedes mostrar versi?n, fecha, etc.
                break;
            case OPT_MENU_RETURN: // Salir
                 LCD_Clear_Buffer();
                 LCD_Write_Buffer(1,1,"Reset...");
                // FSM_App_Dispatch(EVT_MENU_EXIT);
                break;
        }
    }
}

void LCD_Menu_View_Task(void) {
    if (menu_option == menu_option_last)
        return; // nada cambi?

    menu_option_last = menu_option;

    LCD_Clear_Buffer();

    for (uint8_t i = 0; i < 4; i++) {
        LCD_Write_Buffer(i + 1, 1, (menu_option == i) ? ">" : " ");
        LCD_Write_Buffer(i + 1, 3, menu_items[i]);
    }
}



