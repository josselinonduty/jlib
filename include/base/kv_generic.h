/**
 * \file kv_generic.h
 * \brief Key/Value pairs types and functions.
 * \author Josselin Dulongcourty
 * \version 1.0.0
 * \date 2023-12-30
 */

#ifndef __KV_GENERIC_H__
#define __KV_GENERIC_H__

#include <stdlib.h>
#include <stdbool.h>

#include "base/generic.h"

/**
 * \typedef KV
 * \brief KV type.
 */
typedef struct KV KV;

/**
 * \internal
 * \typedef KV
 * \brief KV type.
 */
struct KV
{
    any key;
    any value;
};

/**
 * \typedef KV_copy
 * \brief KV copy function.
 * \param data The data to copy.
 * \return The copy of the given value.
 */
typedef KV (*KV_copy)(KV data);

/**
 * \typedef KV_free
 * \brief KV free function.
 * \param data The data to free.
 */
typedef void (*KV_free)(KV data);

/**
 * \typedef KV_compare
 * \brief KV compare function.
 * \param data1 The first data to compare.
 * \param data2 The second data to compare.
 * \return True if the two values are equals, false otherwise.
 */
typedef bool (*KV_compare)(KV data1, KV data2);

/**
 * \typedef KV_print
 * \brief KV print function.
 * \param data The data to print.
 */
typedef void (*KV_print)(KV data);

/**
 * \typedef KV_hash
 * \brief KV hash function.
 * \param data The data to hash.
 * \return The hash of the given value.
 */
typedef hash (*KV_hash)(KV data);

#endif // __KV_GENERIC_H__