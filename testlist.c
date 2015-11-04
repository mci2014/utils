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

typedef struct myStruct {

    LINK_LIST;
    int number;
} myStruct;

void printListElem(UTIL_LIST *list) {

    myStruct *s = List_head(list);
    while (s != NULL) {
        printf ("Current item is %p and it's elem is %d\n",
                s, ((myStruct *)s)->number);
        s = List_next(s);
    }
}

// Using global list
static UTIL_LIST util_list;

int main() {

    int i = 0;
    // Init the list
    List_init(&util_list);

    myStruct *s = NULL;
    myStruct *head = NULL;
    myStruct *tail = NULL;
    myStruct *temp = NULL;


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

    printf("currently list %p has %d elements\n", &util_list, util_list.nelem);

    // Deleting from head test
    head = List_delFromHead(&util_list);
    printf ("The item deleted from head is %p and it's number is %d\n",
            head, head->number);

    free(head);
    head = NULL;

    // Deleting from tail test
    tail = (myStruct *)List_tail(&util_list);
    printf ("The item deleted from tail is %p and it's number is %d\n",
            tail, tail->number);

    List_del(&util_list, tail);
    free(tail);

    printListElem(&util_list);


    printf("Deleting from tail!!!\n\n");

    List_delFromTail(&util_list);
    printListElem(&util_list);

    printf("Before clear list the num of elements is %d\n", util_list.nelem);
    // Clear the list
    printf("Clear the list!!\n\n\n");

    myStruct* curr;
    while ((curr = List_delFromTail(&util_list)) != NULL) {
        printf ("curr is %p\n", curr);
        free(curr);
        curr = NULL;
    }

    //while ((curr = List_delFromHead(&util_list)) != NULL) {
    //     printf ("curr is %p\n", curr);
    //     free(curr);
    //     curr = NULL;
    //}

    printf("After clear the num of elements is %d\n", util_list.nelem);
    printListElem(&util_list);
    return 0;
}


