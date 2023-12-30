#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stdbool.h>

#include "base/generic.h"
#include "base/linked_list.h"

/**
 * \struct hash_table_entry
 * \brief Hash map entry type.
 */
typedef struct hash_table_entry hash_table_entry;

/**
 * \internal
 * \struct hash_table_entry
 * \brief Hash map entry type.
 */
struct hash_table_entry
{
    any key;
    any value;
};

typedef struct hash_table_entry_copy_transfer hash_table_entry_copy_transfer;

/**
 * \internal
 * \struct hash_table_entry_copy_transfer
 * \brief Hash map entry copy transfer type.
 */
struct hash_table_entry_copy_transfer
{
    hash_table_entry *entry;

    generic_copy copy_key_fn;
    generic_copy copy_value_fn;
};

typedef struct hash_table_entry_free_transfer hash_table_entry_free_transfer;

/**
 * \internal
 * \struct hash_table_entry_free_transfer
 * \brief Hash map entry free transfer type.
 */
struct hash_table_entry_free_transfer
{
    hash_table_entry *entry;

    generic_free free_key_fn;
    generic_free free_value_fn;
};

/**
 * \fn any hash_table_entry_copy(any entry_data)
 * \brief Copies a hash map entry.
 * \return The copied hash map entry.
 * \param entry_data The hash map entry to copy.
 */
any hash_table_entry_copy(any entry_data);

/**
 * \fn void hash_table_entry_free(any entry_data)
 * \brief Frees a hash map entry.
 * \param entry_data The hash map entry to free.
 */
void hash_table_entry_free(any entry_data);

/**
 * \fn void hash_table_entry_print(any entry_data, generic_print print_key_fn, generic_print print_value_fn)
 * \brief Prints a hash map entry.
 * \param entry_data The hash map entry to print.
 * \param print_key_fn The function to print the key.
 * \param print_value_fn The function to print the value.
 */
void hash_table_entry_print(any entry_data, generic_print print_key_fn, generic_print print_value_fn);

/**
 * \typedef linked_list hash_table_bucket
 * \brief Hash map bucket type.
 */
typedef linked_list hash_table_bucket;

/**
 * \fn hash_table_bucket hash_table_bucket_create(void)
 * \brief Creates a hash map bucket.
 * \return The created hash map bucket.
 */
hash_table_bucket hash_table_bucket_create(void);

/**
 * \fn bool hash_table_bucket_is_empty(hash_table_bucket bucket)
 * \brief Checks if a hash map bucket is empty.
 * \return Whether the hash map bucket is empty.
 * \param bucket The hash map bucket to check.
 */
bool hash_table_bucket_is_empty(hash_table_bucket bucket);

/**
 * \fn hash_table_bucket hash_table_bucket_get_next(hash_table_bucket bucket)
 * \brief Gets the next hash map bucket.
 * \return The next hash map bucket.
 * \param bucket The hash map bucket to get the next hash map bucket from.
 */
hash_table_bucket hash_table_bucket_get_next(hash_table_bucket bucket);

/**
 * \fn void hash_table_bucket_set_next(hash_table_bucket bucket, hash_table_bucket next)
 * \brief Sets the next hash map bucket.
 * \param bucket The hash map bucket to set the next hash map bucket from.
 * \param next The next hash map bucket to set.
 */
void hash_table_bucket_set_next(hash_table_bucket bucket, hash_table_bucket next);

/**
 * \fn hash_table_entry hash_table_bucket_get_data(hash_table_bucket bucket)
 * \brief Gets the data of a hash map bucket.
 * \return The data of the hash map bucket.
 * \param bucket The hash map bucket to get the data from.
 */
hash_table_entry hash_table_bucket_get_data(hash_table_bucket bucket);

/**
 * \fn void hash_table_bucket_set_data(hash_table_bucket bucket, hash_table_entry data, generic_copy copy_key_fn, generic_copy copy_value_fn)
 * \brief Sets the data of a hash map bucket.
 * \param bucket The hash map bucket to set the data from.
 * \param data The data to set.
 * \param copy_key_fn The function to copy the key.
 * \param copy_value_fn The function to copy the value.
 */
void hash_table_bucket_set_data(hash_table_bucket bucket, hash_table_entry data, generic_copy copy_key_fn, generic_copy copy_value_fn);

/**
 * \fn long int hash_table_bucket_length(hash_table_bucket bucket)
 * \brief Gets the length of a hash map bucket.
 * \return The length of the hash map bucket.
 * \param bucket The hash map bucket to get the length from.
 */
long int hash_table_bucket_length(hash_table_bucket bucket);

/**
 * \fn void hash_table_bucket_insert(hash_table_bucket *bucket, hash_table_entry data, generic_copy copy_key_fn, generic_copy copy_value_fn)
 * \brief Inserts data into a hash map bucket.
 * \param bucket The hash map bucket to insert the data into.
 * \param data The data to insert.
 * \param copy_key_fn The function to copy the key.
 * \param copy_value_fn The function to copy the value.
 */
