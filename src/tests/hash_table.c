#include <CUnit/CUnit.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "base/generic.h"
#include "base/kv_generic.h"
#include "base/int.h"
#include "base/string.h"
#include "base/kv_linked_list.h"
#include "base/hash_table.h"

KV __hash_kv_copy_string_int(KV kv)
{
    string *key = string_copy(kv.key);
    int *value = int_copy(kv.value);

    return (KV){key, value};
}

void __hash_kv_free_string_int(KV entry)
{
    string_free(entry.key);
    int_free(entry.value);
}

hash __hash_kv_hash_string_int(KV entry)
{
    return string_hash(entry.key);
}

bool __hash_kv_equal_string_int(KV entry1, KV entry2)
{
    return string_equal(entry1.key, entry2.key);
}

void __hash_kv_print_string_int(KV entry)
{
    printf("(");
    string_print(entry.key);
    printf(":");
    int_print(entry.value);
    printf(")");
}

void __hash_table_alphabet(KV_linked_list *bucket)
{
    for (int i = 97; i < 97 + 26; i++)
    {
        string *key = string_create((char[]){i, '\0'});
        int value = i;
        KV entry = {key, &value};

        KV_linked_list_add(bucket, entry, __hash_kv_copy_string_int);
        string_free(key);
    }
}

void test_hash_table_create(void)
{
    hash_table map = hash_table_create(26);

    CU_ASSERT_EQUAL(map.capacity, 26);

    bool is_empty = true;
    for (long int i = 0; i < map.capacity; i++)
    {
        is_empty = is_empty && KV_linked_list_is_empty(map.buckets[i]);
    }
    CU_ASSERT_TRUE(is_empty);

    CU_ASSERT_EQUAL(hash_table_size(map), 0);

    hash_table_destroy(&map, __hash_kv_free_string_int);
}

void test_hash_table_add(void)
{
    hash_table map = hash_table_create(26);

    string key = "a";
    int value = 1;
    KV entry = (KV){&key, &value};

    hash_table_insert(&map, entry, __hash_kv_copy_string_int, __hash_kv_hash_string_int, __hash_kv_equal_string_int);

    CU_ASSERT_EQUAL(hash_table_size(map), 1);

    key = "b";
    value = 2;
    entry = (KV){&key, &value};

    hash_table_insert(&map, entry, __hash_kv_copy_string_int, __hash_kv_hash_string_int, __hash_kv_equal_string_int);

    CU_ASSERT_EQUAL(hash_table_size(map), 2);

    hash_table_destroy(&map, __hash_kv_free_string_int);
}

void test_hash_table_add_overflow(void)
{
    int capacity = 42;
    long int number = 1;

    hash_table map;
    srand(42);

    for (long int i = 0; i < number; i++)
    {
        map = hash_table_create(capacity);

        for (long int j = 0; j < number; j++)
        {
            string *key = string_create((char[]){rand() % 26 + 97, '\0'});
            int value = rand() % 100;
            KV entry = {key, &value};

            hash_table_insert(&map, entry, __hash_kv_copy_string_int, __hash_kv_hash_string_int, __hash_kv_equal_string_int);
            string_free(key);
        }

        hash_table_destroy(&map, __hash_kv_free_string_int);
    }

    map = hash_table_create(capacity);

    for (long int i = 0; i < number; i++)
    {
        string *key = string_create((char[]){rand() % 26 + 97, '\0'});
        int value = rand() % 100;
        KV entry = {key, &value};

        hash_table_insert(&map, entry, __hash_kv_copy_string_int, __hash_kv_hash_string_int, __hash_kv_equal_string_int);
        string_free(key);
    }

    hash_table_destroy(&map, __hash_kv_free_string_int);
}

void test_hash_table_remove(void)
{
    hash_table map = hash_table_create(26);

    string key = "one";
    int value = 1;
    KV entry = (KV){&key, &value};

    hash_table_insert(&map, entry, __hash_kv_copy_string_int, __hash_kv_hash_string_int, __hash_kv_equal_string_int);
    CU_ASSERT_EQUAL(hash_table_size(map), 1);

    key = "two";
    value = 2;
    entry = (KV){&key, &value};

    hash_table_insert(&map, entry, __hash_kv_copy_string_int, __hash_kv_hash_string_int, __hash_kv_equal_string_int);
    CU_ASSERT_EQUAL(hash_table_size(map), 2);

    key = "one";
    hash_table_remove(&map, &key, __hash_kv_hash_string_int, __hash_kv_equal_string_int, __hash_kv_free_string_int);

    CU_ASSERT_EQUAL(hash_table_size(map), 1);

    hash_table_destroy(&map, __hash_kv_free_string_int);
}

void test_hash_table_find(void)
{
    hash_table map = hash_table_create(26);

    string *key1 = string_create("one");
    int value1 = 1;
    KV entry1 = (KV){key1, &value1};

    hash_table_insert(&map, entry1, __hash_kv_copy_string_int, __hash_kv_hash_string_int, __hash_kv_equal_string_int);

    string *key2 = string_create("two");
    int value2 = 2;
    KV entry2 = (KV){key2, &value2};

    hash_table_insert(&map, entry2, __hash_kv_copy_string_int, __hash_kv_hash_string_int, __hash_kv_equal_string_int);

    bool found = hash_table_has(map, key1, __hash_kv_hash_string_int, __hash_kv_equal_string_int);
    CU_ASSERT_TRUE(found);
    int *entry_found = hash_table_get(map, key1, __hash_kv_hash_string_int, __hash_kv_equal_string_int);
    CU_ASSERT_TRUE(int_equal(entry_found, &value1));

    found = hash_table_has(map, key2, __hash_kv_hash_string_int, __hash_kv_equal_string_int);
    CU_ASSERT_TRUE(found);
    entry_found = hash_table_get(map, key2, __hash_kv_hash_string_int, __hash_kv_equal_string_int);
    CU_ASSERT_TRUE(int_equal(entry_found, &value2));

    string *key3 = string_create("three");
    found = hash_table_has(map, key3, __hash_kv_hash_string_int, __hash_kv_equal_string_int);
    CU_ASSERT_FALSE(found);

    string_free(key1);
    string_free(key2);
    string_free(key3);

    hash_table_destroy(&map, __hash_kv_free_string_int);
}

void test_hash_table_destroy(void)
{
    int capacity = 26;
    hash_table map = hash_table_create(capacity);

    for (long int i = 0; i < capacity; i++)
    {
        map.buckets[i] = KV_linked_list_create();
        __hash_table_alphabet(&map.buckets[i]);
    }
    CU_ASSERT_EQUAL(hash_table_size(map), capacity * 26);

    hash_table_destroy(&map, __hash_kv_free_string_int);

    CU_ASSERT_EQUAL(hash_table_size(map), 0);
}