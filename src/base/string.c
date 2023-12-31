#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "base/generic.h"
#include "base/string.h"

/**
 * @brief Creates a string based on the generic create function.
 * @param value The value to create.
 * @return any The created value.
 */
any string_create(string value)
{
    string *str = malloc(sizeof(string));
    if (NULL == str)
    {
        errno = ENOMEM;
        return NULL;
    }

    *str = malloc(strlen(value) + 1);
    if (NULL == *str)
    {
        errno = ENOMEM;
        free(str);
        return NULL;
    }

    strcpy(*str, value);
    return str;
}

/**
 * @brief Copies a string based on the generic copy function.
 * @param value The value to copy.
 * @return any The copied value.
 */
any string_copy(any value)
{
    string *str = (string *)value;
    if (NULL == str)
    {
        errno = EINVAL;
        return NULL;
    }

    string *copy = malloc(sizeof(string));
    if (NULL == copy)
    {
        errno = ENOMEM;
        return NULL;
    }

    *copy = malloc(strlen(*str) + 1);
    if (NULL == *copy)
    {
        errno = ENOMEM;
        free(copy);
        return NULL;
    }

    strcpy(*copy, *str);
    return copy;
}

/**
 * @brief Frees a string based on the generic free function.
 * @param value The value to free.
 */
void string_free(any value)
{
    free(*(string *)value);
    *(string *)value = NULL;
    free(value);
}

/**
 * @brief Compares two strings based on the generic compare function.
 * @param a The first string.
 * @param b The second string.
 * @return bool True if the strings are equal, false otherwise.
 */
bool string_equal(any a, any b)
{
    return strcmp(*(string *)a, *(string *)b) == 0;
}

/**
 * @brief Prints a string based on the generic print function.
 * @param value The value to print.
 */
void string_print(any value)
{
    printf("%s", *(string *)value);
}

hash string_hash(any value)
{
    string str = *(string *)value;
    if (NULL == str)
    {
        errno = EINVAL;
        return 0;
    }

    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}