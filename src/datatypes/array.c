#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#include "base/generic.h"
#include "datatypes/array.h"

/**
 * \internal
 * \brief Makes a cell empty
 * \param array The dynamic array
 * \param index The index of the cell to make empty
 */
void __array_empty_cell(array *arr, unsigned long int index)
{
    assert(NULL != arr);
    assert(index >= 0 && index < arr->capacity);

    arr->data[index] = NULL;
}

/**
 * \internal
 * \brief Fits the size of the array to the number of elements
 * \param array The dynamic array
 */
void __array_fit_size(array *arr)
{
    assert(NULL != arr);

    while (arr->size > 0 && NULL == arr->data[arr->size - 1])
    {
        arr->size--;
    }
}

array array_create(unsigned long int capacity, unsigned long int initial_size)
{
    assert(capacity > 0);
    assert(initial_size >= 0 && initial_size <= capacity);

    array arr;

    arr.data = malloc(capacity * sizeof(any));
    if (NULL == arr.data)
    {
        errno = ENOMEM;
        return arr;
    }
    arr.size = initial_size;
    arr.capacity = capacity;

    for (unsigned long int i = 0; i < capacity; i++)
    {
        __array_empty_cell(&arr, i);
    }

    return arr;
}

void array_destroy(array *arr, generic_free free_fn)
{
    assert(NULL != arr);

    if (NULL != free_fn)
    {
        for (unsigned long int i = 0; i < array_size(*arr); i++)
        {
            free_fn(arr->data[i]);
        }
    }

    free(arr->data);
    arr->data = NULL;
    arr->capacity = 0;
    arr->size = 0;
}

void array_push(array *arr, any element, generic_copy copy_fn)
{
    assert(NULL != arr);
    assert(NULL != copy_fn);

    if (array_is_full(*arr))
    {
        array_resize(arr, arr->capacity * 2);
    }

    arr->data[arr->size] = copy_fn(element);
    arr->size++;
}

any array_pop(array *arr, generic_free free_fn)
{
    assert(NULL != arr);
    assert(!array_is_empty(*arr));

    arr->size--;
    any element = arr->data[array_size(*arr)];
    if (NULL != free_fn)
    {
        free_fn(element);
        element = NULL;
    }

    __array_empty_cell(arr, array_size(*arr));
    __array_fit_size(arr);

    if (!(array_is_empty(*arr)) && 3 * array_size(*arr) <= array_capacity(*arr))
    {
        array_resize(arr, array_capacity(*arr) / 2);
    }

    return element;
}

void array_remove(array *arr, unsigned long int index, generic_free free_fn)
{
    assert(NULL != arr);
    assert(NULL != free_fn);
    assert(index >= 0 && index < arr->size);

    free_fn(arr->data[index]);
    arr->data[index] = NULL;

    for (unsigned long int i = index; i < arr->size - 1; i++)
    {
        arr->data[i] = arr->data[i + 1];
    }

    __array_empty_cell(arr, arr->size - 1);
    __array_fit_size(arr);

    if (!(array_is_empty(*arr)) && array_size(*arr) == array_capacity(*arr) / 4)
    {
        array_resize(arr, arr->capacity / 2);
    }
}

void array_insert(array *arr, unsigned long int index, any element, generic_copy copy_fn)
{
    assert(NULL != arr);
    assert(NULL != copy_fn);
    assert(index >= 0 && index < array_size(*arr));

    if (array_is_full(*arr))
    {
        array_resize(arr, arr->capacity * 2);
    }

    memmove(arr->data + index + 1, arr->data + index, (arr->size - index) * sizeof(any));
    arr->data[index] = copy_fn(element);
    arr->size++;
}

any array_get(array arr, unsigned long int index)
{
    assert(array_has(arr, index));
    return arr.data[index];
}

bool array_has(array arr, unsigned long int index)
{
    assert(index >= 0 && index < array_capacity(arr));
    return NULL != arr.data[index];
}

void array_set(array *arr, unsigned long int index, any element, generic_copy copy_fn, generic_free free_fn)
{
    assert(NULL != arr);
    assert(NULL != copy_fn);
    assert(NULL != free_fn);
    assert(index >= 0 && index < array_capacity(*arr));

    if (array_has(*arr, index))
    {
        free_fn(arr->data[index]);
    }

    arr->data[index] = copy_fn(element);

    if (index >= arr->size)
    {
        arr->size = index + 1;
    }
}

unsigned long int array_size(array arr)
{
    return arr.size;
}

unsigned long int array_capacity(array arr)
{
    return arr.capacity;
}

bool array_is_empty(array arr)
{
    return array_size(arr) == 0 && array_capacity(arr) > 0;
}

bool array_is_full(array arr)
{
    return array_size(arr) == array_capacity(arr);
}

void array_print(array arr, generic_print print_fn)
{
    assert(NULL != print_fn);

    printf("[");
    for (unsigned long int i = 0; i < arr.size; i++)
    {
        any data = arr.data[i];
        if (NULL == data)
        {
            printf(" ");
        }
        else
        {
            print_fn(data);
        }

        if (i < arr.size - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
}

void array_resize(array *arr, unsigned long int capacity)
{
    assert(NULL != arr);
    assert(capacity >= 0);
    assert(capacity >= arr->size);

    arr->data = realloc(arr->data, capacity * sizeof(any));
    if (NULL == arr->data)
    {
        errno = ENOMEM;
        return;
    }

    arr->capacity = capacity;
    arr->size = arr->size;

    for (unsigned long int i = arr->size; i < capacity; i++)
    {
        __array_empty_cell(arr, i);
    }
}