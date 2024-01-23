/**
 * \file int.h
 * \brief Functions for int type
 * \author Josselin Dulongcourty
 * \version 1.3.1
 * \date 2023-12-31
 */

#ifndef __INT_H__
#define __INT_H__

#include <stdbool.h>
#include "base/generic.h"

/**
 * \fn any int_copy(any a)
 * \brief Copies an int.
 * \param value The int to copy.
 * \return any The copy of the int.
 */
any int_copy(any value);

/**
 * \fn void int_free(any a)
 * \brief Frees an int.
 * \param value The int to free.
 */
void int_free(any value);

/**
 * \fn bool int_equal(any a, any b)
 * \brief Checks if two ints are equal.
 * \param a The first int.
 * \param b The second int.
 * \return bool True if the ints are equal, false otherwise.
 */
bool int_equal(any a, any b);

/**
 * \fn bool int_leq(any a, any b)
 * \brief Checks if the first int is less or equal to the second.
 * \param a The first int.
 * \param b The second int.
 * \return bool True if the first int is less or equal to the second, false otherwise.
 */
bool int_leq(any a, any b);

/**
 * \fn bool int_geq(any a, any b)
 * \brief Checks if the first int is greater or equal to the second.
 * \param a The first int.
 * \param b The second int.
 * \return bool True if the first int is greater or equal to the second, false otherwise.
 */
bool int_geq(any a, any b);

/**
 * \fn void int_print(any a)
 * \brief Prints an int.
 * \param value The int to print.
 */
void int_print(any value);

/**
 * \fn hash int_hash(any a)
 * \brief Hashes an int.
 * \param value The int to hash.
 * \return hash The hash of the int.
 */
hash int_hash(any value);

#endif // __INT_H__