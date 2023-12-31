/**
 * \file binary_tree.h
 * \brief Type and functions for binary trees
 * \author Josselin Dulongcourty
 * \version 1.0.1
 * \date 2023-12-31
 */

#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <stdbool.h>
#include "base/generic.h"

/**
 * \private
 * \brief Binary tree node
 * \typedef binary_tree_node
 */
typedef struct binary_tree_node binary_tree_node;

/**
 * \brief Binary tree
 * \typedef binary_tree
 */
typedef binary_tree_node *binary_tree;

/**
 * \private
 * \brief Binary tree node
 * \struct binary_tree_node
 */
struct binary_tree_node
{
    any data;
    binary_tree left;
    binary_tree right;
};

/**
 * \brief Binary tree print strategy
 * \typedef binary_tree_print_strategy
 */
typedef enum binary_tree_print_strategy
{
    /**
     * \brief Print the root, then the left child, then the right child
     */
    BINARY_TREE_PRINT_STRATEGY_ROOT_LEFT_RIGHT,
    /**
     * \brief Print the left child, then the root, then the right child
     */
    BINARY_TREE_PRINT_STRATEGY_LEFT_ROOT_RIGHT,
    /**
     * \brief Print the left child, then the right child, then the root
     */
    BINARY_TREE_PRINT_STRATEGY_LEFT_RIGHT_ROOT
} binary_tree_print_strategy;

/**
 * \brief Creates a new binary tree
 * \param data Data of the root
 * \param copy_fn Function to copy the data
 * \return binary_tree
 */
binary_tree binary_tree_create(any data, generic_copy copy_fn);

/**
 * \brief Checks if a binary tree is empty
 * \param tree Binary tree
 * \return bool
 */
bool binary_tree_is_leaf(binary_tree tree);

/**
 * \brief Gets the data of a binary tree
 * \param tree Binary tree
 * \return any
 */
any binary_tree_get_data(binary_tree tree);

/**
 * \brief Sets the data of a binary tree
 * \param tree Binary tree
 * \param data Data
 * \param copy_fn Function to copy the data
 */
void binary_tree_set_data(binary_tree tree, any data, generic_copy copy_fn);

/**
 * \brief Gets the left child of a binary tree
 * \param tree Binary tree
 * \return binary_tree
 */
binary_tree binary_tree_get_left(binary_tree tree);

/**
 * \brief Sets the left child of a binary tree
 * \param tree Binary tree
 * \param left Left child
 */
void binary_tree_set_left(binary_tree tree, binary_tree left);

/**
 * \brief Gets the right child of a binary tree
 * \param tree Binary tree
 * \return binary_tree
 */
binary_tree binary_tree_get_right(binary_tree tree);

/**
 * \brief Sets the right child of a binary tree
 * \param tree Binary tree
 * \param right Right child
 */
void binary_tree_set_right(binary_tree tree, binary_tree right);

/**
 * \brief Adds a root to a binary tree
 * \param left Left child
 * \param right Right child
 * \param data Data
 * \param copy_fn Function to copy the data
 * \return binary_tree
 */
binary_tree binary_tree_add_root(binary_tree left, binary_tree right, any data, generic_copy copy_fn);

/**
 * \brief Destroys a binary tree
 * \param tree Binary tree
 * \param free_fn Function to free the data
 */
void binary_tree_destroy(binary_tree *tree, generic_free free_fn);

/**
 * \brief Prints a binary tree
 * \param tree Binary tree
 * \param strategy Print strategy
 * \param print_fn Function to print the data
 */
void binary_tree_print(binary_tree tree, binary_tree_print_strategy strategy, generic_print print_fn);

#endif // __BINARY_TREE_H__