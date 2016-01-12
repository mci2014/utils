/*****************************************************************************
*
* @File       hash.c
*
* @Author     Alan Wang
*
* @Purpose    Self scaling hash tables.
*
* The MIT License (MIT)
* https://opensource.org/licenses/MIT
*
*****************************************************************************/
#include <assert.h>

#include "hash.h"

#include "pool.h"

static UTIL_BOOL gbInitialised = UTIL_FALSE;

// pool of struct hash objects
static struct Pool * gpHashPool = NULL;

// pool of struct Bucket objects
static struct Pool * gpBucketPool = NULL;

/*!
******************************************************************************

 @Function				hashFunc

 @Description

 Hash function intended for hashing addresses.

 @Input	    ui64Vale    : The key to hash.

 @Input	    ui32Size    : The size of the hash table

 @Return    ui32Hash	: The hash value.

*******************************************************************************/
static uint32_t hashFunc(
    uint64_t ui64Vale,
    uint32_t ui32Size)
{
	uint32_t ui32Hash = (uint32_t)(ui64Vale);
	ui32Hash += (ui32Hash << 12);
	ui32Hash ^= (ui32Hash >> 22);
	ui32Hash += (ui32Hash << 4);
	ui32Hash ^= (ui32Hash >> 9);
	ui32Hash += (ui32Hash << 10);
	ui32Hash ^= (ui32Hash >> 2);
	ui32Hash += (ui32Hash << 7);
	ui32Hash ^= (ui32Hash >> 12);
	ui32Hash &= (ui32Size-1);
	return ui32Hash;
}

/*!
******************************************************************************

 @Function				hashInsert

 @Description

 Insert an intem to the Hash table.

 @Input	    pBucket    : The sBucket

 @Input	    ppTable    : The hash table

 @Input	    ui32Size    : The size of the hash table

 @Return    UTIL_RESULT  : UTIL_SUCCESS or an error code.

********************************************************************************/
static UTIL_RESULT hashInsert(
        struct sBucket * pBucket,
        struct sBucket ** ppsTable,
        uint32_t ui32Size) {

    UTIL_RESULT res = UTIL_SUCCESS;
    uint32_t ui32Index;

    assert(pBucket  != NULL);
    assert(ppsTable != NULL);
    assert(ui32Size != 0);

    if (pBucket == NULL ||
        ppsTable == NULL ||
        ui32Size == 0) {
        res = -UTIL_ERROR_INVALID_PARAMETERS;
        return res;
    }

    ui32Index = hashFunc(pBucket->u64Key, ui32Size);

    assert(ui32Index <= ui32Size);

    if (ui32Index > ui32Index) {
        res = -UTIL_ERROR_FATAL;
        return res;
    } else {
        res = UTIL_SUCCESS;
        pBucket->pNext = ppsTable[ui32Index];
        ppsTable[ui32Index] = pBucket;
    }

    return res;
}

/*!
******************************************************************************

 @Function				hashRehash

 @Description

 Iterate over every entry in an old hash table and rehash into the new table.

 @Input	    ppsOldTable : The old hash table

 @Input	    ui32OldSize : The size of the old hash table

 @Input	    ppsNewTable : The new hash table

 @Input	    ui32NewSize : The size of the new hash table

 @Return    UTIL_RESULT  : UTIL_SUCCESS or an error code.

********************************************************************************/

static UTIL_RESULT hashRehash(
        struct sBucket ** ppsOldTable,
        uint32_t ui32OldSize,
        struct sBucket ** ppsNewTable,
        uint32_t ui32NewSize) {

    UTIL_RESULT res    = UTIL_SUCCESS;
    uint32_t ui32Index = 0;

    assert(ppsOldTable != NULL);
    assert(ppsNewTable != NULL);

    if (ppsOldTable == NULL ||
            ppsNewTable == NULL) {
        res = -UTIL_ERROR_INVALID_PARAMETERS;
        return res;
    }

    for (ui32Index = 0; ui32Index < ui32OldSize; ui32Index++) {

        struct sBucket *pCurrent;
        struct sBucket *pNext;

        pCurrent = ppsOldTable[ui32Index];
        while (pCurrent != NULL) {
            pNext = pCurrent->pNext;
            res = hashInsert(pCurrent, ppsNewTable, ui32NewSize);
            assert(res == UTIL_SUCCESS);
            if (res != UTIL_SUCCESS) {
                return res;
            }
            pCurrent = pNext;
        }
    }

    return res;
}

