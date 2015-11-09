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

// The MAX elements in a queue
#define MAX_ELEMENTS_IN_QUEUE 10

/* Private
 * Outsider has no ideal what DQUEUE_T really is*/
typedef struct UTIL_DQUEUE {
    struct UTIL_DQUEUE *prev;
    struct UTIL_DQUEUE *next;
    int    nelem;
} DQUEUE_LINKAGE_TYPE;

typedef struct {
    DLINK_QUEUE;
} DQUEUE_T;

// Doubly linked queue init
void DQUEUE_init(DQUEUE_T *dqueue);

// If the queue is empty?
int DQUEUE_empty(DQUEUE_T *dqueue);

// The number of the elements in queue
int DQUEUE_count(DQUEUE_T *dqueue);

// Enqueue(to tail) a item to the given queue
int DQUEUE_enqueue(DQUEUE_T *dqueue, void *item);

// Dequeue(from head) a item from the given queue
void *DQUEUE_dequeue(DQUEUE_T *dqueue);

// Return the first element in the queue
void *DQUEUE_first(DQUEUE_T *dqueue);

// Return the last element in the queue
void *DQUEUE_last(DQUEUE_T *dqueue);

// Return the element that next to item
void *DQUEUE_next(void *item);

#if defined (__cplusplus)
}
#endif

#endif
