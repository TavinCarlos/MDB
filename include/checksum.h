#ifndef CHECKSUM_H
#define	CHECKSUM_H

#ifdef	__cplusplus
extern "C" {
#endif

uint8_t CalculateChecksum(const uint8_t tdata[], uint8_t n);

uint8_t ValidateChecksum(const uint8_t tdata[], uint8_t n);


#ifdef	__cplusplus
}
#endif

#endif	/* CHECKSUM_H */

