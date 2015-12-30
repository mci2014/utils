/******************************************************************************
 *
 * @File       pool.h
 *
 * @Author     Alan Wang
 *
 * @Purpose    Implements a simple object pool
 *
 * Subject to The MIT License (MIT)
 * https://opensource.org/licenses/MIT
 *
 *****************************************************************************/
#ifndef __POOL_H__
#define __POOL_H__

#include "util_error_n_types.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


#define MAX_BUF_SIZE 8192
#define MAX_BUF_GROW 32

// 64 bits alignment
#define ALIGNMENT (sizeof(long long) - 1)

#if defined (__cplusplus)
    extern "C" {
#endif

struct Buffer {
    struct Buffer *pNextBuf;
};

struct Object {
    struct Object *pNextObj;
};

typedef struct Pool {

    char *pName;
    uint32_t objSize;                        //size of each object in the pool
    uint32_t growSize;
    struct Buffer *pBufs;
    struct Object *pObjs;
} Pool;

// Pool Create
UTIL_RESULT Pool_create(const char * pName, uint32_t objSize, Pool ** const ppPool);

// Pool destory
UTIL_RESULT Pool_destory(Pool * const pPool);

// Alloc object from the pool
UTIL_RESULT Pool_alloc(Pool * const pPool, void **const ppObj);

// Free object from the pool
UTIL_RESULT Pool_free(Pool * const pPool, void * const pObj);

#if defined (__cplusplus)
}
#endif

#endif
