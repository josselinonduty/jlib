#include <stdbool.h>
#include <stdio.h>
#include <errno.h>

#include "base/kv_generic.h"
#include "base/kv_linked_list.h"

KV_linked_list KV_linked_list_create(void)
{
    return NULL;
}

bool KV_linked_list_is_empty(KV_linked_list kvls)
{
    return NULL == kvls;
}

KV_linked_list KV_linked_list_get_next(KV_linked_list kvls)
{
    if (KV_linked_list_is_empty(kvls))
    {
        errno = EINVAL;
        return NULL;
    }

    return kvls->next;
}

void KV_linked_list_set_next(KV_linked_list kvls, KV_linked_list next)
{
    if (KV_linked_list_is_empty(kvls))
    {
        errno = EINVAL;
        return;
    }

    kvls->next = next;
}

KV KV_linked_list_get_data(KV_linked_list kvls)
{
    if (KV_linked_list_is_empty(kvls))
    {
        errno = EINVAL;
        return (KV){NULL, NULL};
    }

    return kvls->data;
}

void KV_linked_list_set_data(KV_linked_list kvls, KV data, KV_copy copy_fn)
{
    if (KV_linked_list_is_empty(kvls))
    {
        errno = EINVAL;
        return;
    }

    kvls->data = copy_fn(data);
}

long int KV_linked_list_length(KV_linked_list kvls)
{
    long int length = 0;

    while (!KV_linked_list_is_empty(kvls))
    {
        length++;
        kvls = kvls->next;
    }

    return length;
}

void KV_linked_list_add(KV_linked_list *kvls, KV data, KV_copy copy_fn)
{
    KV_linked_list new_node = (KV_linked_list)malloc(sizeof(KV_linked_list_node));
    if (NULL == new_node)
    {
        errno = ENOMEM;
        return;
    }

    KV_linked_list_set_data(new_node, data, copy_fn);
    KV_linked_list_set_next(new_node, *kvls);
    *kvls = new_node;
}

void KV_linked_list_add_sorted(KV_linked_list *kvls, KV data, KV_copy copy_fn, KV_compare compare_fn)
{
    if (KV_linked_list_is_empty(*kvls))
    {
        KV_linked_list_add(kvls, data, copy_fn);
        return;
    }

    if (!compare_fn(KV_linked_list_get_data(*kvls), data))
    {
        KV_linked_list_add(kvls, data, copy_fn);
        return;
    }

    KV_linked_list next = KV_linked_list_get_next(*kvls);
    KV_linked_list_add_sorted(&next, data, copy_fn, compare_fn);
    KV_linked_list_set_next(*kvls, next);
}

void KV_linked_list_remove(KV_linked_list *kvls, KV_free free_fn)
{
    if (KV_linked_list_is_empty(*kvls))
    {
        errno = EINVAL;
        return;
    }

    KV_linked_list next = KV_linked_list_get_next(*kvls);
    free_fn(KV_linked_list_get_data(*kvls));
    free(*kvls);
    *kvls = next;
}

void KV_linked_list_destroy(KV_linked_list *kvls, KV_free free_fn)
{
    while (!KV_linked_list_is_empty(*kvls))
    {
        KV_linked_list_remove(kvls, free_fn);
    }

    *kvls = KV_linked_list_create();
}

void KV_linked_list_print(KV_linked_list kvls, KV_print print_fn)
{
    while (!KV_linked_list_is_empty(kvls))
    {
        print_fn(KV_linked_list_get_data(kvls));
        kvls = KV_linked_list_get_next(kvls);

        if (!KV_linked_list_is_empty(kvls))
        {
            printf("->");
        }
    }
}