#include <CUnit/CUnit.h>
#include <stdlib.h>

#include "base/linked_list.h"
#include "base/int.h"
#include "base/string.h"

#include "tests/base/linked_list.h"

void test_linked_list_empty(void)
{
    linked_list ls = linked_list_create();

    CU_ASSERT_TRUE(linked_list_is_empty(ls));

    linked_list_destroy(&ls, NULL);

    CU_ASSERT_TRUE(linked_list_is_empty(ls));
}

void test_linked_list_add_int(void)
{
    linked_list ls = linked_list_create();

    int a = 42;
    linked_list_add(&ls, &a, int_copy);

    CU_ASSERT_FALSE(linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(linked_list_length(ls), 1);
    CU_ASSERT_TRUE(int_equal(linked_list_get_data(ls), &a));

    int b = 43;
    int c = 44;
    linked_list_add(&ls, &b, int_copy);
    linked_list_add(&ls, &c, int_copy);

    CU_ASSERT_FALSE(linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(linked_list_length(ls), 3);
    CU_ASSERT_TRUE(int_equal(linked_list_get_data(ls), &c));
    CU_ASSERT_TRUE(int_equal(linked_list_get_data(linked_list_get_next(ls)), &b));

    linked_list_destroy(&ls, int_free);

    CU_ASSERT_TRUE(linked_list_is_empty(ls));
}

void test_linked_list_add_sorted_int(void)
{
    linked_list ls = linked_list_create();

    int count = 42;

    for (int i = 0; i < count; i++)
    {
        int random = rand() % count;
        linked_list_add_sorted(&ls, &random, int_copy, int_leq);
    }

    CU_ASSERT_FALSE(linked_list_is_empty(ls));

    bool sorted = true;
    for (int i = 0; i < count - 1; i++)
    {
        sorted &= int_leq(linked_list_get_data(ls), linked_list_get_data(linked_list_get_next(ls)));
        linked_list_remove(&ls, int_free);
    }
    CU_ASSERT_TRUE(sorted);

    linked_list_destroy(&ls, int_free);

    CU_ASSERT_TRUE(linked_list_is_empty(ls));
}

void test_linked_list_remove_int(void)
{
    linked_list ls = linked_list_create();

    int a = 42;
    linked_list_add(&ls, &a, int_copy);

    CU_ASSERT_FALSE(linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(linked_list_length(ls), 1);

    linked_list_remove(&ls, int_free);

    CU_ASSERT_TRUE(linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(linked_list_length(ls), 0);

    int b = 43;
    int c = 44;
    linked_list_add(&ls, &a, int_copy);
    linked_list_add(&ls, &b, int_copy);
    linked_list_add(&ls, &c, int_copy);

    CU_ASSERT_FALSE(linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(linked_list_length(ls), 3);

    linked_list_remove(&ls, int_free);

    CU_ASSERT_FALSE(linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(linked_list_length(ls), 2);
    CU_ASSERT_TRUE(int_equal(linked_list_get_data(ls), &b));

    linked_list_remove(&ls, int_free);

    CU_ASSERT_FALSE(linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(linked_list_length(ls), 1);
    CU_ASSERT_TRUE(int_equal(linked_list_get_data(ls), &a));

    linked_list_remove(&ls, int_free);

    CU_ASSERT_TRUE(linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(linked_list_length(ls), 0);

    linked_list_destroy(&ls, int_free);

    CU_ASSERT_TRUE(linked_list_is_empty(ls));
}

void test_linked_list_add_string(void)
{
    linked_list ls = linked_list_create();

    string a = "Hello";
    linked_list_add(&ls, &a, string_copy);

    CU_ASSERT_FALSE(linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(linked_list_length(ls), 1);
    CU_ASSERT_TRUE(string_equal(linked_list_get_data(ls), &a));

    string b = "World";
    string c = "!";
    linked_list_add(&ls, &b, string_copy);
    linked_list_add(&ls, &c, string_copy);

    CU_ASSERT_FALSE(linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(linked_list_length(ls), 3);
    CU_ASSERT_TRUE(string_equal(linked_list_get_data(ls), &c));
    CU_ASSERT_TRUE(string_equal(linked_list_get_data(linked_list_get_next(ls)), &b));

    linked_list_destroy(&ls, string_free);

    CU_ASSERT_TRUE(linked_list_is_empty(ls));
}

void test_linked_list_remove_string(void)
{
    linked_list ls = linked_list_create();

    string a = "Hello";
    linked_list_add(&ls, &a, string_copy);

    CU_ASSERT_FALSE(linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(linked_list_length(ls), 1);

    linked_list_remove(&ls, string_free);

    CU_ASSERT_TRUE(linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(linked_list_length(ls), 0);

    string b = "World";
    string c = "!";
    linked_list_add(&ls, &a, string_copy);
    linked_list_add(&ls, &b, string_copy);
    linked_list_add(&ls, &c, string_copy);

    CU_ASSERT_FALSE(linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(linked_list_length(ls), 3);

    linked_list_remove(&ls, string_free);

    CU_ASSERT_FALSE(linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(linked_list_length(ls), 2);
    CU_ASSERT_TRUE(string_equal(linked_list_get_data(ls), &b));

    linked_list_remove(&ls, string_free);

    CU_ASSERT_FALSE(linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(linked_list_length(ls), 1);
    CU_ASSERT_TRUE(string_equal(linked_list_get_data(ls), &a));

    linked_list_remove(&ls, string_free);

    CU_ASSERT_TRUE(linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(linked_list_length(ls), 0);

    linked_list_destroy(&ls, string_free);

    CU_ASSERT_TRUE(linked_list_is_empty(ls));
}