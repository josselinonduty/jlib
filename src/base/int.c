#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "base/generic.h"
#include "base/int.h"

/**
 * @brief Copies an integer based on the generic copy function.
 * @param value The value to copy.
 * @return any The copied value.
 */
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
bool int_geq(any a, any b)
{
    return *(int *)a >= *(int *)b;
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

/**
 * @brief Hashes an integer based on the generic hash function.
 * @param value The value to hash.
 * @return hash The hash of the value.
 */
hash int_hash(any value)
{
    int v = *(int *)value;
    v = (v + 0x7ed55d16) + (v << 12);
    v = (v ^ 0xc761c23c) ^ (v >> 19);
    v = (v + 0x165667b1) + (v << 5);
    v = (v + 0xd3a2646c) ^ (v << 9);

    return v ^ (v >> 16);
}