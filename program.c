#include <xc.h>
#include <builtins.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "program.h"
#include "timers.h"
#include "app.h"
#include "botones.h"
#include "hal_uart.h"
#include "eeprom.h"
#include "events.h"
#include "mdb.h"
#include "mdb_core.h"
#include "global.h"
#include "credit.h"
#include "vend.h"
#include "lcd_render.h"
#include "uart.h"
#include "timers.h"
#include "lcd_hal.h"
#include "ui.h"
#include "ui_menu.h"
#include "utils.h"
#include "settings.h"
#include "mdb_link.h"
#include "dispatcher.h"
#include "datos_venta.h"
#include "vend.h"
#include "saldo.h"

// const char* App_GetState(void);
// const char* Global_GetState(void);
const char* UI_GetState(void);

#define TMR0H_VAL  0xD1 //  Timer0 a  1 ms 
#define TMR0L_VAL  0x20 //              

#define TMR1H_VAL  0x6D //  Timer1 a 25 ms 
#define TMR1L_VAL  0x84 //             

volatile uint8_t Rx_data[MDB_BUFFER_SIZE];
volatile uint8_t RX_mode[MDB_BUFFER_SIZE];
volatile uint8_t received_data = 0;
volatile uint8_t rx_frame_hint = 0;

volatile unsigned int Timer0_Counter = 0; // 0 .. 65535
volatile unsigned int Timer1_Counter = 0;
volatile uint32_t timer0_millis = 0;

// Global variable for interrupt flag
volatile unsigned char timer0_flag = 0;
volatile unsigned char timer1_flag = 0; // 1-ms flag

void __interrupt() ISR(void) {
    /* ---------- TIMER0 ---------- */
    if (INTCONbits.TMR0IF) {
        INTCONbits.TMR0IF = 0; // Clear flag
        TMR0H = TMR0H_VAL; // Reload Timer0
        TMR0L = TMR0L_VAL;
        timer0_millis++;
        Timer0_Counter++;
    }

    /* ---------- TIMER1 ---------- */
    if (PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0; // Clear flag
        TMR1H = TMR1H_VAL;
        TMR1L = TMR1L_VAL;
        Timer1_Counter++;
    }

    /* ---------- UART RX ---------- */
    if (PIR1bits.RCIF) {
        uint8_t mode;
        uint8_t dato;
         LATAbits.LA5 = ~LATAbits.LA5;
        
        /* Overrun error: limpiar antes de leer */
        if (RCSTAbits.OERR) {
            RCSTAbits.CREN = 0;
            RCSTAbits.CREN = 1;
            return;
        }

        /* Capturar bit 9 (MDB mode) */
        mode = RCSTAbits.RX9D ? 1 : 0;

        /* Leer dato (limpia RCIF) */
        dato = RCREG;

        /* Framing error: descartar */
        if (RCSTAbits.FERR) {
            return;
        }
        
       

        /* Guardar byte */
        if (received_data < MDB_BUFFER_SIZE) {
            Rx_data[received_data] = dato;
            RX_mode[received_data] = mode;
            received_data++;
        }
        else {
            // Buffer lleno ? decidir política
            // received_data = 0;
        }
    }
}

void main(void) {

    ADCON1 = 0x0F; // Configure AN pins as digital
    CMCON = 0x07; // Turn off comparators

    GPIO_Init(); // Inicializa los puertos de etnrada/salida
    Timer0_Init(); // Inicializa el Timer 0
    Timer1_Init(); // Inicializa el Timer 1

    // UART1_Init_a(9600); // primero UART1_Init(9600)
    
    UART1_Init_c(9600); // primero UART1_Init(9600)

    // Habilitar interrupción UART RX
PIR1bits.RCIF = 0;     // Limpiar flag
IPR1bits.RCIP = 1;     // Prioridad alta (recomendado)
PIE1bits.RCIE = 1;     // Habilitar RX interrupt

    UART_Helper_Init(); // Lee los bytes del UART (Rx_data, Rx_mode)
    for (uint8_t k = 0; k < 255; k++) __delay_ms(1); // Espera a que el modulo UART se estabilice

    LCD_HAL_Init(); // (Hardware) Driver para el LCD
    LCD_FSM_Init(); // (Software) Controlador FSM - LCD_Write_Buffer
    for (uint8_t k = 0; k < 255; k++) __delay_ms(1);
    
    DatosVenta_Init();
    Global_Init();
    App_Init();
    MDB_Core_Init(); // Construye un frame MDB con los bytes del UART
    MDB_Link_Init(); // Controlador principal MDB (Comandos y Respuestas)
    Credit_Init();
    Vend_Init();
    Saldo_Init();
    Buttons_Init(); // Inicializa el controlador de Botones
    UI_Init(); // LCD_Vending   UI_Vending
   
    Dispatcher_Init();

    for (uint8_t k = 0; k < 255; k++) __delay_ms(1);


    // 1. Configurar el modo de interrupciones
    RCONbits.IPEN = 1; // Habilita niveles de prioridad
    // 2. Configurar prioridades específicas (Si no lo haces, por defecto son HIGH)    
    INTCON2bits.TMR0IP = 1; // Timer0 prioridad alta (opcional)
    IPR1bits.TMR1IP = 0; // Timer1 prioridad baja (opcional)
    // 3. Habilitar los permisos locales (los "switches" de cada timer)
    INTCONbits.TMR0IF = 0; // Limpiar bandera antes de habilitar
    INTCONbits.TMR0IE = 1; // Habilita Timer0
    PIR1bits.TMR1IF = 0; // Limpiar bandera antes de habilitar
    PIE1bits.TMR1IE = 1; // Habilita Timer1
    // 4. Habilitar los permisos de grupo
    INTCONbits.GIEL = 1; // Habilita todas las interrupciones de prioridad BAJA (PEIE)
    INTCONbits.GIEH = 1; // Habilita todas las interrupciones de prioridad ALTA (GIE)

    while (1) {
        
//        if (PIR1bits.RCIF)
//{
//    LATAbits.LA5 = ~LATAbits.LA5;
//    volatile uint8_t dummy = RCREG;
//}
        
        MDB_Core_Task(); // construye un frame MDB con los bytes del UART

        MDB_Link_Task_Command(); // Tareas del protocolo MDB utilizando el frame 
        MDB_Link_Task_Response(); // Tareas del protocolo MDB utilizando el frame 

        Credit_Task(); // Manejo de monedas / Tubos
        Vend_Task(); // Controla el proceso de Venta
        // Global_Task(); // Vending / UI
        Dispatcher_Task();
        
        Buttons_Task(); // Monitorea Botones y genera Evento de Boton        

        App_Controller();
        App_Task(); // Controlador para Vending/Menu/Config/Service

        LCD_Render_Task(); // Driver LCD, escribe el uffer en el LCD

        if (Timer0_Counter > 2000) {
            UI_View_Credit();
            // const char* ptr;
            Timer0_Counter = 0; // Clear the 1-second flag
            if (1) {
                char _tmp[10];
                MDB_Link_State_t _mdb_link_state = MDB_Link_GetState();
                IntToStr((int) _mdb_link_state, _tmp);
                Trim(_tmp);
                LCD_Write_Buffer(4, 1, _tmp);
                LCD_Write_Buffer(4, 4, Global_GetState());
                LCD_Write_Buffer(4, 6, App_GetState());                
                LCD_Write_Buffer(4, 8, Credit_GetState());
                LCD_Write_Buffer(4, 10, Vend_GetState());
                LCD_Write_Buffer(4, 12, UI_GetState());
            }
            // LATAbits.LA5 = ~LATAbits.LA5;
        }
    }
}