static UTIL_RESULT hashResize(
        struct sHash * psHash,
        uint32_t ui32NewSize) {

    UTIL_RESULT res = UTIL_SUCCESS;

    assert (psHash != NULL);
    if (psHash == NULL) {
        res = -UTIL_ERROR_INVALID_PARAMETERS;
        return res;
    }

    if (ui32NewSize == psHash->ui32Size)
        return res;

    while (ui32NewSize != psHash->ui32Size) {

        struct sBucket ** ppNewTable;
        ppNewTable = (struct sBucket **)
                        malloc(sizeof(struct sBucket *) * ui32NewSize);

        assert(ppNewTable != NULL);
        if (!ppNewTable) {
            res = -UTIL_ERROR_MALLOC_FAILED;
            break;
        }

        if (ppNewTable != NULL) {
            uint32_t ui32Index;

            for (ui32Index = 0; ui32Index < ui32NewSize; ui32Index++) {
                ppNewTable[ui32Index] = NULL;
            }

            res = hashRehash(psHash->ppsTable,
                             psHash->ui32Size,
                             ppNewTable,
                             ui32NewSize);

            if (res != UTIL_SUCCESS) {
                free(ppNewTable);
                ppNewTable = NULL;
                res = -UTIL_ERROR_UNEXPECTED_STATE;
                break;
            } else {
                if (psHash->ppsTable) {
                    free(psHash->ppsTable);
                    psHash->ppsTable = NULL;
                }
                psHash->ui32Size = ui32NewSize;
                psHash->ppsTable = ppNewTable;
                res = UTIL_SUCCESS;
                break;
            }
        }
    }

    return res;
}

UTIL_RESULT HASH_Init() {

    UTIL_RESULT res = UTIL_SUCCESS;
    assert(gbInitialised == UTIL_FALSE);

    if (gbInitialised == UTIL_TRUE) {
        res = -UTIL_ERROR_ALREADY_INITIALISED;
        return res;
    }

    while (!gbInitialised) {
        assert(gpHashPool == NULL);
        assert(gpBucketPool == NULL);

        if (gpHashPool != NULL ||
                gpBucketPool != NULL) {
            res = -UTIL_ERROR_UNEXPECTED_STATE;
            break;
        }

        res = Pool_create("hash", sizeof(struct sHash), &gpHashPool);
        assert (res == UTIL_SUCCESS);
        if (res != UTIL_SUCCESS) {
            res = -UTIL_ERROR_UNEXPECTED_STATE;
            break;
        }

        res = Pool_create("bucket", sizeof(struct sBucket), &gpBucketPool);
        assert (res == UTIL_SUCCESS);
        if (res != UTIL_SUCCESS) {
            res = -UTIL_ERROR_UNEXPECTED_STATE;
            break;
        } else {
            gbInitialised = UTIL_TRUE;
            res = UTIL_SUCCESS;
            break;
        }
    }

    return res;
}

UTIL_RESULT HASH_Deinit() {

    UTIL_RESULT res = UTIL_SUCCESS;
    assert(gbInitialised == UTIL_TRUE);

    if (gbInitialised == UTIL_FALSE) {
        res = -UTIL_ERROR_NOT_INITIALISED;
        return res;
    }

    while (gbInitialised) {
        if (gpHashPool) {
            res = Pool_destory(gpHashPool);
            assert(res == UTIL_SUCCESS);

            if (res != UTIL_SUCCESS) {
                res = -UTIL_ERROR_UNEXPECTED_STATE;
                break;
            }
        }

        if (gpBucketPool) {
            res = Pool_destory(gpBucketPool);
            assert(res == UTIL_SUCCESS);

            if (res != UTIL_SUCCESS) {
                res = -UTIL_ERROR_UNEXPECTED_STATE;
                break;
            }
        }
        break;
    }

    gbInitialised = UTIL_TRUE;
    return res;
}

UTIL_RESULT HASH_Create(uint32_t ui32InitialSize,
                       struct sHash ** const ppsHash) {

    UTIL_RESULT res       = UTIL_SUCCESS;
    uint32_t ui32Index    = 0;
    struct sHash * psHash = NULL;

    assert(ppsHash != NULL);
    if (ppsHash == NULL) {
        res = -UTIL_ERROR_INVALID_PARAMETERS;
        return res;
    }

    assert (gbInitialised == UTIL_TRUE);
    if (!gbInitialised) {
        res = -UTIL_ERROR_NOT_INITIALISED;
        return res;
    }

    while (gbInitialised) {

        res = Pool_alloc(gpHashPool, (void **)&psHash);
        if (res != UTIL_SUCCESS) {
            *ppsHash = NULL;
            res = -UTIL_ERROR_UNEXPECTED_STATE;
            break;
        }

        psHash->ui32Size        = ui32InitialSize;
        psHash->ui32Count       = 0;
        psHash->ui32MinimumSize = ui32InitialSize;

        psHash->ppsTable = (struct sBucket **)
                            malloc(sizeof(struct sBucket *) * ui32InitialSize);

        if (psHash->ppsTable == NULL) {
            res = -UTIL_ERROR_MALLOC_FAILED;
            Pool_free(gpHashPool, psHash);
            *ppsHash = NULL;
            break;
        }

        for (ui32Index = 0; ui32Index < ui32InitialSize; ui32Index ++) {
            psHash->ppsTable[ui32Index] = NULL;
        }

        (*ppsHash) = psHash;
        res = UTIL_SUCCESS;
        break;
    }

    return res;
}

