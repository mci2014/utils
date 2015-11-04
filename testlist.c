/*****************************************************************************
*
* @File       list.c
*
* @Author     archersmind
*
* @Purpose    Implements a simple linked list
*
* The MIT License (MIT)
* https://opensource.org/licenses/MIT
*
*****************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "list.h"

// Using global list
static UTIL_LIST util_list;

typedef struct myStruct {

    LINK_LIST;
    int number;
} myStruct;

void printListElem(UTIL_LIST *list) {

    int nelem = list->nelem;
    myStruct *s = List_head(list);

    printf("\n\n **** Number of Elements (%d) ****\n\n", nelem);

    if (nelem == 0) {
        printf("(nil)\n\n");
    }

    while (s != NULL) {
        printf("|%p(%d)|-->", s, ((myStruct *)s)->number);
        s = List_next(s);

        if (s == NULL) {
            printf("(nil)\n\n");
        }
    }
}

int main() {

    int i = 0;

    //Normal case
    List_init(&util_list);

    myStruct *head = NULL;
    myStruct *tail = NULL;
    myStruct *curr = NULL;

    myStruct *s = NULL;

    // Add to tail testing
    for (i = 0; i < 10; i++) {
        s = (myStruct *)malloc(sizeof(myStruct));
        s->number = i;
        
        List_addTail(&util_list, s);
        printf ("adding %p to tail and it's number is %d\n", s, s->number);
    }

    // Check the list for tail adding
    printListElem(&util_list); 

    // Add to head testing
    for (i = 20; i >= 10; i--) {
        s = (myStruct *)malloc(sizeof(myStruct));
        s->number = i;

        List_addHead(&util_list, s);
        printf ("adding %p to head and it's number is %d\n", s, s->number);
    }

    // Check the list for head adding
    printListElem(&util_list);

    printf("Deleting from head...\n");
    // Deleting from head test
    head = List_delFromHead(&util_list);
    printf ("The item deleted from head is %p and it's number is %d\n",
            head, head->number);

    free(head);
    head = NULL;

    printf("After head has been removed");
    printListElem(&util_list);

    printf("Deleting from tail using List_del...\n");
    // Deleting from tail test
    tail = (myStruct *)List_tail(&util_list);

    List_del(&util_list, tail);
    free(tail);

    printf("After tail has been removed");
    printListElem(&util_list);


    printf("Deleting from tail using List_delFromTail...\n");
    List_delFromTail(&util_list);

    printf("After tail has been removed");
    printListElem(&util_list);

    printf("Before clear list the num of elements is %d\n", util_list.nelem);

    // Clear the list
    printf("Clear the list!! using List_delFromTail\n\n\n");
    while ((curr = List_delFromTail(&util_list)) != NULL) {
        printf ("curr is %p\n", curr);
        free(curr);
        curr = NULL;
    }

    //printf("Clear the list!! using List_delFromHead\n\n\n");
    //while ((curr = List_delFromHead(&util_list)) != NULL) {
    //     printf ("curr is %p\n", curr);
    //     free(curr);
    //     curr = NULL;
    //}

    printf("After clear the num of elements is %d\n", util_list.nelem);
    printListElem(&util_list);
    return 0;
}


