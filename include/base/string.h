/**
 * \file string.h
 * \brief Type and function definitions for string
 * \author Josselin DULONGCOURTY
 * \date 2023-12-31
 * \version 1.1.1
 */

#ifndef __STRING_H__
#define __STRING_H__

#include <stdbool.h>
#include "base/generic.h"

/**
 * \brief String type
 * \typedef string
 */
typedef char *string;

/**
 * \brief Creates a new string
 * \param str The string to copy
 * \return string
 */
any string_create(string);

/**
 * \brief Copies a string
 * \param pstr The pointer to the string to copy
 * \return pointer to the copy of the string
 */
any string_copy(any);

/**
 * \brief Frees a string
 * \param str The pointer to the string to free
 */
void string_free(any);

/**
 * \brief Compares two strings
 * \param str1 The pointer to the first string
 * \param str2 The pointer to the second string
 * \return true if the two strings are equal, false otherwise
 */
bool string_equal(any, any);

/**
 * \brief Prints a string
 * \param str The pointer to the string to print
 */
void string_print(any);

/**
 * \brief Hashes a string
 * \param str The pointer to the string to hash
 * \return hash
 */
hash string_hash(any);

#endif // __STRING_H__