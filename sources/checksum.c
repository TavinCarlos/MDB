#include <xc.h>
#include <stdint.h>

uint8_t CalculateChecksum(const uint8_t tdata[], uint8_t n) {
    uint8_t checksum = 0; // Usar 8 bits directamente
    uint8_t i;
    // sum up all bytes except the last one (thats the checksum!)
    for (i = 0; i < n - 1; i++) {
        checksum += tdata[i];
    }
    return (uint8_t) checksum;
}

uint8_t ValidateChecksum(const uint8_t tdata[], uint8_t n) {
    if (n < 2)
        return 0;
    uint8_t calculated = CalculateChecksum(tdata, n);
    uint8_t received = tdata[n - 1];

    // Comparamos lo calculado con lo recibido
    return (calculated == received);
}
