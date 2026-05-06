#ifndef DISPATCHER_H
#define	DISPATCHER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/* Origen del evento */
typedef enum {
    SRC_NONE = 0,
    SRC_APP,
    SRC_MDB,
    SRC_CREDIT,
    SRC_VEND,
    SRC_UI
} EventSource_t;

/* Evento genérico */
typedef struct {
    EventSource_t src;
    uint16_t evt;
    uint16_t param;
} DispatcherEvent_t;

/* API */
void Dispatcher_Init(void);
bool Dispatcher_Post(EventSource_t src, uint16_t evt, uint16_t param);
void Dispatcher_Task(void);


#ifdef	__cplusplus
}
#endif

#endif	/* DISPATCHER_H */

