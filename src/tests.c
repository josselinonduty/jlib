#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "tests/utilities.h"
#include "tests/int.h"
#include "tests/string.h"
#include "tests/array.h"
#include "tests/linked_list.h"

int init_suite(void)
{
    return 0;
}

int clean_suite(void)
{
    return 0;
}

int main(void)
{
    CU_pSuite pSuite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    pSuite = CU_add_suite("Utilities", init_suite, clean_suite);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        NULL == CU_add_test(pSuite, "exchange()", test_utils_exchange))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    pSuite = CU_add_suite("Types", init_suite, clean_suite);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "int_copy()", test_int_copy) ||
        NULL == CU_add_test(pSuite, "int_equal()", test_int_equal) ||
        NULL == CU_add_test(pSuite, "int_leq()", test_int_leq) ||
        NULL == CU_add_test(pSuite, "string_copy()", test_string_copy) ||
        NULL == CU_add_test(pSuite, "string_equal()", test_string_equal))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    pSuite = CU_add_suite("Array", init_suite, clean_suite);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        NULL == CU_add_test(pSuite, "array_create()", test_array_create) ||
        NULL == CU_add_test(pSuite, "array_destroy()", test_array_destroy) ||
        NULL == CU_add_test(pSuite, "array_free()", test_array_free) ||
        NULL == CU_add_test(pSuite, "array_add()", test_array_add) ||
        NULL == CU_add_test(pSuite, "array_add_multiple()", test_array_add_multiple) ||
        NULL == CU_add_test(pSuite, "array_add_overflow()", test_array_add_overflow) ||
        NULL == CU_add_test(pSuite, "array_insert()", test_array_insert) ||
        NULL == CU_add_test(pSuite, "array_resize()", test_array_resize))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    pSuite = CU_add_suite("Linked List", init_suite, clean_suite);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        NULL == CU_add_test(pSuite, "list_empty()", test_list_empty) ||
        NULL == CU_add_test(pSuite, "list_add_int()", test_list_add_int) ||
        NULL == CU_add_test(pSuite, "list_overflow_int()", test_list_overflow_int) ||
        NULL == CU_add_test(pSuite, "list_remove_int()", test_list_remove_int) ||
        NULL == CU_add_test(pSuite, "list_add_string()", test_list_add_string) ||
        NULL == CU_add_test(pSuite, "list_overflow_string()", test_list_overflow_string) ||
        NULL == CU_add_test(pSuite, "list_remove_string()", test_list_remove_string))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_basic_show_failures(CU_get_failure_list());
    printf("\n");

    return CU_get_number_of_tests_failed() > 0;
}