#include <CUnit/CUnit.h>

#include "base/int.h"
#include "base/linked_list.h"
#include "types/stack.h"
#include "tests/types/stack.h"

void test_stack_create(void)
{
    stack q = stack_create(NULL, NULL, NULL);
    CU_ASSERT_PTR_NULL(stack_get_head(q));
    CU_ASSERT_EQUAL(stack_length(q), 0);
    stack_destroy(&q);
}

void test_stack_add(void)
{
    stack q = stack_create(int_copy, int_free, int_geq);

    CU_ASSERT_TRUE(stack_is_empty(q));
    CU_ASSERT_EQUAL(stack_length(q), 0);

    long int count = 1000;
    for (int i = 0; i < count; i++)
    {
        stack_stack(&q, &i);
    }

    CU_ASSERT_FALSE(stack_is_empty(q));
    CU_ASSERT_EQUAL(stack_length(q), count);
    CU_ASSERT_PTR_NOT_NULL(stack_get_head(q));

    bool stackValid = true;
    for (int i = 0; i < count; i++)
    {
        int *item = stack_unstack(&q);

        if (item == NULL)
        {
            stackValid = false;
            break;
        }

        if (*item != (count - 1) - i)
        {
            stackValid = false;
            break;
        }

        int_free(item);
    }

    CU_ASSERT_TRUE(stackValid);
    CU_ASSERT_TRUE(stack_is_empty(q));
    CU_ASSERT_EQUAL(stack_length(q), 0);

    stack_destroy(&q);
}