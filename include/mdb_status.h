/* 
 * File:   mdb_status.h
 * Author: Carlos
 *
 * Created on January 3, 2026, 8:03 PM
 */

#ifndef MDB_STATUS_H
#define	MDB_STATUS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>

    typedef struct {
        // Status de control / Operacion
        uint8_t escrow_req; // 0x01 El usuario presionó la palanca de devolución.
        uint8_t pay_busy; //0x02 Pagador ocupado: El monedero está soltando monedas ahora mismo., El monedero está dispensando cambio.
        uint8_t no_credit; //0x03 Se insertó una moneda pero no se pudo validar.
        uint8_t busy; //Monedero ocupado: No puede responder comandos ahora.
        uint8_t reset; // 0x0B El monedero se reinició. Debes reconfigurarlo.

        // Status de Error Mecanico
        uint8_t tube_sensor_err; // 0x04 Sensor de tubo defectuoso: Fallo en sensores de nivel.
        uint8_t double_coin; //0x05 Dos monedas pasaron demasiado rápido por el sensor.
        uint8_t tube_jam; // 0x07   Atasco en tubo: Moneda trabada durante el pago.  
        uint8_t routing_error; // 0x09 Error de ruta: La moneda no siguió el camino previsto.
        uint8_t coin_jam; // 0x0C Atasco de moneda: Moneda trabada en la entrada.

        // STATUS HARDWARE
        uint8_t acceptor_removed; // 0x06 Aceptador desenchufado: Se ha desconectado el cabezal.
        uint8_t rom_error; // 0x08 Error de ROM: Error interno de memoria (Checksum). 
        uint8_t fraud; // 0x0D Extracción de moneda: Intento de fraude/pesca detectado.

    } mdb_status_flags_t;

    void UI_MDB_MapStatus(uint8_t status_code);
    void MDB_Status_Clear(void);

    extern mdb_status_flags_t mdb_status;


#ifdef	__cplusplus
}
#endif

#endif	/* MDB_STATUS_H */

