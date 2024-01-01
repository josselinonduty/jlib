/**
 * \file array.h
 * \brief Types and functions for dynamic arrays
 * \author Josselin Dulongcourty
 * \version 2.0.0
 * \date 2023-12-31
 */

#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "base/generic.h"

/**
 * \typedef array
 * \brief Dynamic array
 */
typedef struct array array;

/**
 * \internal
 * \struct array
 * \brief Dynamic array
 *
 * \var array::data
 * \brief Pointer to the array's data
 *
 * \var array::size
 * \brief Number of elements in the array
 *
 * \var array::capacity
 * \brief Maximum number of elements in the array
 */
struct array
{
    any *data;
    unsigned long int size;
    unsigned long int capacity;
};

/**
 * \brief Creates a new dynamic array
 *
 * \param capacity Maximum number of elements in the array
 * \param initial_size Number of elements in the array
 * \return The new dynamic array
 */
array array_create(unsigned long int capacity, unsigned long int initial_size);

/**
 * \brief Destroys a dynamic array
 *
 * \param arr The dynamic array to destroy
 * \param free_fn The function to free the elements of the array
 */
void array_destroy(array *arr, generic_free free_fn);

/**
 * \brief Pushes an element at the end of a dynamic array
 *
 * \param arr The dynamic array
 * \param element The element to push
 * \param copy_fn The function to copy the element
 *
 * \note If the array is full, it is resized
 */
void array_push(array *arr, any element, generic_copy copy_fn);

/**
 * \brief Pops an element from the end of a dynamic array
 *
 * \param arr The dynamic array
 * \param free_fn The function to free the element
 * \return The popped element
 *
 * \pre The array is not empty
 *
 * \note If free_fn is NULL, the element is not freed
 * \note If half of the array's capacity is unused, it is resized
 */
any array_pop(array *arr, generic_free free_fn);

/**
 * \brief Removes an element from a dynamic array
 *
 * \param arr The dynamic array
 * \param index The index of the element to remove
 * \param free_fn The function to free the element
 *
 * \pre The index is valid
 *
 * \note If half of the array's capacity is unused, it is resized
 */
void array_remove(array *arr, unsigned long int index, generic_free free_fn);

/**
 * \brief Inserts an element to a dynamic array
 *
 * \param arr The dynamic array
 * \param index The index where to add the element
 * \param element The element to add
 * \param copy_fn The function to copy the element
 * \param free_fn The function to free the element
 *
 * \pre The index is valid
 *
 * \note If the array is full, it is resized
 */
void array_insert(array *arr, unsigned long int index, any element, generic_copy copy_fn);

/**
 * \brief Gets an element from a dynamic array
 *
 * \param arr The dynamic array
 * \param index The index of the element to get
 * \return The element
 *
 * \pre The index is valid
 */
any array_get(array arr, unsigned long int index);

/**
 * \brief Checks if a dynamic array contains an element at a given index
 *
 * \param arr The dynamic array
 * \param index The index of the element to check
 * \return true if the array contains an element at the given index, false otherwise
 *
 * \pre The index is valid
 */
bool array_has(array arr, unsigned long int index);

/**
 * \brief Sets an element to a dynamic array
 *
 * \param arr The dynamic array
 * \param index The index of the element to set
 * \param element The element to set
 * \param copy_fn The function to copy the element
 * \param free_fn The function to free the element
 *
 * \pre The index is valid
 *
 * \note If an element is already at the index, it is freed
 */
void array_set(array *arr, unsigned long int index, any element, generic_copy copy_fn, generic_free free_fn);

/**
 * \brief Gets the size of a dynamic array
 *
 * \param arr The dynamic array
 * \return The size of the dynamic array
 */
unsigned long int array_size(array arr);

/**
 * \brief Gets the capacity of a dynamic array
 *
 * \param arr The dynamic array
 * \return The capacity of the dynamic array
 */
unsigned long int array_capacity(array arr);

/**
 * \brief Checks if a dynamic array is empty
 *
 * \param arr The dynamic array
 * \return true if the dynamic array is empty, false otherwise
 */
bool array_is_empty(array arr);

/**
 * \brief Checks if a dynamic array is full
 *
 * \param arr The dynamic array
 * \return true if the dynamic array is full, false otherwise
 */
bool array_is_full(array arr);

/**
 * \brief Prints a dynamic array
 *
 * \param arr The dynamic array
 * \param print_fn The function to print the elements
 */
void array_print(array arr, generic_print print_fn);

/**
 * \brief Resizes a dynamic array
 *
 * \param arr The dynamic array
 * \param capacity The new capacity
 */
void array_resize(array *arr, unsigned long int capacity);

#endif // __ARRAY_H__