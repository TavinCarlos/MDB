#include <xc.h>
#include "ui.h"
#include "lcd_render.h"
#include "utils.h"
#include "saldo.h"
#include "events.h"
#include "mdb_link.h"
#include "global.h"
#include "botones.h"
#include "credit.h"
#include "vend.h"

typedef enum
{
    ST_UI_IDLE = 0, // "Bienvenido / Inserte Monedas"
    ST_UI_HAS_CREDIT, // "Saldo: $XX.XX"
    ST_UI_DISPENSING, // "Entregando producto... espere"
    ST_UI_OUT_OF_SERVICE// "Fuera de servicio / Mantenimiento"
} UI_State_t;

void UI_Init(void);
void UI_Dispatch(UI_Event_t evt);

void UI_View_Init(void);

static UI_State_t current_state;
static UI_State_t prev_state;

static uint16_t current_credit;
static uint16_t prev_credit;

static uint16_t ui_price = 0;
char _tmp[10];

void UI_Init(void) {
    current_state = ST_UI_OUT_OF_SERVICE;
    prev_state = ST_UI_IDLE; // forzar redraw, ui_vend_state_prev = UI_VEND_STATE_OUT_OF_SERVICE;
    current_credit = 0;
    prev_credit = 0xFFFF; // fuerza redraw    
}

static UI_State_t FSM_UI_GetState(void) {
    return current_state;
}

const char* UI_GetState(void) {
    switch (FSM_UI_GetState()) {
        case ST_UI_IDLE: return "I";
        case ST_UI_HAS_CREDIT: return "C";
        case ST_UI_DISPENSING: return "D";
        case ST_UI_OUT_OF_SERVICE: return "O";
        default:
            return "?";
    }
}

void UI_Show_MDB_Rx_Line4(const uint8_t *tx, const uint8_t *rx, uint8_t len) {
    char hex[4]; // "FF\0"
    uint8_t col = 1;

    // Limpiar renglón 4 primero // 20 espacios
    LCD_Write_Buffer(3, 1, "                    ");

    ByteToHex(tx[0], hex); // utils.c ? "FF"
    LCD_Write_Buffer(3, col, hex);
    col += 3;

    for (uint8_t i = 0; i < len && col <= 18; i++) {
        ByteToHex(rx[i], hex); // utils.c ? "FF"
        LCD_Write_Buffer(3, col, hex);
        col += 3; // espacio para "FF "
    }
}

//void UI_SetProgress(UI_Event_t evt, uint8_t value) {
//    if (evt == EVT_UI_VENDING && value > 0) {
//        char tmp[10];
//        IntToStr((int) value, tmp);
//        Trim(tmp);
//        PadLeft(tmp, 3, ' ');
//        LCD_Write_Buffer(1, 18, tmp);
//    }
//    else if (evt == EVT_UI_VENDING && value == 0) {
//        LCD_Write_Buffer(1, 18, "   ");
//    }
//}

void LCD_Write_Credit(uint16_t value) {
    IntToStr((int) (value), _tmp);
    Trim(_tmp);
    LCD_Write_Buffer(1, 10, _tmp);
}

void UI_Dispatch(UI_Event_t evt) {
    switch (evt) {
        case EVT_UI_IDLE:
            current_state = ST_UI_IDLE;
            break;

        case EVT_UI_HAS_CREDIT:
            prev_credit = current_credit;
            current_credit = Saldo_Get();
            current_state = ST_UI_HAS_CREDIT;
            LCD_Write_Buffer(1, 1, "Credito:");
            LCD_Write_Credit(current_credit);
            break;

        case EVT_UI_CREDIT_UPDATE:
            if (current_state == ST_UI_HAS_CREDIT) {
                prev_credit = current_credit;
                current_credit = Saldo_Get();
                LCD_Write_Credit(current_credit);
            }
            break;

        case EVT_UI_VENDING:
            current_state = ST_UI_DISPENSING;
            break;
        case EVT_UI_OUT_OF_SERVICE:
            current_state = ST_UI_OUT_OF_SERVICE;
            break;
    }
}

void UI_Ctrl_Task() {
    //    if (BtnD0_LongEvent) {
    //        BtnD0_LongEvent = 0;
    //        BtnD0_Event = 0;
    //        FSM_App_Dispatch(EVT_MENU); 
    //    }
}

void UI_View_Task(void) {
    if (current_state != prev_state)
        LCD_Clear_Buffer();

    if (current_state == prev_state && prev_credit == current_credit)
        return;

    switch (current_state) {
        case ST_UI_IDLE:
            LCD_Write_Buffer(1, 1, "Inserte monedas");
            break;
        case ST_UI_HAS_CREDIT:
            LCD_Write_Buffer(1, 1, "Credito:");
            IntToStr((int) current_credit, _tmp);
            Trim(_tmp);
            LCD_Write_Buffer(1, 10, _tmp);
            break;
        case ST_UI_DISPENSING:
            LCD_Write_Buffer(1, 1, "Despachando...");
            break;
        case ST_UI_OUT_OF_SERVICE:
            LCD_Write_Buffer(1, 1, "Fuera de Servicio");
            break;
    }

    prev_state = current_state;
    prev_credit = current_credit;
}

void UI_View_Credit(void) {
    static uint8_t last_sec = 0xFF;
    if (current_credit > 0) {
        uint8_t sec = Credit_GetInactivity();
        if (sec != last_sec) {
            char tmp[5];
            last_sec = sec;
            IntToStr((int) sec, tmp);
            Trim(tmp);
            PadLeft(tmp, 2, ' ');
            LCD_Write_Buffer(1, 18, tmp);
        }
    }
}
