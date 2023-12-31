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
#include "base/array.h"

array_t array_create(long int capacity, long int element_size, generic_copy copy_fn, generic_free free_fn)
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

any *__array_data(array_t array)
{
    return array.data;
}

any *__array_element_position_in_memory(array_t array, long int index)
{
    return array.data + index * array.element_size;
}

void array_destroy(array_t *array)
{
    free(array->data);
    array->data = NULL;
}

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

void array_pop(array_t array)
{
    array_remove(array, array.size - 1);
}

void array_remove(array_t array, long int index)
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

void array_insert(array_t *array, long int index, any element)
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

any array_get(array_t array, long int index)
{
    if (index >= array.capacity)
    {
        errno = ENOMEM;
        return NULL;
    }

    return array.data[index];
}

void array_set(array_t *array, long int index, any element)
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

long int array_size(array_t array)
{
    return array.size;
}

long int array_capacity(array_t array)
{
    return array.capacity;
}

bool array_is_empty(array_t array)
{
    return array.size == 0;
}

bool array_is_full(array_t array)
{
    return array.size == array.capacity;
}

void array_print(array_t array, generic_print print_fn)
{
    for (long int i = 0; i < array.size; i++)
    {
        printf("array[%lu] = ", i);
        print_fn(array.data + i * array.size);
        printf("\n");
    }
}

void array_resize(array_t *array, long int capacity)
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