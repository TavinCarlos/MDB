#ifndef MDB_CORE_H
#define	MDB_CORE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "mdb.h"

typedef struct {
    uint8_t rxdata[MDB_MAX_FRAME_LEN];
    uint8_t len;
    bool checksum_ok;
} mdb_frame_t;


//
//typedef enum {
//    MDB_POLL_NONE = 0,
//    MDB_POLL_ACK,
//    MDB_POLL_JUST_RESET,
//    MDB_POLL_IDLE,
//    MDB_POLL_COIN,
//    MDB_POLL_COIN_INVALID,
//    MDB_POLL_STATUS,
//    MDB_POLL_INVALID
//} mdb_poll_result_t;

void MDB_Core_Init(void);
void MDB_Core_Task(void);
bool MDB_Core_FrameAvailable(void);
mdb_frame_t* MDB_Core_GetFrame(void);
void MDB_Core_ReleaseFrame(void);


#ifdef	__cplusplus
}
#endif

#endif	/* MDB_CORE_H */

