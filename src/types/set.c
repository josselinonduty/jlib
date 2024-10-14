#include <stdbool.h>
#include <errno.h>

#include "base/kv_generic.h"
#include "datatypes/hash_table.h"
#include "datatypes/array.h"
#include "types/int.h"
#include "types/set.h"

set set_create(long int buckets, KV_copy copy_fn, KV_hash hash_fn, KV_compare equal_fn, KV_free free_fn)
{
    set set;

    set.data = hash_table_create(buckets);
    set.copy_fn = copy_fn;
    set.hash_fn = hash_fn;
    set.equal_fn = equal_fn;
    set.free_fn = free_fn;

    return set;
}

void set_destroy(set *set)
{
    if (NULL == set)
    {
        errno = EINVAL;
        return;
    }

    hash_table_destroy(&set->data, set->free_fn);
    set->copy_fn = NULL;
    set->hash_fn = NULL;
    set->equal_fn = NULL;
    set->free_fn = NULL;
}

bool set_is_empty(set set)
{
    return 0 == hash_table_size(set.data);
}

void set_add(set *set, any value)
{
    if (NULL == set)
    {
        errno = EINVAL;
        return;
    }

    KV entry = {value, value};
    hash_table_insert(&set->data, entry, set->copy_fn, set->hash_fn, set->equal_fn);
}

void set_remove(set *set, any value)
{
    if (NULL == set)
    {
        errno = EINVAL;
        return;
    }

    hash_table_remove(&set->data, value, set->hash_fn, set->equal_fn, set->free_fn);
}

bool set_has(set set, any value)
{
    if (set_is_empty(set))
    {
        return false;
    }

    return hash_table_has(set.data, value, set.hash_fn, set.equal_fn);
}

long int set_cardinal(set set)
{
    return hash_table_size(set.data);
}

// array set_to_array(set set);

void set_print(set set, KV_print print_fn)
{
    hash_table_print(set.data, print_fn);
}

// set set_union(set set1, set set2)
// {
//     assert(set1.copy_fn == set2.copy_fn);
//     assert(set1.hash_fn == set2.hash_fn);
//     assert(set1.equal_fn == set2.equal_fn);
//     assert(set1.free_fn == set2.free_fn);

//     long int set1_size = hash_table_size(set1.data);
//     long int set2_size = hash_table_size(set2.data);
//     long int buckets = set1_size <= set2_size ? set1_size : set2_size;

//     set set = set_create(buckets, set1.copy_fn, set1.hash_fn, set1.equal_fn, set1.free_fn);

//     return set;
// }
// set set_intersection(set set1, set set2);
// set set_difference(set set1, set set2);
// bool set_is_subset(set set1, set set2);
// bool set_is_equal(set set1, set set2);