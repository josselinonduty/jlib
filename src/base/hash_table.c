#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "base/generic.h"
#include "base/linked_list.h"
#include "base/hash_table.h"

any hash_table_entry_copy(any entry_data)
{
    hash_table_entry_copy_transfer *data = (hash_table_entry_copy_transfer *)entry_data;

    hash_table_entry *copy = malloc(sizeof(hash_table_entry));

    copy->key = data->copy_key_fn(data->entry->key);
    copy->value = data->copy_value_fn(data->entry->value);

    return copy;
}

void hash_table_entry_free(any entry_data)
{
    hash_table_entry_free_transfer *data = (hash_table_entry_free_transfer *)entry_data;

    data->free_key_fn(data->entry->key);
    data->free_value_fn(data->entry->value);
    free(data->entry);
}

void hash_table_entry_print(any entry_data, generic_print print_key_fn, generic_print print_value_fn)
{
    hash_table_entry *data = (hash_table_entry *)entry_data;

    print_key_fn(data->key);
    printf("=>");
    print_value_fn(data->value);
    printf("\n");
}

hash_table_bucket hash_table_bucket_create(void)
{
    return linked_list_create();
}

bool hash_table_bucket_is_empty(hash_table_bucket bucket)
{
    return linked_list_is_empty(bucket);
}

hash_table_bucket hash_table_bucket_get_next(hash_table_bucket bucket)
{
    assert(!hash_table_bucket_is_empty(bucket));

    return linked_list_get_next(bucket);
}

void hash_table_bucket_set_next(hash_table_bucket bucket, hash_table_bucket next)
{
    assert(!hash_table_bucket_is_empty(bucket));

    linked_list_set_next(bucket, next);
}

hash_table_entry hash_table_bucket_get_data(hash_table_bucket bucket)
{
    assert(!hash_table_bucket_is_empty(bucket));

    return *(hash_table_entry *)linked_list_get_data(bucket);
}

void hash_table_bucket_set_data(hash_table_bucket bucket, hash_table_entry data, generic_copy copy_key_fn, generic_copy copy_value_fn)
{
    assert(!hash_table_bucket_is_empty(bucket));

    hash_table_entry entry = {data.key, data.value};
    hash_table_entry_copy_transfer transfer = {
        &entry,
        copy_key_fn,
        copy_value_fn};

    linked_list_set_data(bucket, &transfer, hash_table_entry_copy);
}

long int hash_table_bucket_length(hash_table_bucket bucket)
{
    return linked_list_length(bucket);
}

void hash_table_bucket_insert(hash_table_bucket *bucket, hash_table_entry data, generic_copy copy_key_fn, generic_copy copy_value_fn)
{
    hash_table_entry entry = {data.key, data.value};
    hash_table_entry_copy_transfer transfer = {
        &entry,
        copy_key_fn,
        copy_value_fn};

    linked_list_add(bucket, &transfer, hash_table_entry_copy);
}

void hash_table_bucket_remove(hash_table_bucket *bucket, generic_free free_key_fn, generic_free free_value_fn)
{
    hash_table_entry data = hash_table_bucket_get_data(*bucket);
    hash_table_bucket next = hash_table_bucket_get_next(*bucket);

    free_key_fn(data.key);
    free_value_fn(data.value);
    free((*bucket)->data);
    free(*bucket);

    *bucket = next;
}

void hash_table_bucket_destroy(hash_table_bucket *bucket, generic_free free_key_fn, generic_free free_value_fn)
{
    while (!hash_table_bucket_is_empty(*bucket))
    {
        hash_table_bucket_remove(bucket, free_key_fn, free_value_fn);
    }

    *bucket = hash_table_bucket_create();
}

void hash_table_bucket_print(hash_table_bucket bucket, generic_print print_key_fn, generic_print print_value_fn)
{
    while (!hash_table_bucket_is_empty(bucket))
    {
        hash_table_entry_print(linked_list_get_data(bucket), print_key_fn, print_value_fn);
        printf(" -> ");
        bucket = hash_table_bucket_get_next(bucket);
    }
}

hash_table hash_table_create(long int capacity)
{
    hash_table map;
    map.capacity = capacity;
    map.buckets = malloc(sizeof(hash_table_bucket) * capacity);

    for (long int i = 0; i < capacity; i++)
    {
        map.buckets[i] = hash_table_bucket_create();
    }

    return map;
}

void hash_table_destroy(hash_table *map, generic_free free_key_fn, generic_free free_value_fn)
{
    for (long int i = 0; i < map->capacity; i++)
    {
        hash_table_bucket_destroy(&map->buckets[i], free_key_fn, free_value_fn);
    }

    free(map->buckets);
    map->capacity = 0;
}

void hash_table_insert(hash_table *map, any key, generic_hash hash_key_fn, generic_copy copy_key_fn, any value, generic_copy copy_value_fn)
{
    long int index = hash_key_fn(key) % map->capacity;

    hash_table_entry entry = {key, value};
    hash_table_bucket_insert(&map->buckets[index], entry, copy_key_fn, copy_value_fn);
}

void hash_table_remove(hash_table *map, any key, generic_hash hash_key_fn, generic_compare equal_key_fn, generic_free free_key_fn, generic_free free_value_fn)
{
    long int index = hash_key_fn(key) % map->capacity;

    hash_table_bucket bucket = map->buckets[index];

    while (!hash_table_bucket_is_empty(bucket))
    {
        hash_table_entry entry = hash_table_bucket_get_data(bucket);

        if (equal_key_fn(entry.key, key))
        {
            hash_table_bucket_remove(&bucket, free_key_fn, free_value_fn);
            map->buckets[index] = bucket;
            return;
        }
    }
}

any hash_table_get(hash_table map, any key, generic_hash hash_key_fn, generic_compare equal_key_fn)
{
    long int index = hash_key_fn(key) % map.capacity;

    hash_table_bucket bucket = map.buckets[index];

    while (!hash_table_bucket_is_empty(bucket))
    {
        hash_table_entry entry = hash_table_bucket_get_data(bucket);

        if (equal_key_fn(entry.key, key))
        {
            return entry.value;
        }

        bucket = hash_table_bucket_get_next(bucket);
    }

    return NULL;
}

bool hash_table_has(hash_table map, any key, generic_hash hash_key_fn, generic_compare equal_key_fn)
{
    long int index = hash_key_fn(key) % map.capacity;

    hash_table_bucket bucket = map.buckets[index];

    while (!hash_table_bucket_is_empty(bucket))
    {
        hash_table_entry entry = hash_table_bucket_get_data(bucket);

        if (equal_key_fn(entry.key, key))
        {
            return true;
        }

        bucket = hash_table_bucket_get_next(bucket);
    }

    return false;
}

long int hash_table_size(hash_table map)
{
    unsigned long int size = 0;

    for (long int i = 0; i < map.capacity; i++)
    {
        size += hash_table_bucket_length(map.buckets[i]);
    }

    return size;
}

void hash_table_print(hash_table map, generic_print print_key_fn, generic_print print_value_fn)
{
    for (long int i = 0; i < map.capacity; i++)
    {
        printf("%ld: ", i);
        hash_table_bucket_print(map.buckets[i], print_key_fn, print_value_fn);
        printf("\n");
    }
}