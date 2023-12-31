#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "base/kv_generic.h"
#include "base/kv_linked_list.h"
#include "base/hash_table.h"

hash_table hash_table_create(long int capacity)
{
    hash_table map;
    map.capacity = capacity;
    map.buckets = malloc(sizeof(KV_linked_list) * capacity);

    for (long int i = 0; i < capacity; i++)
    {
        map.buckets[i] = KV_linked_list_create();
    }

    return map;
}

void hash_table_destroy(hash_table *map, KV_free free_fn)
{
    for (long int i = 0; i < map->capacity; i++)
    {
        KV_linked_list_destroy(&map->buckets[i], free_fn);
    }

    free(map->buckets);
    map->capacity = 0;
}

void hash_table_insert(hash_table *map, KV entry, KV_copy copy_fn, KV_hash hash_fn, KV_compare equal_fn)
{
    long int index = hash_fn(entry) % map->capacity;
    KV_linked_list_add(&map->buckets[index], entry, copy_fn);
}

void hash_table_remove(hash_table *map, any key, KV_hash hash_fn, KV_compare equal_fn, KV_free free_fn)
{
    KV data = (KV){key, NULL};
    long int index = hash_fn(data) % map->capacity;

    KV_linked_list bucket = map->buckets[index];

    while (!KV_linked_list_is_empty(bucket))
    {
        KV entry = KV_linked_list_get_data(bucket);

        if (equal_fn(entry, data))
        {
            KV_linked_list_remove(&bucket, free_fn);
            map->buckets[index] = bucket;
            return;
        }
    }
}

any hash_table_get(hash_table map, any key, KV_hash hash_fn, KV_compare equal_fn)
{
    KV data = {key, NULL};
    long int index = hash_fn(data) % map.capacity;

    KV_linked_list bucket = map.buckets[index];

    while (!KV_linked_list_is_empty(bucket))
    {
        KV entry = KV_linked_list_get_data(bucket);

        if (equal_fn(entry, data))
        {
            return entry.value;
        }

        bucket = KV_linked_list_get_next(bucket);
    }

    assert(false);
    return NULL;
}

bool hash_table_has(hash_table map, any key, KV_hash hash_fn, KV_compare equal_fn)
{
    KV data = {key, NULL};
    long int index = hash_fn(data) % map.capacity;

    KV_linked_list bucket = map.buckets[index];

    while (!KV_linked_list_is_empty(bucket))
    {
        KV entry = KV_linked_list_get_data(bucket);

        if (equal_fn(entry, data))
        {
            return true;
        }

        bucket = KV_linked_list_get_next(bucket);
    }

    return false;
}

long int hash_table_size(hash_table map)
{
    unsigned long int size = 0;

    for (long int i = 0; i < map.capacity; i++)
    {
        size += KV_linked_list_length(map.buckets[i]);
    }

    return size;
}

void hash_table_print(hash_table map, KV_print print_fn)
{
    for (long int i = 0; i < map.capacity; i++)
    {
        printf("%ld: ", i);
        KV_linked_list_print(map.buckets[i], print_fn);
        printf("\n");
    }
}