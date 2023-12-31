#include <CUnit/CUnit.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "base/kv_linked_list.h"
#include "base/int.h"
#include "base/string.h"

#include "tests/kv_linked_list.h"

string *__kv_linked_list_string_random(int n)
{
    char s[n + 1];

    for (int i = 0; i < n; i++)
    {
        s[i] = rand() % 26 + 'a';
    }
    s[n] = '\0';

    string *str = malloc(sizeof(string));
    *str = malloc(strlen(s) + 1);
    strcpy(*str, s);

    return str;
}

KV KV_copy_string_int(KV kv)
{
    return (KV){string_copy(kv.key), int_copy(kv.value)};
}

bool KV_equal_string_int(KV kv1, KV kv2)
{
    return string_equal(kv1.key, kv2.key) && int_equal(kv1.value, kv2.value);
}

bool KV_leq_string_int(KV kv1, KV kv2)
{
    string str1 = *(string *)kv1.key;
    string str2 = *(string *)kv2.key;

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    int len = len1 < len2 ? len1 : len2;

    if (strcmp(str1, str2) == 0)
    {
        return int_leq(kv1.value, kv2.value);
    }

    for (int i = 0; i < len; i++)
    {
        if (str1[i] < str2[i])
        {
            return true;
        }
        else if (str1[i] > str2[i])
        {
            return false;
        }
    }

    return len1 <= len2;
}

void KV_free_string_int(KV kv)
{
    string_free(kv.key);
    int_free(kv.value);
}

void KV_print_string_int(KV kv)
{
    printf("(%s:%d)", *(string *)kv.key, *(int *)kv.value);
}

void test_kv_linked_list_empty(void)
{
    KV_linked_list ls = KV_linked_list_create();

    CU_ASSERT_TRUE(KV_linked_list_is_empty(ls));

    KV_linked_list_destroy(&ls, NULL);

    CU_ASSERT_TRUE(KV_linked_list_is_empty(ls));
}

void test_kv_linked_list_add(void)
{
    KV_linked_list ls = KV_linked_list_create();

    string key1 = "mykey1";
    int value1 = 42;

    KV kv1 = {&key1, &value1};

    KV_linked_list_add(&ls, kv1, KV_copy_string_int);

    CU_ASSERT_FALSE(KV_linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(KV_linked_list_length(ls), 1);
    CU_ASSERT_TRUE(KV_equal_string_int(KV_linked_list_get_data(ls), kv1));

    string key2 = "mykey2";
    int value2 = 43;
    KV kv2 = {&key2, &value2};

    KV_linked_list_add(&ls, kv2, KV_copy_string_int);

    string key3 = "mykey3";
    int value3 = 44;
    KV kv3 = {&key3, &value3};

    KV_linked_list_add(&ls, kv3, KV_copy_string_int);

    CU_ASSERT_FALSE(KV_linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(KV_linked_list_length(ls), 3);
    CU_ASSERT_TRUE(KV_equal_string_int(KV_linked_list_get_data(ls), kv3));
    CU_ASSERT_TRUE(KV_equal_string_int(KV_linked_list_get_data(KV_linked_list_get_next(ls)), kv2));

    KV_linked_list_destroy(&ls, KV_free_string_int);

    CU_ASSERT_TRUE(KV_linked_list_is_empty(ls));
}

void test_kv_linked_list_add_sorted(void)
{
    KV_linked_list ls = KV_linked_list_create();

    int count = 1000;

    srand(time(NULL));
    for (int i = 0; i < count; i++)
    {
        string *key = __kv_linked_list_string_random(1);
        int value = rand() % 100;

        KV kv = {key, &value};

        KV_linked_list_add_sorted(&ls, kv, KV_copy_string_int, KV_leq_string_int);

        string_free(key);
    }
    CU_ASSERT_FALSE(KV_linked_list_is_empty(ls));

    bool sorted = true;
    for (int i = 0; i < count - 1; i++)
    {
        sorted &= KV_leq_string_int(KV_linked_list_get_data(ls), KV_linked_list_get_data(KV_linked_list_get_next(ls)));
        KV_linked_list_remove(&ls, KV_free_string_int);
    }
    CU_ASSERT_TRUE(sorted);

    KV_linked_list_destroy(&ls, KV_free_string_int);
}

void test_kv_linked_list_remove(void)
{
    KV_linked_list ls = KV_linked_list_create();

    string key1 = "mykey1";
    int value1 = 42;
    KV kv1 = {&key1, &value1};

    KV_linked_list_add(&ls, kv1, KV_copy_string_int);
    KV_linked_list_remove(&ls, KV_free_string_int);

    CU_ASSERT_TRUE(KV_linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(KV_linked_list_length(ls), 0);

    KV_linked_list_add(&ls, kv1, KV_copy_string_int);

    string key2 = "mykey2";
    int value2 = 43;
    KV kv2 = {&key2, &value2};

    KV_linked_list_add(&ls, kv2, KV_copy_string_int);

    string key3 = "mykey3";
    int value3 = 44;
    KV kv3 = {&key3, &value3};

    KV_linked_list_add(&ls, kv3, KV_copy_string_int);
    KV_linked_list_remove(&ls, KV_free_string_int);

    CU_ASSERT_FALSE(KV_linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(KV_linked_list_length(ls), 2);
    CU_ASSERT_TRUE(KV_equal_string_int(KV_linked_list_get_data(ls), kv2));
    CU_ASSERT_TRUE(KV_equal_string_int(KV_linked_list_get_data(KV_linked_list_get_next(ls)), kv1));

    KV_linked_list_remove(&ls, KV_free_string_int);

    CU_ASSERT_FALSE(KV_linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(KV_linked_list_length(ls), 1);
    CU_ASSERT_TRUE(KV_equal_string_int(KV_linked_list_get_data(ls), kv1));

    KV_linked_list_remove(&ls, KV_free_string_int);

    CU_ASSERT_TRUE(KV_linked_list_is_empty(ls));
    CU_ASSERT_EQUAL(KV_linked_list_length(ls), 0);

    KV_linked_list_destroy(&ls, KV_free_string_int);
}