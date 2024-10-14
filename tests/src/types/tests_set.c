#include <CUnit/CUnit.h>
#include <stdbool.h>

#include "types/int.h"
#include "types/set.h"

KV __set_int_copy(KV data)
{
    KV copy;
    copy.key = int_copy(data.key);

    return copy;
}

void __set_int_free(KV data)
{
    int_free(data.key);
}

long int __set_int_hash(KV data)
{
    return int_hash(data.key);
}

bool __set_int_equal(KV data1, KV data2)
{
    return int_equal(data1.key, data2.key);
}

void __set_int_print(KV data)
{
    int_print(data.key);
}

void test_set_create(void)
{
    set set = set_create(16, NULL, NULL, NULL, NULL);

    CU_ASSERT_TRUE(set_is_empty(set));
    CU_ASSERT_EQUAL(set_cardinal(set), 0);
    CU_ASSERT_FALSE(set_has(set, 0));

    set_destroy(&set);
}

void test_set_add(void)
{
    set set = set_create(16, __set_int_copy, __set_int_hash, __set_int_equal, __set_int_free);

    int i = 1;
    int j = 2;
    int k = 3;
    set_add(&set, &i);

    CU_ASSERT_FALSE(set_is_empty(set));
    CU_ASSERT_EQUAL(set_cardinal(set), 1);
    CU_ASSERT_TRUE(set_has(set, &i));
    CU_ASSERT_FALSE(set_has(set, &j));
    CU_ASSERT_FALSE(set_has(set, &k));

    set_add(&set, &j);

    CU_ASSERT_FALSE(set_is_empty(set));
    CU_ASSERT_EQUAL(set_cardinal(set), 2);
    CU_ASSERT_TRUE(set_has(set, &i));
    CU_ASSERT_TRUE(set_has(set, &j));
    CU_ASSERT_FALSE(set_has(set, &k));

    set_add(&set, &k);

    CU_ASSERT_FALSE(set_is_empty(set));
    CU_ASSERT_EQUAL(set_cardinal(set), 3);
    CU_ASSERT_TRUE(set_has(set, &i));
    CU_ASSERT_TRUE(set_has(set, &j));
    CU_ASSERT_TRUE(set_has(set, &k));

    set_destroy(&set);
}