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

 @Function				hash_Insert

 @Description

 Insert an intem to the Hash table.

 @Input	    pBucket    : The sBucket

 @Input	    ppTable    : The hash table

 @Input	    ui32Size    : The size of the hash table

 @Return    UTIL_RESULT  : UTIL_SUCCESS or an error code.

********************************************************************************/
static UTIL_RESULT hash_Insert(
        struct sBucket * pBucket,
        struct sHash  ** ppsTable,
        uint32_t ui32Size) {

    UTIL_RESULT res = UTIL_SUCCESS;
    uint32_t ui32Index;

    assert(pBucket  != NULL);
    assert(ppsTable != NULL);
    assert(ui32Size != 0)

    if (pBucket == NULL ||
        ppsTable == NULL ||
        ui32Size == NULL) {
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
        struct sHash ** ppsOldTable,
        uint32_t ui32OldSize,
        struct sHash ** ppsNewTable,
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

}
