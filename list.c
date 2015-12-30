/******************************************************************************
 *
 * @File       list.c
 *
 * @Author     Alan Wang
 *
 * @Purpose    Implements a simple linked list
 *
 * The MIT License (MIT)
 * https://opensource.org/licenses/MIT
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"


/** Initialize a list descriptor
 *
 * @param list The list descriptor to initialize.
 * The user needs to allocate the list
 * @return 0  success
 *         -1 fail
 */
inline void List_init(UTIL_LIST *list) {

    list->first = NULL;
    list->last  = NULL;
    list->nelem = 0;
}

/** De-init a list descriptor
 *
 * @param list The list descriptor to de-init
 *
 */
inline void List_deinit(UTIL_LIST *list) {

    list->nelem = 0;
    list->first = NULL;
    list->last  = NULL;
}

/** Return the header of the list
 *  @param list The requested list
 */
inline void *List_head(UTIL_LIST *list) {
    return list->first;
}

/** Return the number of elements hold in the list
 *
 * @param list The requested list
 * @return the elements number
 *
 */
inline int List_nelem(UTIL_LIST *list) {
    return list->nelem;
}

/** Return the tail of the list
 *
 * @param list The requested list
 * @return the last item hold in the list
 *
 */
inline void *List_tail(UTIL_LIST *list) {
    return list->last;
}

/** Tell if the a list is empty
 *
 * @param list The requested list
 * @return 0-->Not Empty
 *         1-->Empty
 *
 */
inline UTIL_BOOL List_empty(UTIL_LIST *list) {
    return (list->first == NULL);
}

/** Add an item to the tail of the given list
 *
 * @param item The item to be added
 * @param list The list where item add to
 *
 */
inline void List_addTail(UTIL_LIST *list, void *item) {

    // Empty list
    if (list->first == NULL) {

        list->first = item;
        list->last  = item;
    } else { // list is not empty
        *(list->last) = item; // Link the item
        list->last = item;    // Update last pointer
    }

    // The linkage of the added item is set to NULL
    (*(void **)item) = NULL;
    list->nelem++;

}

/** Add an item to the head of the given list
 *
 * @param item The item to be added
 * @param list The list where item add to
 *
 */
inline void List_addHead(UTIL_LIST *list, void *item) {

    //Empty list
    if (list->first == NULL) {

        list->first = item;
        list->last  = item;
    } else { // list is not empty
        *((void **)item) = list->first; // Update the first pointer
        list->first = item; // link the first item
    }

    list->nelem++;
}

/** Return the item that next to current
 *
 * @param item The current item
 * @return The item that next to the current item
 *
 */
inline void *List_next(void *item) {
    return *((void **)item);
}

/** Delete an item from the head of the given list
 *
 * @param list The list where item deleted from
 * @return The item that be deleted from the list
 *
 */
inline void *List_delFromHead(UTIL_LIST *list) {

    void **head = list->first;

    if (head != NULL) {
        if ((list->first = *head) == NULL) {
            list->last = NULL;
        }

        list->nelem--;
    }

    return head;
}

/** Delete an item from the tail of the given list
 *
 * @param list The list where item deleted from
 * @return The item that be deleted from the list
 */
inline void *List_delFromTail(UTIL_LIST *list) {

    void **tail = list->last;
    return List_del(list, tail);
}

/** Delete a specific item from the given list
 *
 * @param list The list where item deleted from
 * @param item The item that need to be deleted
 * @return the removed item
 */
inline void *List_del(UTIL_LIST *list, void *item) {

    void **prev;
    void **curr;

    prev = list->first;
    curr = prev;

    while (curr != NULL) {
        // Found the target item
        if (curr == item) {
            *prev = *curr;

            // if it's the last item
            if (list->last == curr) {
                list->last = prev;
            }

            // if it's the last one and only one
            if (list->last == curr &&
                    list->first == curr) {
                list->last  = NULL;
                list->first = NULL;
            }

            list->nelem--;
            return item;
        }
        // Not found
        prev = curr;
        curr = *((void **)curr);
    }

    return NULL;
}
