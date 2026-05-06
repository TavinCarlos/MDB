#include "xc.h"
#include "app.h"
#include "botones.h"
#include "ui_service.h"
#include "ui_menu.h"
#include "ui.h"
#include "ui_config.h"
#include "global.h"
#include "dispatcher.h"

void App_Dispatch(App_Event_t evt);
void App_Task(void);


static App_State_t current_state = ST_APP_RUNING;

//static void TransitionTo(App_State_t new_state) {
//    current_state = new_state;
//}

static App_State_t FSM_App_Get_State(void) {
    return current_state;
}

const char* App_GetState(void) {
    switch (FSM_App_Get_State()) {
        case ST_APP_RUNING: return "R";
        case ST_APP_MENU: return "M";
        case ST_APP_ERROR: return "E";
        default:
            return "?";
    }
}

void App_Init(void) {

}

void App_Dispatch(App_Event_t evt) {
    switch (current_state) {
        case ST_APP_RUNING:
            break;

        case ST_APP_MENU:
            if (evt == EVT_APP_NONE) {
                current_state = ST_APP_RUNING;
            }
            break;

        case ST_APP_ERROR:
            break;
    }
    //    switch (evt) {
    //        case EVT_APP_CONFIG_SELECTED:
    //            UI_Config_OnEnter();
    //            current_state = ST_CONFIG;
    //            break;
    //        case EVT_APP_MENU_SELECTED:
    //            current_state = ST_MENU;
    //            UI_Menu_OnEnter();
    //            break;
    //        case EVT_APP_VEND_SELECTED:
    //            current_state = ST_VENDING;
    //            break;
    //        default:
    //            break;
    //    }
}

void App_Controller(void) {
    if (BtnD0_LongEvent) {
        BtnD0_LongEvent = 0;
        BtnD0_Event = 0;
        UI_Config_Init();
        current_state = ST_APP_MENU;
    }
    if (current_state == ST_APP_RUNING && BtnD0_Event) {
        BtnD0_Event = 0;        
        Dispatcher_Post(SRC_APP, EVT_MDB_DIAG_REQUEST, 0);
    }
}

void App_Task(void) {
    switch (current_state) {

        case ST_APP_RUNING:
            UI_Ctrl_Task();
            UI_View_Task();
            break;

        case ST_APP_MENU:
            UI_Config_Contrl_Task();
            LCD_Config_View_Task();
            break;

        case ST_APP_ERROR:
            break;
    }
}



//        case ST_MENU:
//            UI_Menu_Task();
//            LCD_Menu_View_Task();
//            break;
//        case ST_CONFIG:
//            UI_Config_Contrl_Task();
//            LCD_Config_View_Task();
//            break;


//typedef enum {
//    ST_VENDING = 0,
//    ST_CONFIG,
//    ST_MENU    
//} app_state_t;
//
//static app_state_t st_app;
//static app_state_t Current_state;
//
//void st_config(void);
//void st_menu(void);
//void st_vending(void);
//

//

//
//void FSM_App_Dispatch(app_event_t evt) {
//    switch (evt) {
//        case EVT_APP_VEND:
//            FSM_Global_Dispatch(EVT_GLOBAL_INIT_DONE);
//            Current_state = ST_VENDING;
//            break;
//        default:
//            break;
//    }
//}
//
//void st_vending(void) {
//    UI_Vending_Task();
//    LCD_Vending_View_Task();

//}
//
//void st_config(void) {
//    UI_Config_Task();
//    LCD_Config_View_Task();
//}
//
//void st_menu(void) {
//    UI_Menu_Task();
//    LCD_Menu_View_Task();
//}
//
//void FSM_App_Task(void) {
//    
//}
