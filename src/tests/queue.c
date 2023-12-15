#include <CUnit/CUnit.h>

#include "base/int.h"
#include "base/linked_list.h"
#include "types/queue.h"
#include "tests/queue.h"

void test_queue_create(void)
{
    queue q = queue_create(NULL, NULL, NULL);
    CU_ASSERT_PTR_NULL(queue_get_head(q));
    CU_ASSERT_PTR_NULL(queue_get_tail(q));
    CU_ASSERT_EQUAL(queue_length(q), 0);
    queue_destroy(&q);
}

void test_queue_add(void)
{
    queue q = queue_create(int_copy, int_free, int_geq);

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
    queue q = queue_create(int_copy, int_free, int_geq);

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