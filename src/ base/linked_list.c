#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#include "base/generic.h"
#include "types/linked_list.h"

linked_list linked_list_create()
{
    return NULL;
}

bool linked_list_is_empty(linked_list ls)
{
    return ls == NULL;
}

linked_list linked_list_get_next(linked_list ls)
{
    if (linked_list_is_empty(ls))
    {
        errno = EINVAL;
        return linked_list_create();
    }

    return ls->next;
}

void linked_list_set_next(linked_list ls, linked_list next)
{
    if (linked_list_is_empty(ls))
    {
        errno = EINVAL;
        return;
    }

    ls->next = next;
}

any linked_list_get_data(linked_list ls)
{
    if (linked_list_is_empty(ls))
    {
        errno = EINVAL;
        return linked_list_create();
    }

    return ls->data;
}

void linked_list_set_data(linked_list ls, any data, generic_copy copy_fn)
{
    if (linked_list_is_empty(ls))
    {
        errno = EINVAL;
        return;
    }

    ls->data = copy_fn(data);
}

long int linked_list_length(linked_list ls)
{
    long int length = 0;

    while (!linked_list_is_empty(ls))
    {
        length++;
        ls = linked_list_get_next(ls);
    }

    return length;
}

void linked_list_add(linked_list *ls, any data, generic_copy copy_fn)
{
    linked_list new_node = malloc(sizeof(linked_list_node));
    if (NULL == new_node)
    {
        errno = ENOMEM;
        return;
    }

    linked_list_set_data(new_node, data, copy_fn);
    linked_list_set_next(new_node, *ls);
    *ls = new_node;
}

// Delete head node
void linked_list_remove(linked_list *ls, generic_free free_fn)
{
    if (linked_list_is_empty(*ls))
    {
        errno = EINVAL;
        return;
    }

    free_fn(linked_list_get_data(*ls));
    linked_list next = linked_list_get_next(*ls);
    free(*ls);
    *ls = next;
}

void linked_list_destroy(linked_list *ls, generic_free free_fn)
{
    while (!linked_list_is_empty(*ls))
    {
        linked_list_remove(ls, free_fn);
    }

    *ls = linked_list_create();
}

void linked_list_print(linked_list ls, generic_print print_fn)
{
    while (!linked_list_is_empty(ls))
    {
        print_fn(linked_list_get_data(ls));
        ls = linked_list_get_next(ls);
    }
}