#include <stdio.h>
#include <stdbool.h>
#include <errno.h>

#include "base/generic.h"
#include "types/linked_list.h"

linked_list list_create(void)
{
    return NULL;
}

bool list_is_empty(linked_list ls)
{
    return ls == NULL;
}

void list_set_next(linked_list ls, linked_list next)
{
    if (list_is_empty(ls))
    {
        errno = EINVAL;
        return;
    }

    ls->next = next;
}

linked_list list_get_next(linked_list ls)
{
    if (list_is_empty(ls))
    {
        errno = EINVAL;
        return NULL;
    }

    return ls->next;
}

any list_get_data(linked_list ls)
{
    if (list_is_empty(ls))
    {
        errno = EINVAL;
        return NULL;
    }

    return ls->data;
}

void list_set_data(linked_list ls, any data, generic_copy copy_fn)
{
    if (list_is_empty(ls))
    {
        errno = EINVAL;
        return;
    }

    ls->data = copy_fn(data);
}

long int list_length(linked_list ls)
{
    long int length = 0;
    while (!list_is_empty(ls))
    {
        length++;
        ls = list_get_next(ls);
    }

    return length;
}

void list_destroy(linked_list *ls, generic_free free_fn)
{
    while (!list_is_empty(*ls))
    {
        linked_list next = list_get_next(*ls);
        free_fn(list_get_data(*ls));
        free(*ls);
        *ls = next;
    }

    *ls = NULL;
}

void list_remove(linked_list *ls, generic_free free_fn)
{
    if (list_is_empty(*ls))
    {
        errno = EINVAL;
        return;
    }

    linked_list next = list_get_next(*ls);
    free_fn(list_get_data(*ls));
    free(*ls);
    *ls = next;
}

void list_add(linked_list *ls, any data, generic_copy copy_fn)
{
    linked_list new_node = (linked_list)malloc(sizeof(linked_list_node));
    if (new_node == NULL)
    {
        errno = ENOMEM;
        return;
    }

    list_set_data(new_node, data, copy_fn);
    list_set_next(new_node, *ls);
    *ls = new_node;
}