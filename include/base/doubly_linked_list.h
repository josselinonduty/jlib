#ifndef __DOUBLY_LINKED_LIST_H__
#define __DOUBLY_LINKED_LIST_H__

#include <stdbool.h>
#include "base/generic.h"

/**
 * @private
 * @brief doubly linked list node
 * @typedef doubly_linked_list_node
 */
typedef struct doubly_linked_list_node doubly_linked_list_node;

/**
 * @brief Linked list
 * @typedef doubly_linked_list
 */
typedef doubly_linked_list_node *doubly_linked_list;

/**
 * @private
 * @brief doubly linked list node
 * @struct doubly_linked_list_node
 */
struct doubly_linked_list_node
{
    any data;
    doubly_linked_list next;
    doubly_linked_list prev;
};

/**
 * @brief Creates a new doubly linked list
 * @return doubly_linked_list
 */
doubly_linked_list
doubly_linked_list_create();

/**
 * @brief Checks if a doubly linked list is empty
 * @param ls Linked list
 * @return bool
 */
bool doubly_linked_list_is_empty(doubly_linked_list ls);

/**
 * @brief Gets the next node of a doubly linked list
 * @param ls Linked list
 * @return doubly_linked_list
 */
doubly_linked_list doubly_linked_list_get_next(doubly_linked_list ls);

/**
 * @brief Gets the previous node of a doubly linked list
 * @param ls Linked list
 * @return doubly_linked_list
 */
doubly_linked_list doubly_linked_list_get_prev(doubly_linked_list ls);

/**
 * @brief Sets the next node of a doubly linked list
 * @param ls Linked list
 * @param next Next node
 */
void doubly_linked_list_set_next(doubly_linked_list ls, doubly_linked_list next);

/**
 * @brief Sets the previous node of a doubly linked list
 * @param ls Linked list
 * @param prev Previous node
 */
void doubly_linked_list_set_prev(doubly_linked_list ls, doubly_linked_list prev);

/**
 * @brief Gets the data of a doubly linked list node
 * @param ls Linked list
 * @return any
 */
any doubly_linked_list_get_data(doubly_linked_list ls);

/**
 * @brief Sets the data of a doubly linked list node
 * @param ls Linked list
 * @param data Data
 * @param copy Copy function
 */
void doubly_linked_list_set_data(doubly_linked_list ls, any data, generic_copy copy);

/**
 * @brief Gets the length of a doubly linked list
 * @param ls Linked list
 * @return long int
 */
long int doubly_linked_list_length(doubly_linked_list ls);

/**
 * @brief Adds a node to a doubly linked list
 * @param ls Linked list
 * @param data Data
 * @param copy Copy function
 */
void doubly_linked_list_add(doubly_linked_list *ls, any data, generic_copy copy);

/**
 * @brief Adds a node to a doubly linked list in a sorted way
 * @param ls Linked list
 * @param data Data
 * @param copy Copy function
 * @param compare Compare function
 */
void doubly_linked_list_add_sorted(doubly_linked_list *ls, any data, generic_copy copy, generic_compare compare);

/**
 * @brief Removes a node from a doubly linked list
 * @param ls Linked list
 * @param free Free function
 */
void doubly_linked_list_remove(doubly_linked_list *ls, generic_free free);

/**
 * @brief Destroys a doubly linked list
 * @param ls Linked list
 * @param free Free function
 */
void doubly_linked_list_destroy(doubly_linked_list *ls, generic_free free);

/**
 * @brief Prints a doubly linked list
 * @param ls Linked list
 * @param print Print function
 */
void doubly_linked_list_print(doubly_linked_list ls, generic_print print);

#endif // __DOUBLY_LINKED_LIST_H__