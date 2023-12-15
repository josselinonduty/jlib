#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>
#include "base/generic.h"
#include "base/linked_list.h"

/**
 * @private
 * @brief Queue
 * @typedef stack
 */
typedef struct stack stack;

/**
 * @brief Queue structure
 * @struct stack
 */
struct stack
{
    linked_list head;

    generic_copy copy;
    generic_free free;
    generic_compare order;
};

/**
 * @brief Create a new stack
 * @param copy_fn Generic copy function
 * @param free_fn Generic free function
 * @param order_fn Generic compare function
 */
stack stack_create(generic_copy copy_fn, generic_free free_fn, generic_compare order_fn);

/**
 * @brief Destroy the stack
 * @param q stack
 */
void stack_destroy(stack *q);

/**
 * @brief Check if the stack is empty
 * @param q stack
 * @return True if the stack is empty, false otherwise
 */
bool stack_is_empty(stack q);

/**
 * @brief Get the length of the stack
 * @param q stack
 * @return long int
 */
long int stack_length(stack q);

/**
 * @brief Get the head of the stack
 * @param q stack
 * @return linked_list
 */
linked_list stack_get_head(stack q);

/**
 * @brief Add an element at the beginning of the stack
 * @param q stack
 * @param data any
 */
void stack_stack(stack *q, any data);

/**
 * @brief Remove the first element of the stack
 * @param q stack
 * @return any
 */
any stack_unstack(stack *q);

/**
 * @brief Print the stack
 * @param q stack
 * @param print_fn Generic print function
 */
void stack_print(stack q, generic_print print_fn);

/**
 * @brief Print the stack inline
 * @param q stack
 * @param print_fn Generic print function
 */
void stack_print_inline(stack q, generic_print print_fn);

#endif // __STACK_H__