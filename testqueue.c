#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

// Test context which has a queue inside
typedef struct Test_Context {
    int data;
    DQUEUE_T dq;    
} Context;

// Doubly queue listable struct, like decoded pic, input buffer etc.
typedef struct Queue_Listable_Struct {

    // Make sure the DLINK_QUEUE place at the very beginning
    DLINK_QUEUE;
    int data;
} QListableStruct;

void printQ(DQUEUE_T *dq) {

    printf ("There are %d elements in the queue %p\n",
            dq->DQUEUE_link.nelem, dq);

    QListableStruct *temp = (QListableStruct *)DQUEUE_first(dq);

    while (temp != NULL) {
        printf ("The element is %p and it's data is %d\n",
                temp, ((QListableStruct *)temp)->data);
        if (temp != DQUEUE_last(dq))
            temp = (QListableStruct *)DQUEUE_next(temp);
        else
            temp = NULL;
    }

}

int main() {

    Context tc;
    tc.data = 3;

    QListableStruct qls;
    qls.data = 1;

    QListableStruct qls2;
    qls2.data = 2;

    // Init the queue
    DQUEUE_init(&tc.dq);

    DQUEUE_enqueue(&tc.dq, &qls);
    printf (" %p enqueued .. \n", &qls);
    DQUEUE_enqueue(&tc.dq, &qls2);
    printf (" %p enqueued .. \n", &qls2);

    printQ(&tc.dq);

    // Dequeue test
    //DQUEUE_dequeue(&tc.dq);
    //DQUEUE_dequeue(&tc.dq);

    //printQ(&tc.dq);

    return 0;
}
