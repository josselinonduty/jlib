#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "base/generic.h"
#include "types/statistic.h"

any stat_copy(any s)
{
    stat *copy = (stat *)malloc(sizeof(stat));
    copy->byte = ((stat *)s)->byte;
    copy->count = ((stat *)s)->count;
    return copy;
}

void stat_free(any s)
{
    free(s);
}

bool stat_leq(any a, any b)
{
    if (((stat *)a)->count == ((stat *)b)->count)
    {
        return ((stat *)a)->byte <= ((stat *)b)->byte;
    }

    return ((stat *)a)->count <= ((stat *)b)->count;
}

void stat_print(any s)
{
    printf("(%c: %ld)", ((stat *)s)->byte, ((stat *)s)->count);
}