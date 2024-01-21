#include <CUnit/CUnit.h>
#include <stdlib.h>

#include "base/doubly_linked_list.h"
#include "base/int.h"
#include "base/string.h"

#include "tests/base/doubly_linked_list.h"

void test_doubly_linked_list_empty(void)
{
    doubly_linked_list ls = doubly_linked_list_create();

    CU_ASSERT_TRUE(doubly_linked_list_is_empty(ls));

    doubly_linked_list_destroy(&ls, NULL);

    CU_ASSERT_TRUE(doubly_linked_list_is_empty(ls));
}

void test_doubly_linked_list_add_int(void)
{
    doubly_linked_list ls = doubly_linked_list_create();

    int a = 42;
    doubly_linked_list_add(&ls, &a, int_copy);

    CU_ASSERT_FALSE(doubly_linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(doubly_linked_list_length(ls), 1);
    CU_ASSERT_TRUE(int_equal(doubly_linked_list_get_data(ls), &a));

    int b = 43;
    int c = 44;
    doubly_linked_list_add(&ls, &b, int_copy);
    doubly_linked_list_add(&ls, &c, int_copy);

    CU_ASSERT_FALSE(doubly_linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(doubly_linked_list_length(ls), 3);
    CU_ASSERT_TRUE(int_equal(doubly_linked_list_get_data(ls), &c));
    CU_ASSERT_TRUE(int_equal(doubly_linked_list_get_data(doubly_linked_list_get_prev(doubly_linked_list_get_next(ls))), &c));
    CU_ASSERT_TRUE(int_equal(doubly_linked_list_get_data(doubly_linked_list_get_next(ls)), &b));
    CU_ASSERT_PTR_EQUAL(ls, doubly_linked_list_get_prev(doubly_linked_list_get_next(ls)));

    doubly_linked_list_destroy(&ls, int_free);

    CU_ASSERT_TRUE(doubly_linked_list_is_empty(ls));
}

void test_doubly_linked_list_add_sorted_int(void)
{
    doubly_linked_list ls = doubly_linked_list_create();

    int count = 42;

    for (int i = 0; i < count; i++)
    {
        int random = rand() % count;
        doubly_linked_list_add_sorted(&ls, &random, int_copy, int_geq);
    }

    CU_ASSERT_FALSE(doubly_linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(doubly_linked_list_length(ls), count);

    bool sorted = true;
    for (int i = 0; i < count - 1; i++)
    {
        sorted &= int_geq(
            doubly_linked_list_get_data(ls),
            doubly_linked_list_get_data(doubly_linked_list_get_next(ls)));
        ls = doubly_linked_list_get_next(ls);
    }
    CU_ASSERT_TRUE(sorted);

    sorted = true;
    for (int i = 0; i < count - 1; i++)
    {
        sorted &= int_leq(
            doubly_linked_list_get_data(ls),
            doubly_linked_list_get_data(doubly_linked_list_get_prev(ls)));
        ls = doubly_linked_list_get_prev(ls);
    }
    CU_ASSERT_TRUE(sorted);

    doubly_linked_list_destroy(&ls, int_free);

    CU_ASSERT_TRUE(doubly_linked_list_is_empty(ls));
}

void test_doubly_linked_list_remove_int(void)
{
    doubly_linked_list ls = doubly_linked_list_create();

    int a = 42;
    doubly_linked_list_add(&ls, &a, int_copy);

    CU_ASSERT_FALSE(doubly_linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(doubly_linked_list_length(ls), 1);

    doubly_linked_list_remove(&ls, int_free);

    CU_ASSERT_TRUE(doubly_linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(doubly_linked_list_length(ls), 0);

    int b = 43;
    int c = 44;
    doubly_linked_list_add(&ls, &a, int_copy);
    doubly_linked_list_add(&ls, &b, int_copy);
    doubly_linked_list_add(&ls, &c, int_copy);

    CU_ASSERT_FALSE(doubly_linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(doubly_linked_list_length(ls), 3);
    CU_ASSERT_PTR_EQUAL(ls, doubly_linked_list_get_prev(doubly_linked_list_get_next(ls)));

    doubly_linked_list_remove(&ls, int_free);

    CU_ASSERT_FALSE(doubly_linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(doubly_linked_list_length(ls), 2);
    CU_ASSERT_TRUE(int_equal(doubly_linked_list_get_data(ls), &b));
    CU_ASSERT_PTR_EQUAL(ls, doubly_linked_list_get_prev(doubly_linked_list_get_next(ls)));

    doubly_linked_list_remove(&ls, int_free);

    CU_ASSERT_FALSE(doubly_linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(doubly_linked_list_length(ls), 1);
    CU_ASSERT_TRUE(int_equal(doubly_linked_list_get_data(ls), &a));
    CU_ASSERT_PTR_EQUAL(doubly_linked_list_get_next(ls), doubly_linked_list_create());
    CU_ASSERT_PTR_EQUAL(doubly_linked_list_get_prev(ls), doubly_linked_list_create());

    doubly_linked_list_remove(&ls, int_free);

    CU_ASSERT_TRUE(doubly_linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(doubly_linked_list_length(ls), 0);

    doubly_linked_list_destroy(&ls, int_free);

    CU_ASSERT_TRUE(doubly_linked_list_is_empty(ls));
}

void test_doubly_linked_list_add_string(void)
{
    doubly_linked_list ls = doubly_linked_list_create();

    string a = "Hello";
    doubly_linked_list_add(&ls, &a, string_copy);

    CU_ASSERT_FALSE(doubly_linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(doubly_linked_list_length(ls), 1);
    CU_ASSERT_TRUE(string_equal(doubly_linked_list_get_data(ls), &a));

    string b = "World";
    string c = "!";
    doubly_linked_list_add(&ls, &b, string_copy);
    doubly_linked_list_add(&ls, &c, string_copy);

    CU_ASSERT_FALSE(doubly_linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(doubly_linked_list_length(ls), 3);
    CU_ASSERT_TRUE(string_equal(doubly_linked_list_get_data(ls), &c));
    CU_ASSERT_TRUE(string_equal(doubly_linked_list_get_data(doubly_linked_list_get_next(ls)), &b));
    CU_ASSERT_PTR_EQUAL(ls, doubly_linked_list_get_prev(doubly_linked_list_get_next(ls)));

    doubly_linked_list_destroy(&ls, string_free);

    CU_ASSERT_TRUE(doubly_linked_list_is_empty(ls));
}

void test_doubly_linked_list_remove_string(void)
{
    doubly_linked_list ls = doubly_linked_list_create();

    string a = "Hello";
    doubly_linked_list_add(&ls, &a, string_copy);

    CU_ASSERT_FALSE(doubly_linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(doubly_linked_list_length(ls), 1);

    doubly_linked_list_remove(&ls, string_free);

    CU_ASSERT_TRUE(doubly_linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(doubly_linked_list_length(ls), 0);

    string b = "World";
    string c = "!";
    doubly_linked_list_add(&ls, &a, string_copy);
    doubly_linked_list_add(&ls, &b, string_copy);
    doubly_linked_list_add(&ls, &c, string_copy);

    CU_ASSERT_FALSE(doubly_linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(doubly_linked_list_length(ls), 3);
    CU_ASSERT_PTR_EQUAL(ls, doubly_linked_list_get_prev(doubly_linked_list_get_next(ls)));

    doubly_linked_list_remove(&ls, string_free);

    CU_ASSERT_FALSE(doubly_linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(doubly_linked_list_length(ls), 2);
    CU_ASSERT_TRUE(string_equal(doubly_linked_list_get_data(ls), &b));
    CU_ASSERT_PTR_EQUAL(ls, doubly_linked_list_get_prev(doubly_linked_list_get_next(ls)));

    doubly_linked_list_remove(&ls, string_free);

    CU_ASSERT_FALSE(doubly_linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(doubly_linked_list_length(ls), 1);
    CU_ASSERT_TRUE(string_equal(doubly_linked_list_get_data(ls), &a));
    CU_ASSERT_PTR_EQUAL(doubly_linked_list_get_next(ls), doubly_linked_list_create());
    CU_ASSERT_PTR_EQUAL(doubly_linked_list_get_prev(ls), doubly_linked_list_create());

    doubly_linked_list_remove(&ls, string_free);

    CU_ASSERT_TRUE(doubly_linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(doubly_linked_list_length(ls), 0);

    doubly_linked_list_destroy(&ls, string_free);

    CU_ASSERT_TRUE(doubly_linked_list_is_empty(ls));
}