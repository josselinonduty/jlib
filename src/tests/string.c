#include <CUnit/CUnit.h>
#include "base/string.h"
#include "tests/string.h"

void test_string_copy(void)
{
    string value = "Hello, World!";
    string *copy = string_copy(&value);

    CU_ASSERT_STRING_EQUAL(*copy, value);
    CU_ASSERT_PTR_NOT_EQUAL(copy, &value);

    string_free(copy);
}

void test_string_equal(void)
{
    string a = "Hello, World!";
    string b = "Hello, World!";

    CU_ASSERT_TRUE(string_equal(&a, &b));
}