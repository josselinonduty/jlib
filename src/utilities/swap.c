/**
 * @file utilities/exchange.c
 * @brief Functions related to swapping elements.
 * @author Josselin Dulongcourty
 * @version 1.0.0
 * @date 2023-12-08
 */

#include <errno.h>

#include "base/generic.h"
#include "utilities/swap.h"

void swap(any *a, any *b)
{
    if (a == NULL || b == NULL)
    {
        errno = EINVAL;
        return;
    }

    any temp = *a;
    *a = *b;
    *b = temp;

    errno = 0;
}