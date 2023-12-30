#include <CUnit/CUnit.h>
#include <stdbool.h>

#include "base/generic.h"
#include "base/flags.h"
#include "base/int.h"
#include "base/linked_list.h"
#include "types/queue.h"
#include "tests/queue.h"

bool __int_mod_1(any a, any b)
{
    int *x = (int *)a;
    int *y = (int *)b;

    return (*x * *x) < (*y * *y);
}

bool __int_mod_2(any a, any b)
{
    int *x = (int *)a;
    int *y = (int *)b;

    return (*x * *x) <= (*y * *y);
}

void test_queue_create(void)
{
    queue q = queue_create(FLAG_UNSORTED, NULL, NULL, NULL);
    CU_ASSERT_PTR_NULL(queue_get_head(q));
    CU_ASSERT_PTR_NULL(queue_get_tail(q));
    CU_ASSERT_EQUAL(queue_length(q), 0);
    CU_ASSERT_FALSE(queue_is_sorted(q));
    queue_destroy(&q);
}

void test_queue_add(void)
{
    queue q = queue_create(FLAG_SORTED, int_copy, int_free, int_leq);

    CU_ASSERT_TRUE(queue_is_empty(q));
    CU_ASSERT_EQUAL(queue_length(q), 0);

    long int count = 1000;
    for (int i = 0; i < count; i++)
    {
        queue_enqueue(&q, &i);
    }

    CU_ASSERT_FALSE(queue_is_empty(q));
    CU_ASSERT_EQUAL(queue_length(q), count);
    CU_ASSERT_PTR_NOT_NULL(queue_get_head(q));
    CU_ASSERT_PTR_NOT_NULL(queue_get_tail(q));

    bool queueValid = true;
    for (int i = 0; i < count; i++)
    {
        int *item = queue_dequeue(&q);

        if (item == NULL)
        {
            queueValid = false;
            break;
        }

        if (*item != i)
        {
            queueValid = false;
            break;
        }

        int_free(item);
    }

    CU_ASSERT_TRUE(queueValid);
    CU_ASSERT_TRUE(queue_is_empty(q));
    CU_ASSERT_EQUAL(queue_length(q), 0);

    queue_destroy(&q);
}

void test_queue_add_overflow(void)
{
    queue q = queue_create(FLAG_UNSORTED, int_copy, int_free, int_geq);

    CU_ASSERT_TRUE(queue_is_empty(q));
    CU_ASSERT_EQUAL(queue_length(q), 0);

    long int count = 1000;
    for (int i = 0; i < count; i++)
    {
        queue_enqueue(&q, &i);
        int *item = queue_dequeue(&q);
        int_free(item);
    }

    CU_ASSERT_TRUE(queue_is_empty(q));
    CU_ASSERT_EQUAL(queue_length(q), 0);
    CU_ASSERT_PTR_NULL(queue_get_head(q));
    CU_ASSERT_PTR_NULL(queue_get_tail(q));

    queue_destroy(&q);
}

void test_queue_add_sorted(void)
{
    queue q = queue_create(FLAG_SORTED, int_copy, int_free, __int_mod_1);

    CU_ASSERT_TRUE(queue_is_empty(q));
    CU_ASSERT_EQUAL(queue_length(q), 0);

    long int count = 10;
    for (int i = 0; i < count; i++)
    {
        queue_enqueue(&q, &i);
    }

    CU_ASSERT_FALSE(queue_is_empty(q));
    CU_ASSERT_EQUAL(queue_length(q), count);
    CU_ASSERT_PTR_NOT_NULL(queue_get_head(q));
    CU_ASSERT_PTR_NOT_NULL(queue_get_tail(q));

    bool queueValid = true;

    int *prev = queue_dequeue(&q);
    for (int i = 1; i < count; i++)
    {
        int *item = queue_dequeue(&q);

        if (item == NULL)
        {
            queueValid = false;
            break;
        }

        if (!__int_mod_1(prev, item))
        {
            queueValid = false;
            break;
        }

        int_free(item);
    }
    int_free(prev);

    CU_ASSERT_TRUE(queueValid);
    CU_ASSERT_TRUE(queue_is_empty(q));
    CU_ASSERT_EQUAL(queue_length(q), 0);

    queue_destroy(&q);

    q = queue_create(FLAG_SORTED, int_copy, int_free, __int_mod_2);

    CU_ASSERT_TRUE(queue_is_empty(q));
    CU_ASSERT_EQUAL(queue_length(q), 0);

    for (int i = 0; i < count; i++)
    {
        queue_enqueue(&q, &i);
    }

    CU_ASSERT_FALSE(queue_is_empty(q));
    CU_ASSERT_EQUAL(queue_length(q), count);
    CU_ASSERT_PTR_NOT_NULL(queue_get_head(q));
    CU_ASSERT_PTR_NOT_NULL(queue_get_tail(q));

    queueValid = true;

    prev = queue_dequeue(&q);
    for (int i = 1; i < count; i++)
    {
        int *item = queue_dequeue(&q);

        if (item == NULL)
        {
            queueValid = false;
            break;
        }

        if (!__int_mod_2(prev, item))
        {
            queueValid = false;
            break;
        }

        int_free(item);
    }
    int_free(prev);

    CU_ASSERT_TRUE(queueValid);
    CU_ASSERT_TRUE(queue_is_empty(q));
    CU_ASSERT_EQUAL(queue_length(q), 0);

    queue_destroy(&q);
}