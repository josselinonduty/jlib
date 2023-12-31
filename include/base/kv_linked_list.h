/**
 * \file kv_linked_list.h
 * \brief Type and functions for KV linked list
 * \author Josselin Dulongcourty
 * \version 2.0.1
 * \date 2023-12-31
 */

#ifndef __KV_LINKED_LIST_H__
#define __KV_LINKED_LIST_H__

#include <stdbool.h>
#include "base/kv_generic.h"

/**
 * \private
 * \brief KV linked list node
 * \typedef KV_linked_list_node
 */
typedef struct KV_linked_list_node KV_linked_list_node;

/**
 * \brief KV Linked list
 * \typedef KV_linked_list
 */
typedef KV_linked_list_node *KV_linked_list;

/**
 * \private
 * \brief KV linked list node
 * \struct KV_linked_list_node
 */
struct KV_linked_list_node
{
    KV data;
    KV_linked_list next;
};

/**
 * \brief Creates a new KV linked list
 * \return KV_linked_list
 */
KV_linked_list KV_linked_list_create(void);

/**
 * \brief Checks if a KV linked list is empty
 * \param kvls KV Linked list
 * \return bool
 */
bool KV_linked_list_is_empty(KV_linked_list kvls);

/**
 * \brief Gets the next node of a KV linked list
 * \param kvls KV Linked list
 * \return KV_linked_list
 */
KV_linked_list KV_linked_list_get_next(KV_linked_list kvls);

/**
 * \brief Sets the next node of a KV linked list
 * \param kvls KV Linked list
 * \param next Next node
 */
void KV_linked_list_set_next(KV_linked_list kvls, KV_linked_list next);

/**
 * \brief Gets the data of a KV linked list node
 * \param kvls KV Linked list
 * \return KV pair
 */
KV KV_linked_list_get_data(KV_linked_list kvls);

/**
 * \brief Sets the data of a KV linked list node
 * \param kvls KV Linked list
 * \param data KV pair
 * \param copy_fn Copy function
 */
void KV_linked_list_set_data(KV_linked_list kvls, KV data, KV_copy copy_fn);

/**
 * \brief Gets the length of a KV linked list
 * \param kvls KV Linked list
 * \return long int
 */
long int KV_linked_list_length(KV_linked_list kvls);

/**
 * \brief Adds a node to a KV linked list
 * \param kvls KV Linked list
 * \param data KV pair
 * \param copy_fn Copy function
 */
void KV_linked_list_add(KV_linked_list *kvls, KV data, KV_copy copy_fn);

/**
 * \brief Adds a node to a KV linked list in a sorted way
 * \param kvls KV Linked list
 * \param data KV pair
 * \param copy_fn Copy function
 * \param compare_fn Compare function
 */
void KV_linked_list_add_sorted(KV_linked_list *kvls, KV data, KV_copy copy_fn, KV_compare compare_fn);

/**
 * \brief Removes a node from a KV linked list
 * \param kvls KV Linked list
 * \param free_fn Free function
 */
void KV_linked_list_remove(KV_linked_list *kvls, KV_free free_fn);

/**
 * \brief Destroys a KV linked list
 * \param kvls KV Linked list
 * \param free_fn Free function
 */
void KV_linked_list_destroy(KV_linked_list *kvls, KV_free free_fn);

/**
 * \brief Prints a KV linked list
 * \param kvls KV Linked list
 * \param print_fn Print function
 */
void KV_linked_list_print(KV_linked_list kvls, KV_print print_fn);

#endif // __KV_LINKED_LIST_H__