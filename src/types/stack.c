#include <stdio.h>
#include <stdbool.h>
#include <errno.h>

#include "base/generic.h"
#include "base/int.h"
#include "base/linked_list.h"
#include "types/stack.h"

stack stack_create(generic_copy copy_fn, generic_free free_fn, generic_compare order_fn)
{
    stack q;

    q.head = linked_list_create();

    q.copy = copy_fn;
    q.free = free_fn;
    q.order = order_fn;

    return q;
}

void stack_destroy(stack *q)
{
    if (NULL == q)
    {
        errno = EINVAL;
        return;
    }

    linked_list head = stack_get_head(*q);
    linked_list_destroy(&head, q->free);
    q->head = head;
}

bool stack_is_empty(stack q)
{
    return linked_list_is_empty(q.head);
}

long int stack_length(stack q)
{
    return linked_list_length(q.head);
}

linked_list stack_get_head(stack q)
{
    return q.head;
}

void stack_stack(stack *q, any data)
{
    if (NULL == q)
    {
        errno = EINVAL;
        return;
    }

    linked_list head = stack_get_head(*q);

    linked_list_add(&head, data, q->copy);
    q->head = head;
}

any stack_unstack(stack *q)
{
    if (NULL == q)
    {
        errno = EINVAL;
        return NULL;
    }

    linked_list head = stack_get_head(*q);
    if (linked_list_is_empty(head))
    {
        errno = ENOMEM;
        return NULL;
    }

    any data = q->copy(linked_list_get_data(head));

    linked_list_remove(&head, q->free);
    q->head = head;

    return data;
}

void stack_print(stack q, generic_print print_fn)
{
    printf("\n");
    printf("|   |\n");

    linked_list ls = stack_get_head(q);

    while (!linked_list_is_empty(ls))
    {
        printf("| ");
        print_fn(linked_list_get_data(ls));
        printf(" |");

        printf("\n");
        ls = linked_list_get_next(ls);
    }

    printf("|___|\n");
}

void stack_print_inline(stack q, generic_print print_fn)
{
    printf("\n[");
    linked_list ls = stack_get_head(q);

    if (linked_list_is_empty(ls))
    {
        goto skip;
    }
loop:
    print_fn(linked_list_get_data(ls));

    ls = linked_list_get_next(ls);

    if (!linked_list_is_empty(ls))
    {
        printf(", ");
        goto loop;
    }
skip:
    printf("]");
}