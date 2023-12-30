#include <CUnit/CUnit.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "base/generic.h"
#include "base/int.h"
#include "base/string.h"
#include "base/linked_list.h"
#include "base/hash_table.h"

hash_table_bucket __hash_table_alphabet(void)
{
    hash_table_bucket bucket = hash_table_bucket_create();

    for (int i = 97; i < 97 + 26; i++)
    {
        string key = malloc(sizeof(char) * 2);
        strcpy(key, (char[]){i, '\0'});

        int value = i;
        hash_table_entry entry = {
            .key = &key,
            .value = &value};

        hash_table_bucket_insert(&bucket, entry, string_copy, int_copy);

        free(key);
    }

    return bucket;
}

void test_hash_table_bucket(void)
{
    hash_table_bucket bucket = hash_table_bucket_create();

    CU_ASSERT_TRUE(hash_table_bucket_is_empty(bucket));

    string key = "one";
    int value = 1;
    hash_table_entry entry = {
        .key = &key,
        .value = &value};

    hash_table_bucket_insert(&bucket, entry, string_copy, int_copy);
    CU_ASSERT_FALSE(hash_table_bucket_is_empty(bucket));

    hash_table_bucket_destroy(&bucket, string_free, int_free);
    CU_ASSERT_TRUE(hash_table_bucket_is_empty(bucket));

    bucket = __hash_table_alphabet();

    CU_ASSERT_FALSE(hash_table_bucket_is_empty(bucket));

    hash_table_bucket_destroy(&bucket, string_free, int_free);
}

void test_hash_table_create(void)
{
    hash_table map = hash_table_create(26);

    CU_ASSERT_EQUAL(map.capacity, 26);

    bool is_empty = true;
    for (long int i = 0; i < map.capacity; i++)
    {
        is_empty = is_empty && hash_table_bucket_is_empty(map.buckets[i]);
    }
    CU_ASSERT_TRUE(is_empty);

    CU_ASSERT_EQUAL(hash_table_size(map), 0);

    hash_table_destroy(&map, string_free, int_free);
}

void test_hash_table_add(void)
{
    hash_table map = hash_table_create(26);

    string key = "one";
    int value = 1;
    hash_table_insert(&map, &key, string_hash, string_copy, &value, int_copy);

    CU_ASSERT_EQUAL(map.capacity, 26);

    bool is_empty = true;
    for (long int i = 0; i < map.capacity; i++)
    {
        is_empty = is_empty && hash_table_bucket_is_empty(map.buckets[i]);
    }
    CU_ASSERT_FALSE(is_empty);
    CU_ASSERT_EQUAL(hash_table_size(map), 1);

    hash_table_destroy(&map, string_free, int_free);
}

void test_hash_table_add_overflow(void)
{
    int capacity = 42;
    long int number = 1000;

    hash_table map;
    srand(42);

    for (long int i = 0; i < number; i++)
    {
        map = hash_table_create(capacity);

        for (long int j = 0; j < number; j++)
        {
            string key = malloc(sizeof(char) * 2);
            strcpy(key, (char[]){rand() % 26 + 97, '\0'});

            int value = rand() % 100;
            hash_table_insert(&map, &key, string_hash, string_copy, &value, int_copy);

            free(key);
        }

        hash_table_destroy(&map, string_free, int_free);
    }

    map = hash_table_create(capacity);

    for (long int i = 0; i < number; i++)
    {
        string key = malloc(sizeof(char) * 2);
        strcpy(key, (char[]){rand() % 26 + 97, '\0'});

        int value = rand() % 100;
        hash_table_insert(&map, &key, string_hash, string_copy, &value, int_copy);

        free(key);
    }

    hash_table_destroy(&map, string_free, int_free);
}

void test_hash_table_remove(void)
{
    hash_table map = hash_table_create(26);

    string key = "one";
    int value = 1;
    hash_table_insert(&map, &key, string_hash, string_copy, &value, int_copy);

    hash_table_remove(&map, &key, string_hash, string_equal, string_free, int_free);

    CU_ASSERT_EQUAL(hash_table_size(map), 0);

    hash_table_destroy(&map, string_free, int_free);
}

void test_hash_table_find(void)
{
    hash_table map = hash_table_create(26);

    string key = "one";
    srand(42);
    int value = rand() % 100;

    hash_table_insert(&map, &key, string_hash, string_copy, &value, int_copy);

    hash_table_entry *entry = hash_table_get(map, &key, string_hash, string_equal);

    CU_ASSERT_PTR_NOT_NULL(entry);
    CU_ASSERT_TRUE(string_equal(entry->key, &key));
    CU_ASSERT_TRUE(int_equal(entry->value, &value));

    hash_table_destroy(&map, string_free, int_free);
}

void test_hash_table_destroy(void)
{
    hash_table map = hash_table_create(26);

    for (long int i = 0; i < map.capacity; i++)
    {
        hash_table_bucket bucket = __hash_table_alphabet();
        map.buckets[i] = bucket;
    }

    hash_table_destroy(&map, string_free, int_free);

    CU_ASSERT_EQUAL(map.capacity, 0);
}