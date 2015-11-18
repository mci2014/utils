/******************************************************************************
 *
 * @File       pool.c
 *
 * @Author     archersmind
 *
 * @Purpose    Implements a simple object pool
 *
 * Subject to The MIT License (MIT)
 * https://opensource.org/licenses/MIT
 *
 *****************************************************************************/

#include <string.h>
#include <assert.h>

#include "pool.h"

/******************************************************************************
 @Description

 Create an Object Pool

 @Input     pName     : Name of Object Pool for diagnostic purposes

 @Input     objSize      : objSize of each Object in the Pool in bytes

 @Output    ppPool    : Will contain NULL or Object Pool handle

 @Return    0 for successed others indicate error occured

*******************************************************************************/
int Pool_create(const char * pName, uint32_t objSize, Pool ** const ppPool) {

    Pool * pPool    = NULL;
    uint32_t result = 0;

    assert(pName != NULL);
    assert(ppPool != NULL);
    if (pName == NULL || ppPool == NULL) {
        // Invaild param
        result = -1;
        return result;
    }
    
    pPool = (Pool *)malloc(sizeof(Pool));

    assert(pPool != NULL);
    if (pPool == NULL) {
        // malloc failed
        result = -2;
        return result;
    }

    pPool->pName = strndup((char *)pName, strlen(pName));
    pPool->objSize = objSize;
    pPool->pBufs = NULL;
    pPool->pObjs = NULL;
    pPool->growSize = (MAX_BUF_SIZE - sizeof(struct Buffer)) / (objSize + ALIGNMENT);

    if (pPool->growSize == 0) {
        pPool->growSize = 1; 
    } else if (pPool->growSize > MAX_BUF_GROW) {
        pPool->growSize = MAX_BUF_GROW;
    }

    *ppPool = pPool;
    
    return result;
}

/*******************************************************************************

 @Description

 Delete an Object sPool. All Objects allocated from the Pool must
 be freed with Pool_free() before deleting the Object Pool.

 @Input	    pPool       : Object Pool pointer

 @Return    0 for successed others indicate error occured
********************************************************************************/
int Pool_destory(Pool * const pPool) {

    struct Buffer *pBufs    = NULL;
    struct Buffer *pTempBuf = NULL;
    uint32_t result         = 0;

    assert (pPool != NULL);
    if (pPool == NULL) {
        // Invaild param
        result = -1;
        return result;
    }

    pBufs = pPool->pBufs;
    pTempBuf = pPool->pBufs;

    while (pTempBuf != NULL) {
        pTempBuf = pBufs->pNextBuf;

        if (pPool->pBufs != NULL) {
            free(pPool->pBufs);
            pPool->pBufs = pTempBuf;
        }
    }

    if (pPool->pName != NULL) {
        free(pPool->pName);
        pPool->pName = NULL;
    }

    free(pPool);
    return result;
}

/*******************************************************************************
 @Description

 Allocate an Object from an Object sPool.

 @Input	    pPool      : Object Pool

 @Output    ppObject    : Pointer containing the handle to
                           the object created or NULL

 @Return    0 for successed others indicate error occured
*******************************************************************************/
int Pool_alloc(Pool * const pPool, void ** const ppObj) {

    struct Buffer *pBuf = NULL;
    struct Object *pObj = NULL;

    uint32_t index  = 0;
    uint32_t result = 0;

    assert(pPool != NULL);
    assert(ppObj != NULL);

    if (pPool == NULL || ppObj == NULL) {
        // Invalid param
        result = -1;
        return result;
    }

    // First call
    if (pPool->pObjs == NULL) {

        pBuf = (struct Buffer *)malloc((pPool->objSize + ALIGNMENT) * pPool->growSize
                                                             + sizeof(struct Buffer));
        assert(pBuf != NULL);
        if (pBuf == NULL) {
            // lack of memory
            result = -2;
            return result;
        }

        pBuf->pNextBuf = pPool->pBufs;
        pPool->pBufs   = pBuf;

        for(index = 0; index < pPool->growSize; index++) {
            struct Object *pObj;
            uint8_t *pTemp = NULL;

            pObj = (struct Object *)(((uint8_t *)(pBuf + 1)) +
                                    (index * (pPool->objSize + ALIGNMENT)));

            // 64bit align
            pTemp = (uint8_t *)pObj;

            // Not 64 aligned
            if ((uintptr_t)pTemp & ALIGNMENT) {
                pTemp += ((ALIGNMENT + 1) - ((uintptr_t)pTemp & ALIGNMENT));
                pObj = (struct Object*)pTemp;
            }

            pObj->pNextObj = pPool->pObjs;
            pPool->pObjs = pObj;
        }
    }

    if (pPool->pObjs == NULL) {
        // Invalid state
        result = -3;
        return result;
    }

    pObj = pPool->pObjs;
    pPool->pObjs = pObj->pNextObj;

    (*ppObj) = (void *)pObj;
    return result;
}

/*******************************************************************************
 @Description

 Free an Object previously allocated from an Object Pool.

 @Input	    pPool      : Object Pool pointer.

 @Output    hObj       : Handle to the object to be freed.

 @Return    0 for successed others indicate error occured
*******************************************************************************/
int Pool_free(Pool * const pPool, void * const hObj) {

    struct Object * pObj = NULL;
    uint32_t result = 0;

    assert(pPool != NULL);
    assert(hObj != NULL);
    if (pPool == NULL || hObj == NULL) {
        // Invalid param
        result = -1;
        return result;
    }

    pObj = (struct Object *)hObj;
    pObj->pNextObj = pPool->pObjs;
    pPool->pObjs = pObj;

    return result;
}

