/******************************************************************************
 *
 * @File       queue.h
 *
 * @Author     archersmind
 *
 * @Purpose    Implements a simple Doubly linked queue
 *
 * The MIT License (MIT)
 * https://opensource.org/licenses/MIT
 *
 *****************************************************************************/

#ifndef __QUEUE_H__
#define __QUEUE_H__

#if defined (__cplusplus)
extern "C" {
#endif

#define DLINK_QUEUE DQUEUE_LINKAGE_TYPE DQUEUE_link

/* Private
 * Outsider has no ideal what DQUEUE_T really is*/
typedef struct UTIL_DQUEUE {
    struct UTIL_DQUEUE *head;
    struct UTIL_DQUEUE *tail;
    int    nelem;
} DQUEUE_LINKAGE_TYPE;

typedef struct {
    DLINK_QUEUE;
} DQUEUE_T;

// Doubly queue init
void DQUEUE_init(DQUEUE_T *dqueue);

// If the queue is empty?
int DQUEUE_empty(DQUEUE_T *dqueue);



#if defined (__cplusplus)
}
#endif


#endif
