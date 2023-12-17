#ifndef __STATISTIC_H__
#define __STATISTIC_H__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "base/generic.h"

typedef struct stat
{
    int byte;
    long int count;
} stat;

any stat_copy(any s);

void stat_free(any s);

bool stat_leq(any a, any b);

void stat_print(any s);

#endif // __STATISTIC_H__