/**
 * \file hash_table.h
 * \brief Types and functions for hash map
 * \author Josselin Dulongcourty
 * \version 2.0.1
 * \date 2023-12-31
 */

#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stdbool.h>

#include "base/kv_generic.h"
#include "base/kv_linked_list.h"

/**
 * \typedef hash_table
 * \brief Hash map type.
 */
typedef struct hash_table hash_table;

/**
 * \internal
 * \struct hash_table
 * \brief Hash map type.
 */
struct hash_table
{
    long int capacity;
    KV_linked_list *buckets;
};

/**
 * \fn hash_table hash_table_create(long int capacity)
 * \brief Creates a hash map.
 * \param capacity The capacity of the hash map.
 * \return hash_table The created hash map.
 */
hash_table hash_table_create(long int capacity);

/**
 * \fn void hash_table_destroy(hash_table *map, KV_free free_fn)
 * \brief Destroys a hash map.
 * \param map The hash map to destroy.
 * \param free_fn The function to free the key and value.
 */
void hash_table_destroy(hash_table *map, KV_free free_fn);

/**
 * \fn void hash_table_insert(hash_table *map, KV entry, KV_copy copy_fn, KV_hash hash_fn, KV_compare equal_fn)
 * \brief Inserts a key-value pair into a hash map.
 * \param map The hash map to insert into.
 * \param entry The key-value pair to insert.
 * \param copy_fn The function to copy the key and value.
 * \param hash_fn The function to hash the key.
 * \param equal_fn The function to compare the keys.
 */
void hash_table_insert(hash_table *map, KV entry, KV_copy copy_fn, KV_hash hash_fn, KV_compare equal_fn);

/**
 * \fn void hash_table_remove(hash_table *map, any key, KV_hash hash_fn, KV_compare equal_fn, KV_free free_fn)
 * \brief Removes a key-value pair from a hash map.
 * \param map The hash map to remove from.
 * \param key The key of the key-value pair to remove.
 * \param hash_fn The function to hash the key.
 * \param equal_fn The function to compare the keys.
 * \param free_fn The function to free the key and value.
 */
void hash_table_remove(hash_table *map, any key, KV_hash hash_fn, KV_compare equal_fn, KV_free free_fn);

/**
 * \fn any hash_table_get(hash_table map, any key, KV_hash hash_fn, KV_compare equal_fn)
 * \brief Gets a value from a hash map.
 * \param map The hash map to get from.
 * \param key The key of the key-value pair to get.
 * \param hash_fn The function to hash the key.
 * \param equal_fn The function to compare the keys.
 * \return any The value of the key-value pair.
 */
any hash_table_get(hash_table map, any key, KV_hash hash_fn, KV_compare equal_fn);

/**
 * \fn bool hash_table_has(hash_table map, any key, KV_hash hash_fn, KV_compare equal_fn)
 * \brief Checks if a hash map has a key.
 * \param map The hash map to check.
 * \param key The key to check for.
 * \param hash_fn The function to hash the key.
 * \param equal_fn The function to compare the keys.
 * \return bool True if the hash map has the key, false otherwise.
 */
bool hash_table_has(hash_table map, any key, KV_hash hash_fn, KV_compare equal_fn);

/**
 * \fn long int hash_table_size(hash_table map)
 * \brief Gets the size of a hash map.
 * \param map The hash map to get the size of.
 * \return long int The size of the hash map.
 */
long int hash_table_size(hash_table map);

/**
 * \fn void hash_table_print(hash_table map, KV_print print_fn)
 * \brief Prints a hash map.
 * \param map The hash map to print.
 * \param print_fn The function to print the key and value.
 */
void hash_table_print(hash_table map, KV_print print_fn);

#endif // __HASH_TABLE_H__
