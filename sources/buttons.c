#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <pic18f4550.h>
#include "botones.h"
#include "utils.h"
#include "timers.h"


// ================= CONFIGURACIÓN =================
#define BTN_A0   PORTAbits.RA0
#define BTN_A1   PORTAbits.RA1
#define BTN_A2   PORTAbits.RA2

#define BTN_OK    PORTDbits.RD0   // OK en D0, activo en 0
#define BTN_DOWN  PORTDbits.RD1   // OK en D1, activo en 0
#define BTN_UP    PORTDbits.RD2   // OK en D2, activo en 0
// =================================================

// ====== EVENTOS (extern en buttons.h)  ======
volatile bool BtnA0_Event;
volatile bool BtnA1_Event;
volatile bool BtnA2_Event;

volatile bool BtnD0_Event;
volatile bool BtnD1_Event;
volatile bool BtnD2_Event;

volatile bool BtnD0_LongEvent;


// ====== VARIABLES INTERNAS ======
static bool rA0_last, rA1_last, rA2_last;
static bool rD0_last, rD1_last, rD2_last;

static bool btnA0_lock, btnA1_lock, btnA2_lock;
static bool btnD0_lock, btnD1_lock, btnD2_lock;

static bool rd1_pressed;
static bool rd2_pressed;

static uint32_t ok_press_start = 0;
static uint8_t ok_long_sent = 0;


static TimerNB_t btnA0_timer;
static TimerNB_t btnA1_timer;
static TimerNB_t btnA2_timer;
static TimerNB_t btnD0_timer;
static TimerNB_t btnD1_timer;
static TimerNB_t btnD2_timer;

// -------------------------------------------------

void Buttons_Init(void) {
    // Eventos
    BtnA0_Event = BtnA1_Event = BtnA2_Event = 0;
    BtnD0_Event = BtnD1_Event = BtnD2_Event = 0;
    BtnD0_LongEvent = 0;

    // Locks
    btnA0_lock = btnA1_lock = btnA2_lock = 0;
    btnD0_lock = btnD1_lock = btnD2_lock = 0;

    ok_long_sent = 0;
    ok_press_start = 0;

    // PORTA como digital
    ADCON1 = 0x0F;
    CMCON = 0x07;

    // Entradas
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA2 = 1;
    TRISDbits.TRISD0 = 1;
    TRISDbits.TRISD1 = 1;
    TRISDbits.TRISD2 = 1;

    // Estado Inicial Real (pull-up)
    rA0_last = BTN_A0;
    rA1_last = BTN_A1;
    rA2_last = BTN_A2;

    rD0_last = BTN_OK;
    rD1_last = BTN_DOWN;
    rD2_last = BTN_UP;

    rd1_pressed = false;
    rd2_pressed = false;
}

// -------------------------------------------------

void Buttons_Task(void) {
    bool ra0, ra1, ra2;
    bool rd0, rd1, rd2;

    ra0 = BTN_A0;
    ra1 = BTN_A1;
    ra2 = BTN_A2;

    rd0 = BTN_OK;
    rd1 = BTN_DOWN;
    rd2 = BTN_UP;

    // -------- RA0 --------
    if (!btnA0_lock && rA0_last && !ra0) {
        btnA0_lock = 1;
        BtnA0_Event = 1;
        TimerNB_Start(&btnA0_timer, BTN_DEBOUNCE_MS);
    }
    if (btnA0_lock && TimerNB_Expired(&btnA0_timer))
        btnA0_lock = 0;

    // -------- RA1 --------
    if (!btnA1_lock && rA1_last && !ra1) {
        btnA1_lock = 1;
        BtnA1_Event = 1;
        TimerNB_Start(&btnA1_timer, BTN_DEBOUNCE_MS);
    }
    if (btnA1_lock && TimerNB_Expired(&btnA1_timer))
        btnA1_lock = 0;

    // -------- RA2 --------
    if (!btnA2_lock && rA2_last && !ra2) {
        btnA2_lock = 1;
        BtnA2_Event = 1;
        TimerNB_Start(&btnA2_timer, BTN_DEBOUNCE_MS);
    }
    if (btnA2_lock && TimerNB_Expired(&btnA2_timer))
        btnA2_lock = 0;

    // -------- RD0 (OK) --------
    if (!btnD0_lock && rD0_last && !rd0) {
        btnD0_lock = 1;
        BtnD0_Event = 1;
        ok_press_start = Millis();
        ok_long_sent = 0;
        TimerNB_Start(&btnD0_timer, BTN_DEBOUNCE_MS);
    }

    if (btnD0_lock && !rd0) {
        if (!ok_long_sent && (Millis() - ok_press_start >= 3000)) {
            BtnD0_LongEvent = 1;
            BtnD0_Event = 0;
            ok_long_sent = 1;
        }
    }

    if (btnD0_lock && rd0 && TimerNB_Expired(&btnD0_timer)) {
        btnD0_lock = 0;
        BtnD0_LongEvent = 0;
    }

    // -------- RD1 --------
    if (!btnD1_lock && rD1_last && !rd1) {
        btnD1_lock = 1;
        BtnD1_Event = 1;
        TimerNB_Start(&btnD1_timer, BTN_DEBOUNCE_MS);
    }
    if (btnD1_lock && TimerNB_Expired(&btnD1_timer))
        btnD1_lock = 0;

    // -------- RD2 --------
    if (!btnD2_lock && rD2_last && !rd2) {
        btnD2_lock = 1;
        BtnD2_Event = 1;
        TimerNB_Start(&btnD2_timer, BTN_DEBOUNCE_MS);
    }
    if (btnD2_lock && TimerNB_Expired(&btnD2_timer))
        btnD2_lock = 0;

    // Guardar estados
    rA0_last = ra0;
    rA1_last = ra1;
    rA2_last = ra2;
    rD0_last = rd0;
    rD1_last = rd1;
    rD2_last = rd2;
    
    rd1_pressed = (rd1 == 0); // activo en 0
    rd2_pressed = (rd2 == 0);
}

bool BtnD1_IsPressed(void) {
    return rd1_pressed;
}

bool BtnD2_IsPressed(void) {
    return rd2_pressed;
}


