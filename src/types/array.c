/**
 * @file src/types/array.c
 * @brief Functions related to dynamic arrays.
 * @author Josselin Dulongcourty
 * @version 1.0.0
 * @date 2023-12-08
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "base/generic.h"
#include "types/array.h"

/**
 * @brief Create a new dynamic array.
 * @param capacity The capacity of the array.
 * @param element_size The size of an element.
 * @param copy_fn The function to copy an element.
 * @param free_fn The function to free an element.
 * @return array_t
 */
array_t array_create(size_t capacity, size_t element_size, generic_copy copy_fn, generic_free free_fn)
{
    array_t array;
    array.capacity = capacity;
    array.size = 0;
    array.element_size = element_size;
    array.copy = copy_fn;
    array.free = free_fn;

    array.data = (any *)malloc(capacity * element_size);
    if (NULL == array.data)
    {
        printf("Error: malloc failed in array_create()\n");
        errno = ENOMEM;
        return array;
    }

    for (long int i = 0; i < capacity; i++)
    {
        array.data[i] = NULL;
    }
    return array;
}

/**
 * @private
 * @brief Get the data of an array.
 * @param array The array to get the data from.
 * @return any*
 */
any *__array_data(array_t array)
{
    return array.data;
}

/**
 * @private
 * @brief Get the position of an element in memory.
 * @param array The array to get the element from.
 * @param index The index to get the element from.
 * @return any* The position of the element in memory.
 */
any *__array_element_position_in_memory(array_t array, size_t index)
{
    return array.data + index * array.element_size;
}

/**
 * @brief Destroy an array.
 * @param array The array to destroy.
 */
void array_destroy(array_t *array)
{
    free(array->data);
    array->data = NULL;
}

/**
 * @brief Push an element to the end of an array.
 * @param array The array to push the element to.
 * @param element The element to push.
 */
void array_push(array_t *array, any element)
{
    if (array_is_full(*array))
    {
        errno = ENOMEM;
        return;
    }

    array_set(array, array->size, element);
    array->size++;
    errno = 0;
}

/**
 * @brief Remove the last element from an array.
 * @param array The array to remove the element from.
 */
void array_pop(array_t array)
{
    array_remove(array, array.size - 1);
}

/**
 * @brief Remove an element from an array at a given index.
 * @param array The array to remove the element from.
 * @param index The index to remove the element from.
 */
void array_remove(array_t array, size_t index)
{
    if (index >= array.capacity)
    {
        errno = ENOMEM;
        return;
    }

    array.free(__array_element_position_in_memory(array, index));
    array.size--;
    errno = 0;
}

/**
 * @brief Insert an element in an array at a given index.
 * @param array The array to insert the element in.
 * @param index The index to insert the element at.
 * @param element The element to insert.
 */
void array_insert(array_t *array, size_t index, any element)
{
    if (index >= array->size)
    {
        errno = ENOMEM;
        return;
    }

    // move elements to the right
    for (long int i = array->size; i > index; i--)
    {
        array_set(array, i, array_get(*array, i - 1));
    }

    array_set(array, index, element);
    array->size++;
    errno = 0;
}

/**
 * @brief Get an element from an array at a given index.
 * @param array The array to get the element from.
 * @param index The index to get the element from.
 */
any array_get(array_t array, size_t index)
{
    if (index >= array.capacity)
    {
        errno = ENOMEM;
        return NULL;
    }

    return array.data[index];
}

/**
 * @brief Set an element in an array at a given index.
 * @param array The array to set the element in.
 * @param index The index to set the element at.
 * @param element The element to set.
 */
void array_set(array_t *array, size_t index, any element)
{
    if (index >= array->capacity)
    {
        errno = ENOMEM;
        return;
    }

    if (array->data[index] != NULL)
    {
        array->free(array->data[index]);
    }

    any copy = array->copy(element);
    array->data[index] = copy;
    errno = 0;
}

/**
 * @brief Get the actual size of an array.
 * @param array The array to get the size from.
 * @return long int
 */
size_t array_size(array_t array)
{
    return array.size;
}

/**
 * @brief Get the capacity (reserved size) of an array.
 * @param array The array to get the capacity from.
 * @return long int
 */
size_t array_capacity(array_t array)
{
    return array.capacity;
}

/**
 * @brief Check if an array is empty.
 * @param array The array to check.
 * @return bool
 */
bool array_is_empty(array_t array)
{
    return array.size == 0;
}

/**
 * @brief Check if an array is fully filled.
 * @param array The array to check.
 * @return bool
 */
bool array_is_full(array_t array)
{
    return array.size == array.capacity;
}

/**
 * @brief Print an array to stdout.
 * @param array The array to print.
 * @param print_fn The function to print an element.
 */
void array_print(array_t array, generic_print print_fn)
{
    for (long int i = 0; i < array.size; i++)
    {
        printf("array[%lu] = ", i);
        print_fn(array.data + i * array.size);
        printf("\n");
    }
}

/**
 * @brief Resize an array.
 * @param array The array to resize.
 * @param capacity The new capacity of the array.
 * @return array_t
 */
void array_resize(array_t *array, size_t capacity)
{
    if (capacity < array->size)
    {
        errno = EINVAL;
        return;
    }

    array_t new_array = array_create(capacity, array->element_size, array->copy, array->free);
    memcpy(new_array.data, array->data, array->size * array->element_size);
    new_array.size = array->size;

    array_destroy(array);
    *array = new_array;
    errno = 0;
}