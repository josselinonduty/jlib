#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include <ncurses.h>

#include "utilities/tests_swap.h"
#include "datatypes/tests_array.h"
#include "datatypes/tests_linked_list.h"
#include "datatypes/tests_doubly_linked_list.h"
#include "datatypes/tests_kv_linked_list.h"
#include "datatypes/tests_binary_tree.h"
#include "datatypes/tests_hash_table.h"
#include "types/tests_int.h"
#include "types/tests_string.h"
#include "types/tests_queue.h"
#include "types/tests_stack.h"

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
        NULL == CU_add_test(pSuite, "swap()", test_utils_swap))
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
        NULL == CU_add_test(pSuite, "int_geq()", test_int_geq) ||
        NULL == CU_add_test(pSuite, "string_create()", test_string_create) ||
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
        NULL == CU_add_test(pSuite, "array_add()", test_array_add) ||
        NULL == CU_add_test(pSuite, "array_add_multiple()", test_array_add_multiple) ||
        NULL == CU_add_test(pSuite, "array_insert()", test_array_insert) ||
        NULL == CU_add_test(pSuite, "array_remove()", test_array_remove) ||
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
        NULL == CU_add_test(pSuite, "linked_list_empty()", test_linked_list_empty) ||
        NULL == CU_add_test(pSuite, "linked_list_add_int()", test_linked_list_add_int) ||
        NULL == CU_add_test(pSuite, "test_linked_list_add_sorted_int()", test_linked_list_add_sorted_int) ||
        NULL == CU_add_test(pSuite, "linked_list_add_string()", test_linked_list_add_string) ||
        NULL == CU_add_test(pSuite, "linked_list_remove()", test_linked_list_remove_string))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    pSuite = CU_add_suite("Doubly Linked List", init_suite, clean_suite);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        NULL == CU_add_test(pSuite, "doubly_linked_list_empty()", test_doubly_linked_list_empty) ||
        NULL == CU_add_test(pSuite, "doubly_linked_list_add_int()", test_doubly_linked_list_add_int) ||
        NULL == CU_add_test(pSuite, "doubly_linked_list_add_sorted_int()", test_doubly_linked_list_add_sorted_int) ||
        NULL == CU_add_test(pSuite, "doubly_linked_list_add_string()", test_doubly_linked_list_add_string) ||
        NULL == CU_add_test(pSuite, "doubly_linked_list_remove()", test_doubly_linked_list_remove_string))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    pSuite = CU_add_suite("KV Linked List", init_suite, clean_suite);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        NULL == CU_add_test(pSuite, "kv_linked_list_empty()", test_kv_linked_list_empty) ||
        NULL == CU_add_test(pSuite, "kv_linked_list_add()", test_kv_linked_list_add) ||
        NULL == CU_add_test(pSuite, "kv_linked_list_add_sorted()", test_kv_linked_list_add_sorted) ||
        NULL == CU_add_test(pSuite, "kv_linked_list_remove()", test_kv_linked_list_remove))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    pSuite = CU_add_suite("Binary Tree", init_suite, clean_suite);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        NULL == CU_add_test(pSuite, "binary_tree_create()", test_binary_tree_create) ||
        NULL == CU_add_test(pSuite, "binary_tree_add()", test_binary_tree_add) ||
        NULL == CU_add_test(pSuite, "binary_tree_remove()", test_binary_tree_remove))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    pSuite = CU_add_suite("Queue", init_suite, clean_suite);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        NULL == CU_add_test(pSuite, "queue_create()", test_queue_create) ||
        NULL == CU_add_test(pSuite, "queue_add()", test_queue_add) ||
        NULL == CU_add_test(pSuite, "queue_add_sorted()", test_queue_add_sorted))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    pSuite = CU_add_suite("Stack", init_suite, clean_suite);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        NULL == CU_add_test(pSuite, "stack_create()", test_stack_create) ||
        NULL == CU_add_test(pSuite, "stack_add()", test_stack_add))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    pSuite = CU_add_suite("Hash Table", init_suite, clean_suite);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        NULL == CU_add_test(pSuite, "hash_table_create()", test_hash_table_create) ||
        NULL == CU_add_test(pSuite, "hash_table_add()", test_hash_table_add) ||
        NULL == CU_add_test(pSuite, "hash_table_remove()", test_hash_table_remove) ||
        NULL == CU_add_test(pSuite, "hash_table_find()", test_hash_table_find) ||
        NULL == CU_add_test(pSuite, "hash_table_destroy()", test_hash_table_destroy))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    pSuite = CU_add_suite("Vec2D", init_suite, clean_suite);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_basic_show_failures(CU_get_failure_list());
    printf("\n");

    if (CU_get_number_of_tests_failed() > 0)
    {
        CU_cleanup_registry();
        return EXIT_FAILURE;
    }

    CU_cleanup_registry();
    return EXIT_SUCCESS;
}