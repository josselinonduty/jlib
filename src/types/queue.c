#include <stdio.h>
#include <stdbool.h>
#include <errno.h>

#include "base/generic.h"
#include "base/int.h"
#include "base/linked_list.h"
#include "types/queue.h"

queue queue_create(generic_copy copy_fn, generic_free free_fn, generic_compare order_fn)
{
    queue q;

    q.head = linked_list_create();
    q.tail = q.head;

    q.copy = copy_fn;
    q.free = free_fn;
    q.order = order_fn;

    return q;
}

void queue_destroy(queue *q)
{
}

bool queue_is_empty(queue q)
{
    return linked_list_is_empty(q.head);
}

long int queue_length(queue q)
{
    return linked_list_length(q.head);
}

linked_list queue_get_head(queue q)
{
    return q.head;
}

linked_list queue_get_tail(queue q)
{
    return q.tail;
}

void queue_enqueue(queue *q, any data)
{
    if (NULL == q)
    {
        errno = EINVAL;
        return;
    }

    linked_list node = linked_list_create();
    linked_list_add(&node, data, q->copy);

    if (linked_list_is_empty(queue_get_head(*q)))
    {
        q->tail = node;
        q->head = node;
        return;
    }

    linked_list tail = queue_get_tail(*q);
    linked_list_set_next(tail, node);
    q->tail = node;
}

any queue_dequeue(queue *q)
{
    if (NULL == q)
    {
        errno = EINVAL;
        return NULL;
    }

    linked_list head = queue_get_head(*q);
    if (linked_list_is_empty(head))
    {
        errno = ENOMEM;
        return NULL;
    }

    any data = linked_list_get_data(head);
    q->head = linked_list_get_next(head);

    if (linked_list_is_empty(q->head))
    {
        q->tail = q->head;
    }

    free(head);

    return data;
}

void queue_print(queue q, generic_print print_fn)
{
    printf("\n");
    printf("  ^  out\n");
    printf("  |  \n");
    printf("\n");

    linked_list ls = queue_get_head(q);

    if (linked_list_is_empty(ls))
    {
        printf("[...]\n");
    }

    while (!linked_list_is_empty(ls))
    {
        printf("| ");
        print_fn(linked_list_get_data(ls));
        printf(" |");

        if (queue_get_head(q) == ls)
        {
            printf(" <- head");
        }

        if (queue_get_tail(q) == ls)
        {
            printf(" <- tail");
        }

        printf("\n");
        ls = linked_list_get_next(ls);
    }

    printf("\n");
    printf("  ^  in\n");
    printf("  |  ");
}

void queue_print_inline(queue q, generic_print print_fn)
{
    printf("\n[");
    linked_list ls = queue_get_head(q);

    while (!linked_list_is_empty(ls))
    {
        if (queue_get_head(q) == ls)
        {
            printf("(h)");
        }

        if (queue_get_tail(q) == ls)
        {
            printf("(t)");
        }

        print_fn(linked_list_get_data(ls));

        if (queue_get_tail(q) != ls)
        {
            printf(", ");
        }

        ls = linked_list_get_next(ls);
    }

    printf("]");
}