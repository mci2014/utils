# utils

Utils in c that working with Linux

- [x] Single linked List
- [x] Doubly linked Queue
- [ ] Message Pool
- [ ] Tree
- [ ] Hash
- [x] Pool

## Single Linked List

### How to

First of all, Add macro `LINK_LIST` at the very beginning of the struct that you want to be linkable.

```
  #define  LINK_LIST LINKAGE_TYPE LINK_LIST
  typedef void **LINKAGE_TYPE;
```

As one can see, `LINK_LIST` is defined as `(void **)`. Since `LINK_LIST` placed at the very beginning of a struct, so when we have the address(pointer) of a target struct we also have the **entry** of a linked list of this given struct.

```
    typedef struct UTIL_LIST {

        int   nelem;
        void  **first;
        void  **last;

    } UTIL_LIST ;
```

Above is what `UTIL_LIST` looks like, the tricky part is `first` and `last` is pointer to pointer, we'll use this trick implement linkage function between list items.

So, `first` and `last` is point to the actual item from a linked list. More specifically, the current `item` is typde defined as `(void **)item`, with the help of **pointer to pointer**, we can using (*(void **)item) as the `next_item` next to `item`.

So If we want to retrive the `item` next to the current, we can simply `(*(void **)current)`.



## Doubly Linked Queue

### How to

## Objects Pool

## How to



# WIP
  - [ ] Codes need validation.  
  - [ ] Fullfill how to section, maybe add some diagrams.
  - [ ] Create A better makefile 
  - [ ] Reorganize the source
