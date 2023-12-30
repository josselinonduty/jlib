#ifndef __INT_H__
#define __INT_H__

#include <stdbool.h>
#include "base/generic.h"

any int_copy(any);
void int_free(any);
bool int_equal(any, any);
bool int_leq(any, any);
bool int_geq(any, any);
void int_print(any);
hash int_hash(any);

#endif // __INT_H__