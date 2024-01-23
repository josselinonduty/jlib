#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "base/generic.h"
#include "types/string.h"

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

void string_free(any value)
{
    free(*(string *)value);
    *(string *)value = NULL;
    free(value);
}

bool string_equal(any a, any b)
{
    return strcmp(*(string *)a, *(string *)b) == 0;
}

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