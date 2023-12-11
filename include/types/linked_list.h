/**
 * @file linked_list.h
 * @brief Linked list type and functions.
 * @author Josselin Dulongcourty
 * @version 1.0
 * @date 2023-12-10
 */

#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdbool.h>
#include <stdlib.h>

#include "base/generic.h"

/**
 * @private
 * @brief The linked list node
 * @typedef linked_list_node
 */
typedef struct linked_list_node linked_list_node;

/**
 * @private
 * @brief The linked list
 * @typedef linked_list
 */
typedef linked_list_node *linked_list;

struct linked_list_node
{
    any data;
    linked_list next;
};

/**
 * @brief Create a new linked list
 * @return linked_list
 */
linked_list list_create(void);

/**
 * @brief Check if a linked list is empty
 * @param ls The linked list
 * @return bool
 */
bool list_is_empty(linked_list ls);

/**
 * @brief Set the next node of a linked list
 * @param ls The linked list
 * @param next The next node
 */
void list_set_next(linked_list ls, linked_list next);

/**
 * @brief Get the next node of a linked list
 * @param ls The linked list
 * @return linked_list
 */
linked_list list_get_next(linked_list ls);

/**
 * @brief Set the data of a linked list node
 * @param ls The linked list
 * @param data The data
 * @param copy The copy function
 */
void list_set_data(linked_list ls, any data, generic_copy copy_fn);

/**
 * @brief Get the data of a linked list node
 * @param ls The linked list
 * @return linked_list
 */
any list_get_data(linked_list ls);

/**
 * @brief Destroy a linked list
 * @param ls The linked list
 * @param free The free function
 */
void list_destroy(linked_list *ls, generic_free free_fn);

/**
 * @brief Get the length of a linked list
 * @param ls The linked list
 * @return long int
 */
long int list_length(linked_list ls);

/**
 * @brief Remove the head of a linked list
 * @param ls The linked list
 * @param free The free function
 */
void list_remove(linked_list *ls, generic_free free_fn);

/**
 * @brief Add a node to the head of a linked list
 * @param ls The linked list
 * @param data The data
 * @param copy The copy function
 */
void list_add(linked_list *ls, any data, generic_copy copy_fn);

#endif // __LINKED_LIST_H__