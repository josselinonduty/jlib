#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdbool.h>
#include <stdlib.h>
#include "base/generic.h"

typedef struct array_t
{
    any *data;
    long int size;
    long int capacity;
    long int element_size;
    generic_copy copy;
    generic_free free;
} array_t;

any *__array_data(array_t array);

array_t array_create(long int capacity, long int element_size, generic_copy copy_fn, generic_free free_fn);
void array_destroy(array_t *array);
void array_push(array_t *array, any element);
void array_pop(array_t array);
void array_remove(array_t array, long int index);
void array_insert(array_t *array, long int index, any element);
any array_get(array_t array, long int index);
void array_set(array_t *array, long int index, any element);
long int array_size(array_t array);
long int array_capacity(array_t array);
bool array_is_empty(array_t array);
bool array_is_full(array_t array);
void array_print(array_t array, generic_print print_fn);
void array_resize(array_t *array, long int capacity);

#endif