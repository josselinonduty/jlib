#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#include "base/generic.h"
#include "datatypes/doubly_linked_list.h"

doubly_linked_list doubly_linked_list_create()
{
    return NULL;
}

bool doubly_linked_list_is_empty(doubly_linked_list ls)
{
    return ls == NULL;
}

doubly_linked_list doubly_linked_list_get_next(doubly_linked_list ls)
{
    if (doubly_linked_list_is_empty(ls))
    {
        errno = EINVAL;
        return doubly_linked_list_create();
    }

    return ls->next;
}

doubly_linked_list doubly_linked_list_get_prev(doubly_linked_list ls)
{
    if (doubly_linked_list_is_empty(ls))
    {
        errno = EINVAL;
        return doubly_linked_list_create();
    }

    return ls->prev;
}

void doubly_linked_list_set_next(doubly_linked_list ls, doubly_linked_list next)
{
    if (doubly_linked_list_is_empty(ls))
    {
        errno = EINVAL;
        return;
    }

    ls->next = next;
}

void doubly_linked_list_set_prev(doubly_linked_list ls, doubly_linked_list prev)
{
    if (doubly_linked_list_is_empty(ls))
    {
        errno = EINVAL;
        return;
    }

    ls->prev = prev;
}

any doubly_linked_list_get_data(doubly_linked_list ls)
{
    if (doubly_linked_list_is_empty(ls))
    {
        errno = EINVAL;
        return doubly_linked_list_create();
    }

    return ls->data;
}

void doubly_linked_list_set_data(doubly_linked_list ls, any data, generic_copy copy_fn)
{
    if (doubly_linked_list_is_empty(ls))
    {
        errno = EINVAL;
        return;
    }

    ls->data = copy_fn(data);
}

long int doubly_linked_list_length(doubly_linked_list ls)
{
    long int length = 0;

    while (!doubly_linked_list_is_empty(ls))
    {
        length++;
        ls = doubly_linked_list_get_next(ls);
    }

    return length;
}

void doubly_linked_list_add(doubly_linked_list *ls, any data, generic_copy copy_fn)
{
    doubly_linked_list node = malloc(sizeof(struct doubly_linked_list_node));

    if (NULL == node)
    {
        errno = ENOMEM;
        return;
    }

    doubly_linked_list_set_data(node, data, copy_fn);
    doubly_linked_list_set_next(node, *ls);
    doubly_linked_list_set_prev(node, NULL);

    if (!doubly_linked_list_is_empty(*ls))
    {
        doubly_linked_list_set_prev(*ls, node);
    }

    *ls = node;
}

void doubly_linked_list_add_sorted(doubly_linked_list *ls, any data, generic_copy copy_fn, generic_compare compare_fn)
{
    doubly_linked_list node = malloc(sizeof(struct doubly_linked_list_node));

    if (NULL == node)
    {
        errno = ENOMEM;
        return;
    }

    doubly_linked_list_set_data(node, data, copy_fn);
    doubly_linked_list_set_next(node, NULL);
    doubly_linked_list_set_prev(node, NULL);

    if (doubly_linked_list_is_empty(*ls))
    {
        *ls = node;
        return;
    }

    doubly_linked_list current = *ls;
    doubly_linked_list prev = NULL;

    while (!doubly_linked_list_is_empty(current) && compare_fn(doubly_linked_list_get_data(current), data))
    {
        prev = current;
        current = doubly_linked_list_get_next(current);
    }

    if (doubly_linked_list_is_empty(prev))
    {
        doubly_linked_list_set_prev(node, prev);
        doubly_linked_list_set_next(node, current);
        doubly_linked_list_set_prev(current, node);
        *ls = node;
    }
    else if (doubly_linked_list_is_empty(current))
    {
        doubly_linked_list_set_prev(node, prev);
        doubly_linked_list_set_next(node, current);
        doubly_linked_list_set_next(prev, node);
    }
    else
    {
        doubly_linked_list_set_prev(node, prev);
        doubly_linked_list_set_next(node, current);
        doubly_linked_list_set_next(prev, node);
        doubly_linked_list_set_prev(current, node);
    }
}

void doubly_linked_list_remove(doubly_linked_list *ls, generic_free free_fn)
{
    if (doubly_linked_list_is_empty(*ls))
    {
        errno = EINVAL;
        return;
    }

    doubly_linked_list node = doubly_linked_list_get_next(*ls);

    if (!doubly_linked_list_is_empty(node))
    {
        doubly_linked_list_set_prev(node, doubly_linked_list_create());
    }

    free_fn(doubly_linked_list_get_data(*ls));
    free(*ls);

    *ls = node;
}

void doubly_linked_list_destroy(doubly_linked_list *ls, generic_free free_fn)
{
    while (!doubly_linked_list_is_empty(*ls))
    {
        doubly_linked_list_remove(ls, free_fn);
    }

    *ls = doubly_linked_list_create();
}

void doubly_linked_list_print(doubly_linked_list ls, generic_print print)
{
    while (!doubly_linked_list_is_empty(ls))
    {
        print(doubly_linked_list_get_data(ls));
        ls = doubly_linked_list_get_next(ls);
    }
}