/**
 * \file generic.h
 * \brief Generic types and functions.
 * \author Josselin Dulongcourty
 * \version 1.0
 * \date 2023-12-06
 */

#ifndef __GENERIC_H__
#define __GENERIC_H__

#include <stdlib.h>
#include <stdbool.h>

/**
 * \typedef any
 * \brief Generic type.
 */
typedef void *any;

/**
 * \typedef generic_copy
 * \brief Generic copy function.
 * \return The copy of the given value.
 * \param value The value to copy.
 */
typedef any (*generic_copy)(any);

/**
 * \typedef generic_free
 * \brief Generic free function.
 * \param value The value to free.
 */
typedef void (*generic_free)(any);

/**
 * \typedef generic_compare
 * \brief Generic compare function.
 * \param v1 The first value to compare.
 * \param v2 The second value to compare.
 */
typedef bool (*generic_compare)(any, any);

/**
 * \typedef generic_print
 * \brief Generic print function.
 * \param value The value to print.
 */
typedef void (*generic_print)(any);

/**
 * \typedef hash
 * \brief Hash type.
 */
typedef unsigned long hash;

/**
 * \typedef generic_hash
 * \brief Generic hash function.
 * \param value The value to hash.
 * \return The hash of the given value.
 */
typedef hash (*generic_hash)(any);

#endif