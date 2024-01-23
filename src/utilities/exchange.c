/**
 * @file utilities/exchange.c
 * @brief Functions related to swapping elements.
 * @author Josselin Dulongcourty
 * @version 1.0.0
 * @date 2023-12-08
 */

#include <errno.h>

#include "base/generic.h"
#include "utilities/exchange.h"

/**
 * @brief Swap two elements by reference.
 * @param a The first element.
 * @param b The second element.
 *
 * @throw EINVAL if either a or b is NULL.
 * @example
 * @code{.c}
 * any a = 1;
 * any b = 2;
 *
 * exchange(&a, &b);
 * // a = 2, b = 1
 * @endcode
 */
void exchange(any *a, any *b)
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