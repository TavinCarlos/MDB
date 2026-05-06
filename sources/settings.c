#include <xc.h>
#include "app.h"

void GPIO_Init(void) {
    // limpiamos los registros LATx
    PORTA = PORTB = PORTC = PORTD = PORTE = 0x00;

    // Configuramos los registros TRISx
    TRISA = TRISB = TRISC = TRISD = 0xff; // 8bits
    TRISE = 0x0F; // 4 bits

    // GPIO A
    TRISAbits.RA0 = 1; // BOTON PRECIO 1
    TRISAbits.RA1 = 1; // BOTON PRECIO 2
    TRISAbits.RA2 = 1; // BOTON
    TRISAbits.RA3 = 1; // BOTON
    TRISAbits.RA4 = 1; // BOTON
    TRISAbits.RA5 = 0; // LED piloto

    // GPIO B
    TRISBbits.RB0 = 0; // RELAY 0 .
    TRISBbits.RB1 = 0; // RELAY 1..
    TRISBbits.RB2 = 0; // LCD_RS..
    TRISBbits.RB3 = 0; // LCD_EN..
    TRISBbits.RB4 = 0; // LCD_D4..
    TRISBbits.RB5 = 0; // LCD_D5
    TRISBbits.RB6 = 0; // LCD_D6
    TRISBbits.RB7 = 0; // LCD_D7
    LATBbits.LATB0 = 0; // RELAY 0 EN OFF
    LATBbits.LATB1 = 0; // RELAY 1 EN OFF

    // GPIO C
    // Set the RX-TX pins to be in UART mode, not I/O
    TRISCbits.RC6 = 0; // RC6 = Tx -> Salida  UART1
    TRISCbits.RC7 = 1; // RC7 = Rx -> Entrad  UART1

    // GPIO D
    TRISDbits.RD0 = 1; // BTN_DOWN
    TRISDbits.RD1 = 1; // BTN_UP
    TRISDbits.RD2 = 1; // BTN_OK

    // GPIO E
    TRISEbits.RE0 = 0; // RE0 = Tx -> salida  SOFT_UART
    TRISEbits.RE1 = 1; // RE1 = Rx -> Entrada SOFT_UART
}

void Timer0_Init(void) {
    T0CONbits.TMR0ON = 0; // Apagar Timer0 antes de configurar
    T0CONbits.T08BIT = 0; // 16-bit timer
    T0CONbits.T0CS = 0; // Clock interno (Fosc/4)
    T0CONbits.T0SE = 0; // No aplica con clock interno
    T0CONbits.PSA = 1; // Prescaler OFF
    T0CONbits.T0PS = 0; // No importa si PSA=1

    TMR0H = TMR0H_VAL; // Preset
    TMR0L = TMR0L_VAL;

    INTCONbits.TMR0IF = 0; // Limpiar bandera
    INTCONbits.TMR0IE = 1; // Habilitar interrupción

    T0CONbits.TMR0ON = 1; // Encender Timer0 
}

// Configuración de Timer1
//Prescaler 1:8; TMR1 Preload = 28036; Actual Interrupt Time : 25 ms

void Timer1_Init(void) {
    T1CON = 0x31;
    TMR1IF = 0;
    TMR1H = TMR1H_VAL; // preset for Timer0 MSB register
    TMR1L = TMR1L_VAL; // preset for Timer0 LSB register
}

void UART1_Init_a(uint32_t baud) {
    // Solo soportamos 9600 (como MikroC)
    (void) baud;

    /* Deshabilitar módulo antes de configurar */
    RCSTAbits.SPEN = 0;
    TXSTAbits.TXEN = 0;
    RCSTAbits.CREN = 0;

    /* Configurar pines */
    TRISCbits.TRISC6 = 0; // TX salida
    TRISCbits.TRISC7 = 1; // RX entrada

    RCSTAbits.RX9 = 1; // RX9_bit = 1;   Habilitaci?n del modo de 9 bits en recepci?n
    TXSTAbits.TX9 = 1; // Habilitación del modo de 9 bits en transmisi?n

    RCSTAbits.ADDEN = 0; // ADDEN_bit = 1;   Habilitaci?n de la detecci?n de direcci?n

    TXSTAbits.SYNC = 0; // Modo asíncrono

    // 9600 baud @ 48 MHz
    // TXSTAbits.BRGH = 1;
    // BAUDCONbits.BRG16 = 1;
//    SPBRGH = 0;
//    SPBRG = 77;

    TXSTAbits.BRGH = 1; // Alta velocidad
    BAUDCONbits.BRG16 = 1; // Fosc 20Mhz, 16-bit baud generator 48Mhz
    BAUDCONbits.WUE = 0; // 

    // Cálculo del SPBRG para 9600 baudios:
    // Fórmula: SPBRG = (_XTAL_FREQ / (4 * baudrate)) - 1
    // SPBRG = (48,000,000 / (4 * 9600)) - 1 = 1249
    SPBRGH = 0x04; // (1249 >> 8);  parte alta  Baud rate 9600 (ajustar seg?n frecuencia)
    SPBRG = 0xE1; // (1249 & 0FF); parte baja
    
    /* Habilitar módulo */
    RCSTAbits.SPEN = 1; // Habilitación del puerto UART
    TXSTAbits.TXEN = 1; // Habilitación del transmisor
    RCSTAbits.CREN = 1; // Habilitaci?n de la recepci?n continua

    PIE1bits.TXIE = 0; // TX interrupt OFF    
}

void UART1_Init_c(uint32_t baud) {
    (void) baud; // Solo 9600 soportado

    /* Deshabilitar módulo antes de configurar */
    RCSTAbits.SPEN = 0;
    TXSTAbits.TXEN = 0;
    RCSTAbits.CREN = 0;

    /* Configurar pines */
    TRISCbits.TRISC6 = 0; // TX salida
    TRISCbits.TRISC7 = 1; // RX entrada

    /* Baud rate 9600 @ 48 MHz
       Modo low speed, 8-bit BRG
       Baud = Fosc / (64 * (SPBRG + 1))
       SPBRG = 77  ? 9615 bps (~0.16% error)
     */
    BAUDCONbits.BRG16 = 0; // 8-bit baud generator
    TXSTAbits.BRGH = 0; // Low speed

    SPBRGH = 0;
    SPBRG = 77;

    /* Modo asíncrono */
    TXSTAbits.SYNC = 0;

    /* Modo 9 bits (MDB) */
    TXSTAbits.TX9 = 1;
    RCSTAbits.RX9 = 1;

    /* Modo multiprocesador (recomendado para MDB) */
    RCSTAbits.ADDEN = 1;

    /* Habilitar módulo */
    RCSTAbits.SPEN = 1;
    TXSTAbits.TXEN = 1;
    RCSTAbits.CREN = 1;

    /* Deshabilitar interrupción TX si no se usa */
    PIE1bits.TXIE = 0;
}

