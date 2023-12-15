#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdbool.h>
#include "base/generic.h"

/**
 * @private
 * @brief linked list node
 * @typedef linked_list_node
 */
typedef struct linked_list_node linked_list_node;

/**
 * @brief Linked list
 * @typedef linked_list
 */
typedef linked_list_node *linked_list;

/**
 * @private
 * @brief linked list node
 * @struct linked_list_node
 */
struct linked_list_node
{
    any data;
    linked_list next;
};

/**
 * @brief Creates a new linked list
 * @return linked_list
 */
linked_list
linked_list_create();

/**
 * @brief Checks if a linked list is empty
 * @param ls Linked list
 * @return bool
 */
bool linked_list_is_empty(linked_list ls);

/**
 * @brief Gets the next node of a linked list
 * @param ls Linked list
 * @return linked_list
 */
linked_list linked_list_get_next(linked_list ls);

/**
 * @brief Sets the next node of a linked list
 * @param ls Linked list
 * @param next Next node
 */
void linked_list_set_next(linked_list ls, linked_list next);

/**
 * @brief Gets the data of a linked list node
 * @param ls Linked list
 * @return any
 */
any linked_list_get_data(linked_list ls);

/**
 * @brief Sets the data of a linked list node
 * @param ls Linked list
 * @param data Data
 * @param copy Copy function
 */
void linked_list_set_data(linked_list ls, any data, generic_copy copy);

/**
 * @brief Gets the length of a linked list
 * @param ls Linked list
 * @return long int
 */
long int linked_list_length(linked_list ls);

/**
 * @brief Adds a node to a linked list
 * @param ls Linked list
 * @param data Data
 * @param copy Copy function
 */
void linked_list_add(linked_list *ls, any data, generic_copy copy);

/**
 * @brief Adds a node to a linked list in a sorted way
 * @param ls Linked list
 * @param data Data
 * @param copy Copy function
 * @param compare Compare function
 */
void linked_list_add_sorted(linked_list *ls, any data, generic_copy copy, generic_compare compare);

/**
 * @brief Removes a node from a linked list
 * @param ls Linked list
 * @param free Free function
 */
void linked_list_remove(linked_list *ls, generic_free free);

/**
 * @brief Destroys a linked list
 * @param ls Linked list
 * @param free Free function
 */
void linked_list_destroy(linked_list *ls, generic_free free);

/**
 * @brief Prints a linked list
 * @param ls Linked list
 * @param print Print function
 */
void linked_list_print(linked_list ls, generic_print print);

#endif // __LINKED_LIST_H__