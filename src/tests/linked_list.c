#include <CUnit/CUnit.h>
#include <stdio.h>

#include "tests/linked_list.h"

#include "types/linked_list.h"
#include "types/string.h"
#include "types/int.h"

void test_list_empty(void)
{
    linked_list ls = list_create();

    CU_ASSERT_TRUE(list_is_empty(ls));
    CU_ASSERT_EQUAL(list_length(ls), 0);

    list_destroy(&ls, int_free);
}

void test_list_add_int(void)
{
    linked_list ls = list_create();

    int a = 1;
    int b = 2;
    int c = 3;

    list_add(&ls, &a, int_copy);
    CU_ASSERT_FALSE(list_is_empty(ls));
    CU_ASSERT_EQUAL(list_length(ls), 1);
    CU_ASSERT_EQUAL(*(int *)list_get_data(ls), a);

    list_add(&ls, &b, int_copy);
    CU_ASSERT_EQUAL(list_length(ls), 2);
    CU_ASSERT_EQUAL(*(int *)list_get_data(ls), b);

    list_add(&ls, &c, int_copy);
    CU_ASSERT_EQUAL(list_length(ls), 3);
    CU_ASSERT_EQUAL(*(int *)list_get_data(ls), c);

    list_destroy(&ls, int_free);

    ls = list_create();

    list_add(&ls, &a, int_copy);
    list_add(&ls, &b, int_copy);
    list_add(&ls, &c, int_copy);

    CU_ASSERT_EQUAL(list_length(ls), 3);
    CU_ASSERT_EQUAL(*(int *)list_get_data(ls), c);
    CU_ASSERT_EQUAL(*(int *)list_get_data(list_get_next(ls)), b);
    CU_ASSERT_EQUAL(*(int *)list_get_data(list_get_next(list_get_next(ls))), a);

    list_destroy(&ls, int_free);
}

void test_list_overflow_int(void)
{
    int count = 1000;
    for (int i = 0; i < count; i++)
    {
        linked_list ls = list_create();
        for (int j = 0; j < count; j++)
        {
            list_add(&ls, &j, int_copy);
        }
        CU_ASSERT_EQUAL(list_length(ls), count);
        list_destroy(&ls, int_free);
        CU_ASSERT_EQUAL(list_length(ls), 0);
    }
}

void test_list_remove_int(void)
{
    linked_list ls = list_create();

    int a = 1;
    int b = 2;
    int c = 3;

    list_add(&ls, &a, int_copy);
    list_add(&ls, &b, int_copy);
    list_add(&ls, &c, int_copy);

    list_remove(&ls, int_free);
    CU_ASSERT_EQUAL(list_length(ls), 2);
    CU_ASSERT_EQUAL(*(int *)list_get_data(ls), b);

    list_remove(&ls, int_free);
    CU_ASSERT_EQUAL(list_length(ls), 1);
    CU_ASSERT_EQUAL(*(int *)list_get_data(ls), a);

    list_remove(&ls, int_free);
    CU_ASSERT_EQUAL(list_length(ls), 0);
    CU_ASSERT_TRUE(list_is_empty(ls));

    list_destroy(&ls, int_free);
}

void test_list_add_string(void)
{
    linked_list ls = list_create();

    string a = "Hello";
    string b = "World";
    string c = "!";

    list_add(&ls, &a, string_copy);
    CU_ASSERT_FALSE(list_is_empty(ls));
    CU_ASSERT_EQUAL(list_length(ls), 1);
    CU_ASSERT_STRING_EQUAL(*(string *)list_get_data(ls), a);

    list_add(&ls, &b, string_copy);
    CU_ASSERT_EQUAL(list_length(ls), 2);
    CU_ASSERT_STRING_EQUAL(*(string *)list_get_data(ls), b);

    list_add(&ls, &c, string_copy);
    CU_ASSERT_EQUAL(list_length(ls), 3);
    CU_ASSERT_STRING_EQUAL(*(string *)list_get_data(ls), c);

    list_destroy(&ls, string_free);

    ls = list_create();

    list_add(&ls, &a, string_copy);
    list_add(&ls, &b, string_copy);
    list_add(&ls, &c, string_copy);

    CU_ASSERT_EQUAL(list_length(ls), 3);
    CU_ASSERT_STRING_EQUAL(*(string *)list_get_data(ls), c);
    CU_ASSERT_STRING_EQUAL(*(string *)list_get_data(list_get_next(ls)), b);
    CU_ASSERT_STRING_EQUAL(*(string *)list_get_data(list_get_next(list_get_next(ls))), a);

    list_destroy(&ls, string_free);
}

void test_list_overflow_string(void)
{
    string hello = "Hello, World!";

    int count = 1000;
    for (int i = 0; i < count; i++)
    {
        linked_list ls = list_create();
        for (int j = 0; j < count; j++)
        {
            list_add(&ls, &hello, string_copy);
        }
        CU_ASSERT_EQUAL(list_length(ls), count);
        list_destroy(&ls, string_free);
        CU_ASSERT_EQUAL(list_length(ls), 0);
    }
}

void test_list_remove_string(void)
{
    linked_list ls = list_create();

    string a = "Hello";
    string b = "World";
    string c = "!";

    list_add(&ls, &a, string_copy);
    list_add(&ls, &b, string_copy);
    list_add(&ls, &c, string_copy);

    list_remove(&ls, string_free);
    CU_ASSERT_EQUAL(list_length(ls), 2);
    CU_ASSERT_STRING_EQUAL(*(string *)list_get_data(ls), b);

    list_remove(&ls, string_free);
    CU_ASSERT_EQUAL(list_length(ls), 1);
    CU_ASSERT_STRING_EQUAL(*(string *)list_get_data(ls), a);

    list_remove(&ls, string_free);
    CU_ASSERT_EQUAL(list_length(ls), 0);
    CU_ASSERT_TRUE(list_is_empty(ls));

    list_destroy(&ls, string_free);
}
