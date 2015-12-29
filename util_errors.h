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
#ifdef _UTIL_ERROR_H_
#define _UTIL_ERROR_H_

#if defined (__cplusplus)
extern "C" {
#endif

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

#if defined (__cplusplus)
    }
#endif

#endif
