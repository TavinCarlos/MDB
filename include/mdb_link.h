#ifndef FSM_MDB_LINK_H
#define	FSM_MDB_LINK_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "events.h"
#include "mdb.h"
#include "mdb_core.h"

    typedef enum {
        ST_MDB_RESET = 0, // Reset 0x08
        ST_MDB_RESET_WAIT,
        ST_MDB_JUST_RESET,
        ST_MDB_JUST_RESET_WAIT, // Esperando Just Reset (0x0B 0x0B)
        ST_MDB_SETUP,
        ST_MDB_SETUP_WAIT,
        ST_MDB_EXP_ID,
        ST_MDB_EXP_ID_WAIT,
        ST_MDB_EXP_FEATURE,
        ST_MDB_EXP_FEATURE_WAIT,
        ST_MDB_EXP_DIAGNOSTIC,
        ST_MDB_EXP_DIAGNOSTIC_WAIT,
        ST_MDB_EXP_DIAG_STATUS,
        ST_MDB_EXP_DIAG_STATUS_WAIT,
        ST_MDB_TUBE_STATUS,
        ST_MDB_TUBE_STATUS_WAIT,
        ST_MDB_ENABLE_COINS,
        ST_MDB_ENABLE_COINS_WAIT,
        ST_MDB_DISBLE_COINS,
        ST_MDB_DISABLE_COINS_WAIT,
        ST_MDB_POLL, // Operación normal (polling)
        ST_MDB_POLL_WAIT,
        ST_MDB_REFUND,
        ST_MDB_ERROR, // Error grave / fuera de servicio
        ST_MDB_WAIT
    } MDB_Link_State_t;

    typedef struct {
        uint8_t Tx[7];
        uint8_t Tx_len;
        uint8_t Rx[ MDB_LOG_MAX ];
        uint8_t Rx_len;
        uint8_t Valid;
    } MDB_Log_t;

    MDB_Link_State_t MDB_Link_GetState(void);
    void MDB_Link_Dispatch(MDB_Event_t evt, uint16_t param0);
    void MDB_Link_Init(void);
    // mdb_event_t MDB_ParsePollFrame(const uint8_t *buf, uint8_t len);
    //    void FSM_MDB_Link_RequestRefund(uint8_t x);
    // void FSM_MDB_Link_Send_Command(uint8_t command, uint8_t subCommand);
    
    void MDB_Link_Task_Command(void);
    
    void MDB_Link_Task_Response(void);

    extern volatile uint8_t mdb_diag_ready;
    extern volatile uint8_t mdb_diag_error;

#ifdef	__cplusplus
}
#endif

#endif	/* FSM_MDB_LINK_H */

