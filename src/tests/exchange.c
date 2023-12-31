#include <CUnit/CUnit.h>
#include "utilities/exchange.h"
#include "base/generic.h"
#include "base/int.h"
#include "tests/utilities.h"
#include <stdio.h>

void test_utils_exchange(void)
{
    int a = 9;
    int b = 42;

    void *pa = &a;
    void *pb = &b;

    exchange(&pa, &pb);

    CU_ASSERT_EQUAL(int_equal(pa, &b), 1);
    CU_ASSERT_EQUAL(int_equal(pb, &a), 1);
    CU_ASSERT_PTR_EQUAL(pa, &b);
    CU_ASSERT_PTR_EQUAL(pb, &a);
}