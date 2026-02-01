#include <xc.h>
#include <string.h>
#include "mdb_status.h"

mdb_status_flags_t mdb_status;

void MDB_Status_Clear(void) {
    memset(&mdb_status, 0, sizeof (mdb_status));
}

void UI_MDB_MapStatus(uint8_t status_code) {
    switch (status_code) {

            // INFO
            //  Escrow request
        case 0x01: mdb_status.escrow_req = 1;
            break; // Info
        case 0x02: mdb_status.busy = 1;
            break; // Info
        case 0x03: mdb_status.no_credit = 1;
            break; // Info

            // RESET
        case 0x0B: mdb_status.reset = 1;
            break;

            // ERROR
        case 0x04: mdb_status.tube_sensor_err = 1;
            break; // 
        case 0x06: mdb_status.acceptor_removed = 1;
            break;
        case 0x07: mdb_status.tube_jam = 1;
            break;
        case 0x08: mdb_status.rom_error = 1;
            break;
        case 0x0C: mdb_status.coin_jam = 1;
            break;

            // WARNING            
        case 0x05: mdb_status.double_coin = 1;
            break;
        case 0x09: mdb_status.routing_error = 1;
            break;
        case 0x0D: mdb_status.fraud = 1;
            break;

        case 0x0A: mdb_status.busy = 1;
            break;

        default: break;
    }
}

