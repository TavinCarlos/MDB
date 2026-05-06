#include <xc.h>
#include "botones.h"
#include "lcd_render.h"
#include "utils.h"

#define MDB_DIAG_MAX_BYTES 6

typedef enum {
    UI_SERVICE_DEBUG = 0,
    UI_SERVICE_STATUS,
    UI_SERVICE_EXIT
} ui_services_status_t;

static uint8_t mdb_diag_buf[MDB_DIAG_MAX_BYTES];
static uint8_t mdb_diag_len = 0;
static uint8_t mdb_diag_valid = 0;

unsigned char flag_jam = 0;
unsigned char flag_tube_full = 0;
unsigned char flag_sensor_error = 0;
unsigned char flag_inhibited = 0;

static ui_services_status_t ui_service_status = UI_SERVICE_DEBUG;
static ui_services_status_t ui_service_statusPrev = 0xff;


void UI_Service_Init(void) {

}

void LCD_Service_Clear_Diag(void) {
    mdb_diag_valid = 0;
    mdb_diag_len = 0;
}

void UI_Service_PublishDiag(const uint8_t *dataX, uint8_t len) {
    uint8_t i;
    mdb_diag_len = (len > 6) ? 6 : len;
    for (i = 0; i < mdb_diag_len; i++)
        mdb_diag_buf[i] = dataX[i];
    mdb_diag_valid = 1;
}

void UI_Service_SetModeDebug(void) {
    ui_service_status = UI_SERVICE_DEBUG;
}

void UI_Service_Task(void) {

    if (BtnD2_Event) {
        BtnD2_Event = 0;
        if (ui_service_status > UI_SERVICE_DEBUG)
            ui_service_status--;
        else
            ui_service_status = UI_SERVICE_EXIT;

        //TODO     LCD_Clear();
    }

    if (BtnD1_Event) {
        BtnD1_Event = 0;
        if (ui_service_status < UI_SERVICE_EXIT)
            ui_service_status++;
        else
            ui_service_status = UI_SERVICE_DEBUG;

        //TODO         LCD_Clear();
    }

    // -------- OK (acciones futuras) --------
    if (BtnD0_Event) {
        BtnD0_Event = 0;
        switch (ui_service_status) {
            case UI_SERVICE_DEBUG:
                break;
            case UI_SERVICE_STATUS:
                break;
            case UI_SERVICE_EXIT: // Salir
            {
// todo                FSM_App_Dispatch(EVT_EXIT_TO_VENDING);
            }
                break;
        }
    }
}

void LCD_Service_View_Task(void) {
     if (ui_service_status == ui_service_statusPrev)
        return; // nada cambi?

    ui_service_statusPrev = ui_service_status;

    LCD_Clear_Buffer();
    
    switch (ui_service_status) {
        case UI_SERVICE_DEBUG:
        {
            LCD_Write_Buffer(1, 1, "MDB:");
            if (mdb_diag_valid) {
                char buf[4];
                for (uint8_t i = 0, col = 1; i < mdb_diag_len && col <= 17; i++) {
                    ByteToHex(mdb_diag_buf[i], buf);
                    LCD_Write_Buffer(1, col, buf);
                    col += 3; // "FF "
                }
            }
        }
            break;

        case UI_SERVICE_STATUS:
        {
            LCD_Write_Buffer(1, 1, "Status");
            /*if (mdb_status.jam)
     Lcd_Out(1,1,"ERROR: ATASCO");
 else if (mdb_status.sensor_error)
     Lcd_Out(1,1,"ERROR SENSOR");
 else if (mdb_status.tube_full)
     Lcd_Out(1,1,"TUBO LLENO");
 else if (mdb_status.inhibited)
     Lcd_Out(1,1,"MONEDERO INHIB");
 else
     Lcd_Out(1,1,"MONEDERO OK");*/
        }
            break;
        case UI_SERVICE_EXIT:
        {
            LCD_Write_Buffer(1, 1, "Salir");
        }
            break;
    }
}


