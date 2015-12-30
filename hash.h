/*****************************************************************************
*
* @File       hash.h
*
* @Author     Alan Wang
*
* @Purpose    Self scaling hash tables.
*
* The MIT License (MIT)
* https://opensource.org/licenses/MIT
*
*****************************************************************************/
#ifndef _HASH_H_
#define _HASH_H_

#include "util_error_n_types.h"

#include <stdint.h>

#if defined (__cplusplus)
    extern "C" {
#endif

//Each entry in a hash table is placed into a sBucket
struct sBucket
{
	//the ->psNext sBucket on the same chain
	struct sBucket * pNext;

	//entry key
	uint64_t u64Key;

	//entry value
	void * pValue;
};

struct sHash
{
	//the hash table array
	struct sBucket ** ppsTable;

	//current size of the hash table
	uint32_t ui32Size;

	//number of entries currently in the hash table
	uint32_t ui32Count;

	//the minimum size that the hash table should be re-sized to
	uint32_t ui32MinimumSize;
};

// Hash Module init
UTIL_RESULT HASH_Init();

// Hash Module Deinit
UTIL_RESULT HASH_Deinit();

// Create an Hash table
UTIL_RESULT HASH_Create(uint32_t ui32InitialSize, struct sHash ** const ppsHash);

// Delete an Hash table
UTIL_RESULT HASH_Delete(struct sHash * const psHash);

// Insert a key/value pair into Hash table
UTIL_RESULT HASH_Insert(struct sHash * const psHash, uint64_t ui64Key, void * pValue);

// Remove a key/value pair from Hash table
UTIL_RESULT HASH_Remove(struct sHash * const psHash, uint64_t ui64Key, void ** ppValue);

#if defined (__cplusplus)
    }
#endif


#endif
