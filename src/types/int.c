#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "base/generic.h"
#include "types/int.h"

any int_copy(any value)
{
    any copy = malloc(sizeof(long int));
    if (NULL == copy)
    {
        errno = ENOMEM;
        return NULL;
    }

    memcpy(copy, value, sizeof(long int));

    return copy;
}

void int_free(any value)
{
    int *v = (int *)value;
    free(v);
    v = NULL;
}

bool int_equal(any a, any b)
{
    return *(int *)a == *(int *)b;
}

bool int_leq(any a, any b)
{
    return *(int *)a <= *(int *)b;
}

bool int_geq(any a, any b)
{
    return *(int *)a >= *(int *)b;
}

void int_print(any value)
{
    printf("%d", *(int *)value);
}

hash int_hash(any value)
{
    int v = *(int *)value;
    v = (v + 0x7ed55d16) + (v << 12);
    v = (v ^ 0xc761c23c) ^ (v >> 19);
    v = (v + 0x165667b1) + (v << 5);
    v = (v + 0xd3a2646c) ^ (v << 9);

    return v ^ (v >> 16);
}