#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "mdb.h"
#include "uart.h"
#include "timers.h"
#include "utils.h"
#include "mdb_core.h"
#include "checksum.h"

// Timeout de emergencia (NO normal) para frame roto
// MDB permite pausas, así que debe ser generoso
#define MDB_INTERBYTE_TIMEOUT_MS   10



/* ============================================================
 *  ESTADO INTERNO
 * ============================================================ */

static TimerNB_t tmr_mdb_interbyte;

static mdb_frame_t frame;
static uint8_t idx;
static bool frame_ready;

/* ============================================================
 *  INIT
 * ============================================================ */

void MDB_Core_Init(void)
{
    idx = 0;
    frame_ready = false;
}

/* ============================================================
 *  CIERRE DE FRAME
 * ============================================================ */

static void close_frame(void)
{
    frame.len = idx;
    frame.checksum_ok = ValidateChecksum(frame.rxdata, frame.len);
    frame_ready = true;
    idx = 0;
}

/* ============================================================
 *  CORE TASK
 * ============================================================ */

void MDB_Core_Task(void)
{
    while (UART_Helper_BytesAvailable())
    {
        uint8_t byte;
        uint8_t bit9;
        
        

        if (!UART_Helper_Read(&byte, &bit9))
            break;

        TimerNB_Start(&tmr_mdb_interbyte, MDB_INTERBYTE_TIMEOUT_MS);

        if (idx >= MDB_MAX_FRAME_LEN)
        {
            idx = 0;
            return;
        }

        frame.rxdata[idx++] = byte;
        
        if (bit9)
        {
            close_frame();
            UART_Helper_Flush();
            
            return;
        }

        if (idx == 1 && byte == MDB_MSG_ACK)
        {
            close_frame();
            return;
        }
    }

    // --------------------------------------------------------
    // Watchdog de emergencia (frame roto / ruido)
    // NO forma parte del protocolo normal MDB
    // --------------------------------------------------------
    if (idx > 0 && TimerNB_Expired(&tmr_mdb_interbyte))
    {
        idx = 0;   // descartar frame incompleto
        UART_Helper_Flush();
    }
}

/* ============================================================
 *  API FRAME
 * ============================================================ */

bool MDB_Core_FrameAvailable(void)
{
    return frame_ready;
}

mdb_frame_t* MDB_Core_GetFrame(void)
{
    return frame_ready ? &frame : 0;
}

void MDB_Core_ReleaseFrame(void)
{
    frame_ready = false;
}






















/*mdb_poll_result_t MDB_ParsePoll(const uint8_t *buf, uint8_t len)
{
    if((len == 3) && MDB_IS_COIN(buf[0]))
    {
        // Si no es un c?digo de estado conocido,
        // asumir que es un dep?sito de moneda (formato 2 bytes)
        // --- Parsing de Dep?sito de Moneda (4xH - 7xH) ---
        // valido checksum -> validar moneda  ejemplo --->   42 15 56
        // El bit 7 del primer byte indica si es un evento (0) o un dep?sito/payout (1)
        if (((buf[0] + buf[1]) & 0xFF) == buf[2])
        {
          return MDB_POLL_COIN;
        }
        else
        { // checksum invalido,
          return MDB_POLL_COIN_INVALID;
        }
    }
    else if((len & 1) == 0 && !MDB_IS_COIN(buf[0]))
    {
       uint8_t j;
       for (j = 0; j < len; j += 2)
        {
          if (buf[j] == buf[j + 1])
          {
            MDB_ParsePoll_Status((uint8_t *)buf[j], 2);
          }
          else
            return MDB_POLL_INVALID;
        }
        return MDB_POLL_STATUS;
    }

  return MDB_POLL_INVALID;
}*/
/*void MDB_ProcessMultiStatus(uint8_t *buf, uint8_t len)
{
  uint8_t i;

  for (i = 0; i < len; i += 2)
  {
    UI_MDB_MapStatus(buf[i]); // TU funci?n de mapeo 0x01?0x0D
  }
}*/
