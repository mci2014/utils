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
    
    void **current = list->first;
    void *temp;
    printf ("List %p has %d items \n", list, list->count);

    while (current != NULL) {
        printf ("Current item is %p and it's elem is %d\n",
                current, ((myStruct *)current)->number);
        temp = List_next((void *)current);
        current = (*(void **)temp);
    }

}

// Using global list
static UTIL_LIST util_list;

int main() {

    int i = 0;
    // Init the list
    List_init(&util_list);

    myStruct *s = NULL;
    for (i = 0; i < 10; i++) {
        s = (myStruct *)malloc(sizeof(myStruct));
        s->number = i;
        
        List_addTail(&util_list, s);
        printf ("insert %p and it's number is %d\n", s, s->number);
    }

    // Check the list
    printListElem(&util_list); 


    return 0;
}


