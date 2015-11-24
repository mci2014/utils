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

The usage of this Doubly linked queue is much like the `UTIL_LIST` above. First of all, put macro `DLINK_QUEUE` at the very beginning of the struct that you want to be manipulated like a queue.

It looks like:

The `QListableStruct` could be decoded pic, input buffer (waiting for decode). Any thing that need to be served `FIFO`.

```
typedef struct Queue_Listable_Struct {

    // Make sure the DLINK_QUEUE place at the very beginning
    DLINK_QUEUE;
    int data;
} QListableStruct;
```

So place macro `DQUEUE_T` into a given struct is like putting a doubly linked queue to the struct. It's like:

```
typedef struct Test_Context {
    int data;
    DQUEUE_T dq;    
} Context;
```
Keep in my mind:

- Dequeue is always from the head enqueue is always from the tail A.K.A **FIFO**
- In an empty queue, the `prev` and `next` both pointed to the `QUEUE_T *dqueue` which is passed from outside.
- The `prev` field of the `QUEUE_T *dqueue`(treat this as `header point` which contains no data) is pointed to the tail
- The `next` field of the tail(last item in the queue) is pointed to the `header`. 

For security reasons:

When we removing an item from a queue and returning it, we should modify it's `prev` and `next` field and making them point to the item itself. **CAUSE** if uplayer has a sane item from the queue, it could abuse the `prev` and `next` fields. 

So it's better to:
```
// for the safe of `orphan` remove
temp->next = temp;
temp->prev = temp;
```
Before we return the item.

## Objects Pool

## How to



# WIP
  - [ ] Codes need validation.  
  - [ ] Fullfill how to section, maybe add some diagrams.
  - [ ] Create A better makefile 
  - [ ] Reorganize the source
