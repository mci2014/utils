/******************************************************************************
 *
 * @File       list.h
 *
 * @Author     Alan Wang
 *
 * @Purpose    Implements a simple linked list
 *
 * The MIT License (MIT)
 * https://opensource.org/licenses/MIT
 *
 *****************************************************************************/

#ifndef __LIST_H__
#define __LIST_H__

#if defined (__cplusplus)
extern "C" {
#endif

#include "util_error_n_types.h"

/**
 * If you want linked list some struct
 * Put LST_LINK the beginning of your struct
 */
#define  LINK_LIST LINKAGE_TYPE LINK_LIST

/* Private */
/* Outsider have no ideal what LINK_LIST really is */
typedef void **LINKAGE_TYPE;

typedef struct UTIL_LIST {

    int   nelem;
    void  **first;
    void  **last;

} UTIL_LIST ;

// Init the list
inline void List_init(UTIL_LIST *list);

// Deinit the list
inline void List_deinit(UTIL_LIST *list);

// Return the list element number// Return the header of the list
inline void *List_head(UTIL_LIST *list);

// Return the tail of the list
inline void *List_tail(UTIL_LIST *list);

// Tell if the list is empty
inline UTIL_BOOL List_empty(UTIL_LIST *list);

// Add item to tail
inline void List_addTail(UTIL_LIST *list, void *item);

// Add item to head
inline void List_addHead(UTIL_LIST *list, void *item);

// Get next item
inline void *List_next(void *item);

// Delete item from Head
inline void *List_delFromHead(UTIL_LIST *list);

// Delete item from Tail
inline void *List_delFromTail(UTIL_LIST *list);

// Delete a specific item
inline void *List_del(UTIL_LIST *list, void *item);



#if defined (__cplusplus)
}
#endif

#endif

