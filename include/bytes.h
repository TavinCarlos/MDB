
#ifndef BYTES_H
#define	BYTES_H

#define LO_BYTE(x)   ((uint8_t)((x) & 0xFF))
#define HI_BYTE(x)   ((uint8_t)(((x) >> 8) & 0xFF))

#endif	/* BYTES_H */

