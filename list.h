/******************************************************************************
 *
 * @File       list.h
 *
 * @Author     archersmind
 *
 * @Purpose    Implements a simple linked list
 *
 * The MIT License (MIT)
 * https://opensource.org/licenses/MIT
 *
 *****************************************************************************/

#ifndef __LIST_H__
#define __LIST_H__

/**
 * If you want linked list some struct
 * Put LST_LINK the beginning of your struct
 */
#define  LINK_LIST LINKAGE_TYPE LINK_LIST

/* Type definitions */
typedef void **LINKAGE_TYPE;

#if defined (__cplusplus)
extern "C" {
#endif

typedef struct UTIL_LIST {

    int   count;
    void  **first;
    void  **last;

} UTIL_LIST ;

// Init the list
inline static void List_init(UTIL_LIST *list);

// Deinit the list
inline static void List_deinit(UTIL_LIST *list);

// Return the list element number// Return the header of the list
inline static void *List_head(UTIL_LIST *list);

// Return the tail of the list
inline static void *List_tail(UTIL_LIST *list);

// Tell if the list is empty
inline static int List_empty(UTIL_LIST *list);

// Add item to tail
inline static void List_addTail(UTIL_LIST *list, void *item);

// Add item to head
inline static void List_addHead(UTIL_LIST *list, void *item);

// Delete item from Head
inline static void *List_delFromHead(UTIL_LIST *list);

// Delete item from Tail
inline static void *List_delFromTail(UTIL_LIST *list);

// Delete a specific item
inline static void *List_del(UTIL_LIST *list, void *item);



#if defined (__cplusplus)
}
#endif

#endif