/*!
******************************************************************************

 @Functions            HASH_Delete

 @Description

 To delete a hash table, all entries in the table should be
	            removed before calling this function.

 @Input	    psHash      : Hash table pointer

 @Return    UTIL_RESULT  : UTIL_SUCCESS or an error code.

********************************************************************************/
UTIL_RESULT HASH_Delete(struct sHash * const psHash) {

    UTIL_RESULT res       = UTIL_SUCCESS;

    assert(psHash != NULL);
    if (!psHash) {
        res = -UTIL_ERROR_NOT_SUPPORTED;
        return res;
    }

    assert(gbInitialised != UTIL_FALSE);
    if (!gbInitialised) {
        res = -UTIL_ERROR_NOT_INITIALISED;
        return res;
    }

    while (gbInitialised) {
        // Entries in this table are not removed completly.
        if (psHash->ui32Count != 0) {
            res = -UTIL_ERROR_UNEXPECTED_STATE;
            break;
        }

        if (psHash->ppsTable) {
            free(psHash->ppsTable);
            psHash->ppsTable = NULL;
        }

        res = Pool_free(gpHashPool, (void *)psHash);
        if (res != UTIL_SUCCESS) {
            res = -UTIL_ERROR_UNEXPECTED_STATE;
            break;
        }

        res = UTIL_SUCCESS;
        break;
    }

    return res;
}

UTIL_RESULT HASH_Insert(struct sHash * const psHash,
                        uint64_t ui64Key, void * pValue) {

    UTIL_RESULT res = UTIL_SUCCESS;
    struct sBucket * psBucket = NULL;

    assert(psHash != NULL);
    if (psHash == NULL) {
        res = -UTIL_ERROR_INVALID_PARAMETERS;
        return res;
    }

    assert(gbInitialised != UTIL_FALSE);
    if (!gbInitialised) {
        res = -UTIL_ERROR_NOT_INITIALISED;
        return res;
    }

    while (gbInitialised) {

        res = Pool_alloc(gpBucketPool, (void **)&psBucket);
        if (res != UTIL_SUCCESS ||
                psBucket == NULL) {
            res = -UTIL_ERROR_UNEXPECTED_STATE;
            break;
        }

        psBucket->pNext  = NULL;
        psBucket->u64Key = ui64Key;
        psBucket->pValue = pValue;

        res = hashInsert(psBucket, psHash->ppsTable, psHash->ui32Size);
        if (res != UTIL_SUCCESS) {
            Pool_free(gpBucketPool, psBucket);
            res = -UTIL_ERROR_UNEXPECTED_STATE;
            break;
        }

        psHash->ui32Count++;

        // If we need self-expand the hash table size
        if ((psHash->ui32Count << 1) >= psHash->ui32Size) {
            res = hashResize(psHash, (psHash->ui32Size) << 1);
            if (res != UTIL_SUCCESS) {
                res = -UTIL_ERROR_UNEXPECTED_STATE;
                break;
            }
        }

        res = UTIL_SUCCESS;
        break;
    }

    return res;

}

UTIL_RESULT HASH_Remove(struct sHash * const psHash,
                        uint64_t ui64Key, void ** ppValue) {

    UTIL_RESULT res             = UTIL_SUCCESS;
    uint32_t    ui32Index       = 0;
    struct sBucket ** ppsBucket = NULL;

    assert(psHash != NULL);
    if (psHash == NULL) {
        res = -UTIL_ERROR_INVALID_PARAMETERS;
        return res;
    }

    ui32Index = hashFunc(ui64Key, psHash->ui32Size);

    for (ppsBucket = &(psHash->ppsTable[ui32Index]);
                      (*ppsBucket) != NULL;
                      (*ppsBucket) = (*ppsBucket)->pNext) {
        if ((*ppsBucket)->u64Key == ui64Key) {

            struct sBucket * psBucket = (*ppsBucket);
            void *pResult             = psBucket->pValue;

            (*ppsBucket) = psBucket->pNext;
            res = Pool_free(gpBucketPool, psBucket);

            psHash->ui32Count--;

            // If we need self-diminish the size of hash entries
            if (psHash->ui32Count < (psHash->ui32Size) >> 1) {
                res = hashResize(psHash, (psHash->ui32Size) >> 1);
                if (res != UTIL_SUCCESS) {
                    res = -UTIL_ERROR_UNEXPECTED_STATE;
                    break;
                }
            }

            // Return the vaule from the hash bucket
            *ppValue = pResult;
            res      = UTIL_SUCCESS;
            break;
        }
    }

    return res;
}
