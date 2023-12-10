#ifndef __STRING_H__
#define __STRING_H__

#include <stdbool.h>
#include "base/generic.h"

typedef char *string;
any string_copy(any);
void string_free(any);
bool string_equal(any, any);
void string_print(any);

#endif // __STRING_H__