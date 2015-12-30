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
