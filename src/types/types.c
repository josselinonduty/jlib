#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "base/generic.h"
#include "types/types.h"

/**
 * @brief Copies an integer based on the generic copy function.
 * @param value The value to copy.
 * @return any The copied value.
 */
any int_copy(any value)
{
    any copy = malloc(int_size);
    if (NULL == copy)
    {
        errno = ENOMEM;
        return NULL;
    }

    memcpy(copy, value, int_size);

    return copy;
}

/**
 * @brief Frees an integer based on the generic free function.
 * @param value The value to free.
 */
void int_free(any value)
{
    int *v = (int *)value;
    free(v);
    v = NULL;
}

/**
 * @brief Compares two integers based on the generic compare function.
 * @param a The first integer.
 * @param b The second integer.
 * @return bool True if the integers are equal, false otherwise.
 */
bool int_equal(any a, any b)
{
    return *(int *)a == *(int *)b;
}

/**
 * @brief Compares two integers based on the generic compare function.
 * @param a The first integer.
 * @param b The second integer.
 * @return bool True if the first integer is greater than the second, false otherwise.
 */
bool int_leq(any a, any b)
{
    return *(int *)a <= *(int *)b;
}

/**
 * @brief Compares two integers based on the generic compare function.
 * @param a The first integer.
 * @param b The second integer.
 * @return bool True if the first integer is less than the second, false otherwise.
 */
void int_print(any value)
{
    printf("%d", *(int *)value);
}