#include <CUnit/CUnit.h>
#include <stdio.h>
#include "base/generic.h"
#include "utilities/swap.h"
#include "types/int.h"

void test_utils_swap(void)
{
    int a = 9;
    int b = 42;

    void *pa = &a;
    void *pb = &b;

    swap(&pa, &pb);

    CU_ASSERT_TRUE(int_equal(pa, &b));
    CU_ASSERT_TRUE(int_equal(pb, &a));
    CU_ASSERT_PTR_EQUAL(pa, &b);
    CU_ASSERT_PTR_EQUAL(pb, &a);
}