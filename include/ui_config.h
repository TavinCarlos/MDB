#ifndef LCD_CONFIG_VIEW_H
#define	LCD_CONFIG_VIEW_H




typedef enum {
    ST_CONFIG_IDLE = 0,
    ST_CONFIG_EXIT
} st_config_t;

void UI_Config_Init(void);

void UI_Config_Contrl_Task(void);

void LCD_Config_View_Task(void);

#endif	/* LCD_CONFIG_VIEW_H */

