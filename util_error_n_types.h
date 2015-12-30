/******************************************************************************
 *
 * @File       util_errors.h
 *
 * @Author     Alan Wang
 *
 * @Purpose    Error code used
 *
 * Subject to The MIT License (MIT)
 * https://opensource.org/licenses/MIT
 *
 *****************************************************************************/
#ifndef _UTIL_ERROR_N_TYPES_H_
#define _UTIL_ERROR_N_TYPES_H_

typedef int UTIL_RESULT;
typedef int UTIL_BOOL;

#define UTIL_TRUE  1
#define UTIL_FALSE 0

#define	UTIL_SUCCESS                                             (0)
#define UTIL_ERROR_MALLOC_FAILED                                 (1)
#define UTIL_ERROR_FATAL                                         (2)
#define UTIL_ERROR_OUT_OF_MEMORY                                 (3)
#define UTIL_ERROR_INVALID_ID                                    (4)
#define UTIL_ERROR_INVALID_PARAMETERS                            (5)
#define UTIL_ERROR_UNEXPECTED_STATE                              (6)
#define UTIL_ERROR_NOT_INITIALISED                               (7)
#define	UTIL_ERROR_ALREADY_INITIALISED                           (8)
#define	UTIL_ERROR_VALUE_OUT_OF_RANGE                            (9)
#define UTIL_ERROR_NOT_SUPPORTED                                 (10)

#endif
