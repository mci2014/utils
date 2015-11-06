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
    dqueue->DQUEUE_link.head = (DQUEUE_LINKAGE_TYPE *)dqueue;
    dqueue->DQUEUE_link.tail = (DQUEUE_LINKAGE_TYPE *)dqueue;
    dqueue->DQUEUE_link.nelem = 0;
}

/* See if the given queue is empty
 * @param dqueue The requested Doubly linked queue
 * @return 1 (empty)
 *         0 (not empty)
 */
int DQUEUE_empty(DQUEUE_T *dqueue) {

    assert(dqueue->DQUEUE_link.head != NULL);
    assert(dqueue->DQUEUE_link.tail != NULL);

    return (dqueue->DQUEUE_link.nelem == 0);
}
