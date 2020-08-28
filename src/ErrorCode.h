#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif 

typedef enum {
    // DON'T CHANGE THIS VALUE!
    ERROR_SUCCESS = 0, // indicates that no error has occured.
    DIMENSIONS_ERROR = 1, // indicates attemp to add/multiply two matrices without suitable dimestions.
    INVALID_INDEX = 2, // indicates attemp to get/set value of matrix in an invalid location.
    NULL_POINTER = 3, // indicates null pointer error.
    MEMORY_ERROR = 4, // indicates failure in memory allocation.
} ErrorCode;

/**
 * @brief Checks if a given error code indicates a success or not.
 *
 * @param[in] code the error code.
 * @return whether the error code indicates a success or not.
 */
bool error_isSuccess(ErrorCode code);

/**
 * @brief gets a textual error message for a given error code.
 *
 * @param[in] code the error code.
 * @return const char* the textual representation of the error code.
 */
const char* error_getErrorMessage(ErrorCode code);

#ifdef __cplusplus
}
#endif