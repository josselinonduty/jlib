#include <CUnit/CUnit.h>
#include <errno.h>
#include <stdio.h>
#include "types/array.h"
#include "types/int.h"
#include "tests.h"

void test_array_create(void)
{
    long int capacity = 100;
    array_t array = array_create(capacity, int_size, int_copy, int_free);

    CU_ASSERT_EQUAL(array_capacity(array), capacity);
    CU_ASSERT_EQUAL(array_size(array), 0);
    CU_ASSERT_PTR_NOT_EQUAL(__array_data(array), NULL);

    array_destroy(&array);
}

void test_array_destroy(void)
{
    long int capacity = 100;
    array_t array = array_create(capacity, int_size, int_copy, int_free);

    array_destroy(&array);
    CU_ASSERT_PTR_EQUAL(__array_data(array), NULL);
}

void test_array_free(void)
{
    errno = 0;
    long int capacity = 100;
    long int count = 100000;
    for (long int i = 0; i < count; i++)
    {
        array_t array = array_create(capacity, int_size, int_copy, int_free);
        array_destroy(&array);
    }

    CU_ASSERT_EQUAL(errno, 0);
}

void test_array_add(void)
{
    long int capacity = 100;
    array_t array = array_create(capacity, int_size, int_copy, int_free);

    long int value = 42;
    array_push(&array, &value);

    CU_ASSERT_EQUAL(array_capacity(array), capacity);
    CU_ASSERT_EQUAL(array_size(array), 1);
    CU_ASSERT_EQUAL(*(int *)array_get(array, 0), value);

    array_destroy(&array);
}

void test_array_add_multiple(void)
{
    long int capacity = 100;
    array_t array = array_create(capacity, int_size, int_copy, int_free);

    long int count = 42;
    long int total = 0;
    for (long int i = 0; i < count; i++)
    {
        array_push(&array, &i);
        total += i;
    }

    CU_ASSERT_EQUAL(array_capacity(array), capacity);
    CU_ASSERT_EQUAL(array_size(array), count);

    long int sum = 0;
    for (long int i = 0; i < count; i++)
    {
        sum += *(int *)(array_get(array, i));
    }
    CU_ASSERT_EQUAL(sum, total);

    array_destroy(&array);
}

void test_array_add_overflow(void)
{
    long int capacity = 100;
    array_t array = array_create(capacity, int_size, int_copy, int_free);

    long int count = capacity + 1;

    for (long int i = 0; i < count; i++)
    {
        array_push(&array, &i);

        if (errno == ENOMEM)
        {
            break;
        }
    }

    CU_ASSERT_EQUAL(errno, ENOMEM);
    array_destroy(&array);
}

void test_array_insert(void)
{
    long int capacity = 100;
    array_t array = array_create(capacity, int_size, int_copy, int_free);

    long int count = 42;
    long int total = 0;
    for (long int i = 0; i < count; i++)
    {
        array_push(&array, &i);
        total += i;
    }

    long int value = 42;
    array_insert(&array, 0, &value);

    CU_ASSERT_EQUAL(array_capacity(array), capacity);
    CU_ASSERT_EQUAL(array_size(array), count + 1);

    long int sum = 0;
    for (long int i = 0; i < count + 1; i++)
    {
        sum += *(int *)(array_get(array, i));
    }
    CU_ASSERT_EQUAL(sum, total + value);

    array_destroy(&array);
}

void test_array_resize(void)
{
    long int capacity = 100;
    array_t array = array_create(capacity, int_size, int_copy, int_free);

    long int count = 42;
    long int total = 0;
    for (long int i = 0; i < count; i++)
    {
        array_push(&array, &i);
        total += i;
    }

    long int new_capacity = 200;
    array_resize(&array, new_capacity);

    CU_ASSERT_EQUAL(array_capacity(array), new_capacity);
    CU_ASSERT_EQUAL(array_size(array), count);

    long int sum = 0;
    for (long int i = 0; i < count; i++)
    {
        sum += *(int *)(array_get(array, i));
    }
    CU_ASSERT_EQUAL(sum, total);

    array_destroy(&array);
}