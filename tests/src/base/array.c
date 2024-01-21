#include <CUnit/CUnit.h>
#include <stdio.h>
#include "base/generic.h"
#include "base/array.h"
#include "base/int.h"

unsigned long int __array_next_capacity(unsigned long int base, unsigned long int size)
{
    unsigned long int capacity = base;
    while (capacity <= size)
    {
        capacity <<= 1;
    }
    return capacity;
}

void test_array_create(void)
{
    long int capacity = 100;
    array arr = array_create(capacity, 0);

    CU_ASSERT_EQUAL(array_capacity(arr), capacity);
    CU_ASSERT_EQUAL(array_size(arr), 0);
    CU_ASSERT_PTR_NOT_NULL(arr.data);

    array_destroy(&arr, NULL);
    CU_ASSERT_PTR_NULL(arr.data);

    arr = array_create(capacity, 42);

    CU_ASSERT_EQUAL(array_capacity(arr), capacity);
    CU_ASSERT_EQUAL(array_size(arr), 42);
    CU_ASSERT_PTR_NOT_NULL(arr.data);

    array_destroy(&arr, NULL);
    CU_ASSERT_EQUAL(array_capacity(arr), 0);
    CU_ASSERT_PTR_NULL(arr.data);
}

void test_array_add(void)
{
    long int capacity = 100;
    array arr = array_create(capacity, 0);

    long int value = 42;
    array_push(&arr, &value, int_copy);

    CU_ASSERT_EQUAL(array_capacity(arr), capacity);
    CU_ASSERT_EQUAL(array_size(arr), 1);
    CU_ASSERT_TRUE(int_equal(array_get(arr, 0), &value));

    array_destroy(&arr, int_free);
}

void test_array_add_multiple(void)
{
    long int capacity = 1;
    array arr = array_create(capacity, 0);

    long int count = 100;
    for (long int i = 0; i < count; i++)
    {
        array_push(&arr, &i, int_copy);
    }

    CU_ASSERT_EQUAL(array_capacity(arr), __array_next_capacity(capacity, count));
    CU_ASSERT_EQUAL(array_size(arr), count);

    long int sum = 0;
    for (long int i = 0; i < count; i++)
    {
        sum += *(int *)(array_get(arr, i));
    }
    CU_ASSERT_EQUAL(sum, count * (count - 1) / 2);

    array_destroy(&arr, int_free);
}

void test_array_insert(void)
{
    long int capacity = 42;
    array arr = array_create(capacity, 0);

    long int count = 42;
    for (long int i = 0; i < count; i++)
    {
        array_push(&arr, &i, int_copy);
    }
    CU_ASSERT_EQUAL(array_capacity(arr), capacity);

    long int value = 42;
    array_insert(&arr, count / 2, &value, int_copy);

    CU_ASSERT_EQUAL(array_capacity(arr), __array_next_capacity(capacity, count + 1));
    CU_ASSERT_EQUAL(array_size(arr), count + 1);

    long int sum = 0;
    for (long int i = 0; i < count + 1; i++)
    {
        sum += *(int *)(array_get(arr, i));
    }
    CU_ASSERT_EQUAL(sum, count * (count - 1) / 2 + value);

    array_destroy(&arr, int_free);
}

void test_array_remove(void)
{
    long int capacity = 20;
    array arr = array_create(capacity, 0);

    long int count = 5;
    for (long int i = 0; i < count; i++)
    {
        array_push(&arr, &i, int_copy);
    }
    CU_ASSERT_EQUAL(array_size(arr), count);

    long int value = rand() % 100;
    array_set(&arr, count * 2, &value, int_copy, int_free);

    CU_ASSERT_EQUAL(array_size(arr), count * 2 + 1);
    CU_ASSERT_TRUE(array_has(arr, count * 2));

    array_remove(&arr, count * 2, int_free);

    CU_ASSERT_EQUAL(array_size(arr), count);
    if (array_capacity(arr) > count * 2)
    {
        CU_ASSERT_FALSE(array_has(arr, count * 2));
    }

    array_destroy(&arr, int_free);

    arr = array_create(capacity, 0);

    for (long int i = 0; i < count; i++)
    {
        array_push(&arr, &i, int_copy);
    }

    array_remove(&arr, count - 1, int_free);

    CU_ASSERT_EQUAL(array_size(arr), count - 1);

    value = rand() % 100;
    array_set(&arr, count * 2, &value, int_copy, int_free);

    int element = *(int *)array_get(arr, count * 2);
    CU_ASSERT_TRUE(int_equal(&element, &value));
    CU_ASSERT_EQUAL(array_size(arr), count * 2 + 1);

    int *pop = (int *)array_pop(&arr, NULL);
    CU_ASSERT_TRUE(int_equal(pop, &element));
    CU_ASSERT_EQUAL(array_size(arr), count - 1);
    int_free(pop);

    array_destroy(&arr, int_free);
}

void test_array_resize(void)
{
    long int capacity = 42;
    array arr = array_create(capacity, 0);

    long int count = 42;
    for (long int i = 0; i < count; i++)
    {
        array_push(&arr, &i, int_copy);
    }
    CU_ASSERT_EQUAL(array_is_full(arr), true);

    long int new_capacity = 200;
    array_resize(&arr, new_capacity);

    CU_ASSERT_EQUAL(array_capacity(arr), new_capacity);
    CU_ASSERT_EQUAL(array_size(arr), count);

    new_capacity = 50;
    array_resize(&arr, new_capacity);

    CU_ASSERT_EQUAL(array_capacity(arr), new_capacity);
    CU_ASSERT_EQUAL(array_size(arr), count);

    array_destroy(&arr, int_free);
}