void hash_table_bucket_insert(hash_table_bucket *bucket, hash_table_entry data, generic_copy copy_key_fn, generic_copy copy_value_fn);

/**
 * \fn void hash_table_bucket_remove(hash_table_bucket *bucket, generic_free free_key_fn, generic_free free_value_fn)
 * \brief Removes data from a hash map bucket.
 * \param bucket The hash map bucket to remove the data from.
 * \param free_key_fn The function to free the key.
 * \param free_value_fn The function to free the value.
 */
void hash_table_bucket_remove(hash_table_bucket *bucket, generic_free free_key_fn, generic_free free_value_fn);

/**
 * \fn void hash_table_bucket_destroy(hash_table_bucket *bucket, generic_free free_key_fn, generic_free free_value_fn)
 * \brief Destroys a hash map bucket.
 * \param bucket The hash map bucket to destroy.
 * \param free_key_fn The function to free the key.
 * \param free_value_fn The function to free the value.
 */
void hash_table_bucket_destroy(hash_table_bucket *bucket, generic_free free_key_fn, generic_free free_value_fn);

/**
 * \fn void hash_table_bucket_print(hash_table_bucket bucket, generic_print print_key_fn, generic_print print_value_fn)
 * \brief Prints a hash map bucket.
 * \param bucket The hash map bucket to print.
 * \param print_key_fn The function to print the key.
 * \param print_value_fn The function to print the value.
 */
void hash_table_bucket_print(hash_table_bucket bucket, generic_print print_key_fn, generic_print print_value_fn);

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
    hash_table_bucket *buckets;
};

/**
 * \fn hash_table hash_table_create(long int capacity)
 * \brief Creates a hash map.
 * \return The created hash map.
 * \param capacity The capacity of the hash map.
 */
hash_table hash_table_create(long int capacity);

/**
 * \fn void hash_table_destroy(hash_table *map, generic_free free_key_fn, generic_free free_value_fn)
 * \brief Destroys a hash map.
 * \param map The hash map to destroy.
 * \param free_key_fn The function to free the key.
 * \param free_value_fn The function to free the value.
 */
void hash_table_destroy(hash_table *map, generic_free free_key_fn, generic_free free_value_fn);

/**
 * \fn void hash_table_insert(hash_table *map, any key, generic_hash hash_key_fn, generic_copy copy_key_fn, any value, generic_copy copy_value_fn)
 * \brief Inserts data into a hash map.
 * \param map The hash map to insert the data into.
 * \param key The key to insert.
 * \param hash_key_fn The function to hash the key.
 * \param copy_key_fn The function to copy the key.
 * \param value The value to insert.
 * \param copy_value_fn The function to copy the value.
 */
void hash_table_insert(hash_table *map, any key, generic_hash hash_key_fn, generic_copy copy_key_fn, any value, generic_copy copy_value_fn);

/**
 * \fn void hash_table_remove(hash_table *map, any key, generic_hash hash_key_fn, generic_compare equal_key_fn, generic_free free_key_fn, generic_free free_value_fn)
 * \brief Removes data from a hash map.
 * \param map The hash map to remove the data from.
 * \param key The key to remove.
 * \param hash_key_fn The function to hash the key.
 * \param equal_key_fn The function to compare the key.
 * \param free_key_fn The function to free the key.
 * \param free_value_fn The function to free the value.
 */
void hash_table_remove(hash_table *map, any key, generic_hash hash_key_fn, generic_compare equal_key_fn, generic_free free_key_fn, generic_free free_value_fn);

/**
 * \fn any hash_table_get(hash_table map, any key, generic_hash hash_key_fn, generic_compare equal_key_fn)
 * \brief Gets data from a hash map.
 * \return The data from the hash map.
 * \param map The hash map to get the data from.
 * \param key The key to get.
 * \param hash_key_fn The function to hash the key.
 * \param equal_key_fn The function to compare the key.
 */
any hash_table_get(hash_table map, any key, generic_hash hash_key_fn, generic_compare equal_key_fn);

/**
 * \fn bool hash_table_has(hash_table map, any key, generic_hash hash_key_fn, generic_compare equal_key_fn)
 * \brief Checks if a hash map has data.
 * \return Whether the hash map has data.
 * \param map The hash map to check.
 * \param key The key to check.
 * \param hash_key_fn The function to hash the key.
 * \param equal_key_fn The function to compare the key.
 */
bool hash_table_has(hash_table map, any key, generic_hash hash_key_fn, generic_compare equal_key_fn);

/**
 * \fn long int hash_table_size(hash_table map)
 * \brief Gets the size of a hash map.
 * \return The size of the hash map.
 * \param map The hash map to get the size from.
 */
long int hash_table_size(hash_table map);

/**
 * \fn void hash_table_print(hash_table map, generic_print print_key_fn, generic_print print_value_fn)
 * \brief Prints a hash map.
 * \param map The hash map to print.
 * \param print_key_fn The function to print the key.
 * \param print_value_fn The function to print the value.
 */
void hash_table_print(hash_table map, generic_print print_key_fn, generic_print print_value_fn);

#endif // __HASH_MAP_H__
