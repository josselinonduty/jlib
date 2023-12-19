#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "types/binary_code.h"

void test_binary_code_create()
{
    binary_code code = binary_code_create();
    CU_ASSERT_PTR_NOT_NULL(code);
    binary_code_destroy(code);
}

void test_binary_code_bit()
{
    binary_code code = binary_code_create();
    binary_code_set(code, 0, 1);
    CU_ASSERT_EQUAL(binary_code_get(code, 0), 1);
    binary_code_destroy(code);
}