/******************************************************************************
 *
 * @File       queue.c
 *
 * @Author     archersmind
 *
 * @Purpose    Implements a simple Doubly linked queue
 *
 * The MIT License (MIT)
 * https://opensource.org/licenses/MIT
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "queue.h"

/* Init the doubly linked queue
 * @param dqueue The Doubly linked queue which is allocated outside
 */
void DQUEUE_init(DQUEUE_T *dqueue) {

    // Init the doubly linked queue
    // set head & tail to itself
    dqueue->DQUEUE_link.prev = (DQUEUE_LINKAGE_TYPE *)dqueue;
    dqueue->DQUEUE_link.next = (DQUEUE_LINKAGE_TYPE *)dqueue;
    dqueue->DQUEUE_link.nelem = 0;
}

/* See if the given queue is empty
 * @param dqueue The requested Doubly linked queue
 * @return 1 (empty)
 *         0 (not empty)
 */
int DQUEUE_empty(DQUEUE_T *dqueue) {

    assert(dqueue->DQUEUE_link.prev != NULL);
    assert(dqueue->DQUEUE_link.next != NULL);

    return (dqueue->DQUEUE_link.nelem == 0);
}

/* Get the number of elements hold by the queue
 * @param dqueue The given Doubly linked queue
 * @return Number of elements that dqueue hold
 */
int DQUEUE_count(DQUEUE_T *dqueue) {
    return ((DQUEUE_LINKAGE_TYPE *)dqueue)->nelem;
}

/* Enqueue an element to the given queue descriptor
 *
 * @param dqueue the queue descriptor where to enqueue data
 *
 * @param item The data to be enqueued
 *
 * @return -1 if error happened
 */
int DQUEUE_enqueue(DQUEUE_T *dqueue, void *item) {

    assert(dqueue->DQUEUE_link.prev != NULL);
    assert(dqueue->DQUEUE_link.next != NULL);

    // See if the queue is full
    if (dqueue->DQUEUE_link.nelem >= MAX_ELEMENTS_IN_QUEUE) {
        return -1;
    }

    // See if the queue is damaged
    if (dqueue->DQUEUE_link.prev == NULL ||
            dqueue->DQUEUE_link.next == NULL) {
        return -1;
    }

    ((DQUEUE_LINKAGE_TYPE *)item)->prev = dqueue->DQUEUE_link.prev;
    ((DQUEUE_LINKAGE_TYPE *)item)->next = (DQUEUE_LINKAGE_TYPE *)dqueue;
    ((DQUEUE_LINKAGE_TYPE *)dqueue)->prev->next = ((DQUEUE_LINKAGE_TYPE *)item);
    ((DQUEUE_LINKAGE_TYPE *)dqueue)->prev = ((DQUEUE_LINKAGE_TYPE *)item);

    ((DQUEUE_LINKAGE_TYPE *)dqueue)->nelem++;

    return 0;
}

/* Dequeue an element from the given queue descriptor
 *
 * @param dqueue the queue descriptor from which to dequeue the element
 *
 * @return the element that has bee dequeued. If the queue is empty
 *  a NULL value is returned
 */
void *DQUEUE_dequeue(DQUEUE_T *dqueue) {

    DQUEUE_LINKAGE_TYPE *temp;

    assert(dqueue->DQUEUE_link.prev != NULL);
    assert(dqueue->DQUEUE_link.next != NULL);

    if (dqueue->DQUEUE_link.prev == NULL ||
            dqueue->DQUEUE_link.next == NULL) {
        return NULL;
    }

    // See if the queue is empty ?
    if (dqueue->DQUEUE_link.nelem == 0) {
        return NULL;
    }

    temp = ((DQUEUE_LINKAGE_TYPE *)dqueue)->next;
    temp->next->prev = temp->prev;
    temp->prev->next = temp->next;

    // for the safe of `orphan` remove
    temp->next = temp;
    temp->prev = temp;

    ((DQUEUE_LINKAGE_TYPE *)dqueue)->nelem--;

    return temp;
}

/* Return the first element holds in the queue
 *
 * @param dqueue the queue descriptor from which to get the first element
 *
 * @return the first element in the queue
 */
void *DQUEUE_first(DQUEUE_T *dqueue) {

    assert(dqueue->DQUEUE_link.prev != NULL);
    assert(dqueue->DQUEUE_link.next != NULL);

    // The queue is not even initialised
    if(dqueue->DQUEUE_link.prev == NULL ||
        dqueue->DQUEUE_link.next == NULL)
    {
        return NULL;
    }

    DQUEUE_LINKAGE_TYPE *temp = ((DQUEUE_LINKAGE_TYPE *)dqueue)->next;

    return temp == (DQUEUE_LINKAGE_TYPE *)dqueue ? NULL : temp;
}

/* Return the first element holds in the queue
 *
 * @param dqueue the queue descriptor from which to get the first element
 *
 * @return the first element in the queue
 */
void *DQUEUE_last(DQUEUE_T *dqueue) {

    assert(dqueue->DQUEUE_link.prev != NULL);
    assert(dqueue->DQUEUE_link.next != NULL);

    // The queue is not even initialised
    if(dqueue->DQUEUE_link.prev == NULL ||
        dqueue->DQUEUE_link.next == NULL)
    {
        return NULL;
    }

    DQUEUE_LINKAGE_TYPE *temp = ((DQUEUE_LINKAGE_TYPE *)dqueue)->prev;

    return temp == (DQUEUE_LINKAGE_TYPE *)dqueue ? NULL : temp;
}

/* Get the element that next to the item
 *
 * @param item The given item it a queue
 *
 * @return the element that next to item
 */
void *DQUEUE_next(void *item) {

    assert(((DQUEUE_LINKAGE_TYPE *)item)->prev != NULL);
    assert(((DQUEUE_LINKAGE_TYPE *)item)->next != NULL);

    // The queue is not even initialised
    if(((DQUEUE_LINKAGE_TYPE *)item)->prev == NULL ||
        ((DQUEUE_LINKAGE_TYPE *)item)->next == NULL)
    {
        return NULL;
    }

    return ((DQUEUE_LINKAGE_TYPE *)item)->next;
}
