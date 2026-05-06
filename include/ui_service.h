
#ifndef UI_SERVICE_H
#define	UI_SERVICE_H

void UI_Service_Init(void);



void LCD_Service_Clear_Diag(void);
void UI_Service_PublishDiag(uint8_t *dataX, uint8_t len);
void UI_Service_SetModeDebug(void);
void UI_Service_Task(void);
void LCD_Service_View_Task(void);

#endif	/* UI_SERVICE_H */

