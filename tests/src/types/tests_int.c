#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "types/int.h"

void test_int_copy(void)
{
    int value = 42;
    int *copy = int_copy(&value);

    CU_ASSERT_EQUAL(*copy, value);
    CU_ASSERT_NOT_EQUAL(copy, &value);

    int_free(copy);
}

void test_int_equal(void)
{
    int a = 42;
    int b = 42;

    CU_ASSERT_TRUE(int_equal(&a, &b));
}

void test_int_leq(void)
{
    int a = 41;
    int b = 42;

    CU_ASSERT_TRUE(int_leq(&a, &b));
    CU_ASSERT_TRUE(int_leq(&a, &a));
    CU_ASSERT_FALSE(int_leq(&b, &a));
}

void test_int_geq(void)
{
    int a = 41;
    int b = 42;

    CU_ASSERT_FALSE(int_geq(&a, &b));
    CU_ASSERT_TRUE(int_geq(&b, &b));
    CU_ASSERT_TRUE(int_geq(&b, &a));
}