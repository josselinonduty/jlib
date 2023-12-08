#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdlib.h>
#include <stdbool.h>
#include "base/generic.h"

static size_t const int_size = sizeof(long int);
any int_copy(any);
void int_free(any);
bool int_equal(any, any);
bool int_leq(any, any);
void int_print(any);

#endif // __TYPES_H__