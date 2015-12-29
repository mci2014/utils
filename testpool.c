/*****************************************************************************
*
* @File       testpool.c
*
* @Author     Alan Wang
*
* @Purpose    Test unit for Objects Pool
*
* The MIT License (MIT)
* https://opensource.org/licenses/MIT
*
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "pool.h"

static Pool *gpPool = NULL;

typedef struct ObjectInPool {
    int number;
    void *data;
} ObjectInPool;

int main(void) {

    int result;

    ObjectInPool *obj = NULL;
    ObjectInPool *anotherObj = NULL;
    // Pool create
    result = Pool_create("TestPool", sizeof(ObjectInPool), &gpPool);

    if (result != 0) {
        printf("Pool created failed!!\n");
        return -1;
    }

    result = Pool_alloc(gpPool, (void *)&obj);
    if(result != 0) {
        printf("Pool_alloc failed!!\n");
    }

    obj->number = 1;

    printf("The obj just alloc is %p and it num is %d\n", obj, obj->number);

    // Free the obj
    Pool_free(gpPool, obj);

    // Allocate another obj
    result = Pool_alloc(gpPool, (void *)&anotherObj);
    if(result != 0) {
        printf("Pool_alloc failed!!\n");
    }

    anotherObj->number = 2;
    printf("The anotherObj just alloc is %p and it num is %d\n", anotherObj, anotherObj->number);

    Pool_free(gpPool, anotherObj);

    Pool_destory(gpPool);

    return 0;
}
