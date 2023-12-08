#ifndef __TESTS_H__
#define __TESTS_H__

#include <stdio.h>

void test_utils_exchange(void);

void test_int_copy(void);
void test_int_equal(void);
void test_int_leq(void);

void test_array_create(void);
void test_array_destroy(void);
void test_array_free(void);
void test_array_add(void);
void test_array_add_multiple(void);
void test_array_add_overflow(void);
void test_array_insert(void);
void test_array_resize(void);

#endif