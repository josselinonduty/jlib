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
 */
typedef any (*generic_copy)(any);

/**
 * \typedef generic_free
 * \brief Generic free function.
 */
typedef void (*generic_free)(any);

/**
 * \typedef generic_size
 * \brief Generic size function.
 */
typedef bool (*generic_compare)(any, any);

/**
 * \typedef generic_size
 * \brief Generic size function.
 */
typedef void (*generic_print)(any);

#endif