/**
 * @file set.h
 * @brief Types and functions for set
 * @author Josselin Dulongcourty
 * @version 1.0.0
 * @date 2024-01-23
 */

#ifndef __SET_H__
#define __SET_H__

#include <stdbool.h>

#include "base/generic.h"
#include "datatypes/hash_table.h"
#include "datatypes/array.h"

typedef struct set set;
struct set
{
    hash_table data;
    KV_copy copy_fn;
    KV_hash hash_fn;
    KV_compare equal_fn;
    KV_free free_fn;
};

set set_create(long int buckets, KV_copy copy_fn, KV_hash hash_fn, KV_compare equal_fn, KV_free free_fn);
void set_destroy(set *set);
bool set_is_empty(set set);
void set_add(set *set, any value);
void set_remove(set *set, any value);
bool set_has(set set, any value);
long int set_cardinal(set set);
// array set_to_array(set set);
void set_print(set set, KV_print print_fn);

// set set_union(set set1, set set2);
// set set_intersection(set set1, set set2);
// set set_difference(set set1, set set2);
// bool set_is_subset(set set1, set set2);
// bool set_is_equal(set set1, set set2);
// TODO: hash_table_iterator

#endif // __SET_H__