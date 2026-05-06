
#ifndef APP_H
#define	APP_H

#include <stdint.h>
#include "mdb.h"
#include "events.h"

// #define TMR0_RELOAD (65536 - 12000)
// #define TMR0H_VAL   (TMR0_RELOAD >> 8)
// #define TMR0L_VAL   (TMR0_RELOAD & 0xFF)
    
#define TMR0H_VAL 0xD1 //  Time 1 ms
#define TMR0L_VAL 0x20 //

#define TMR1H_VAL 0x6D //  Time 25 ms
#define TMR1L_VAL 0x84 //

#define LED_MONITOR_SetDigitalInput()    do { TRISA5_bit = 1; } while(0)
#define LED_MONITOR_SetDigitalOutput()   do { TRISA5_bit = 0; } while(0)
#define LED_MONITOR_SetHigh()            do { LATA5_bit = 1; } while(0)
#define LED_MONITOR_SetLow()             do { LATA5_bit = 0; } while(0)
#define LED_MONITOR_Toggle()             do { LATA5_bit = ~LATA5_bit; } while(0)
#define LED_MONITOR_GetValue()           PORTA.B5

#define RELAY_R0_SetDigitalOutput()  do { TRISB0_bit = 0; } while(0)
#define RELAY_R0_ON()                do { LATBbits.LATB0 = 1; } while(0)
#define RELAY_R0_OFF()               do { LATBbits.LATB0 = 0; } while(0)
#define RELAY_R0_Toggle()            do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)

#define RELAY_R1_SetDigitalOutput()  do { TRISB1_bit = 0; } while(0)
#define RELAY_R1_ON()                do { LATBbits.LATB1 = 1; } while(0)
#define RELAY_R1_OFF()               do { LATBbits.LATB1 = 0; } while(0) // LATBbits.LATB1 = 0;
#define RELAY_R1_Toggle()            do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)


typedef enum {
    ST_APP_RUNING = 0,
    ST_APP_MENU,
    ST_APP_ERROR
} App_State_t;

extern volatile uint8_t Rx_data[MDB_BUFFER_SIZE];
extern volatile uint8_t received_data;

extern volatile uint8_t rx_frame_hint;

const char* App_GetState(void);

void App_Controller(void);

void App_Dispatch(App_Event_t evt);

void App_Init(void);

void App_Task(void);



#endif	/* APP_H */

