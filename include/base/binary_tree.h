#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <stdbool.h>
#include "base/generic.h"

/**
 * @private
 * @brief Binary tree node
 * @typedef binary_tree_node
 */
typedef struct binary_tree_node binary_tree_node;

/**
 * @brief Binary tree
 * @typedef binary_tree
 */
typedef binary_tree_node *binary_tree;

/**
 * @brief Create a new binary tree
 * @return binary_tree
 */
struct binary_tree_node
{
    any data;
    binary_tree left;
    binary_tree right;
};

/**
 * @brief Binary tree print strategy
 * @typedef binary_tree_print_strategy
 */
typedef enum binary_tree_print_strategy {
    ROOT_LEFT_RIGHT,
    LEFT_ROOT_RIGHT,
    LEFT_RIGHT_ROOT
} binary_tree_print_strategy;

binary_tree binary_tree_create(any data, generic_copy copy_fn);
bool binary_tree_is_leaf(binary_tree tree);
any binary_tree_get_data(binary_tree tree);
void binary_tree_set_data(binary_tree tree, any data, generic_copy copy_fn);
binary_tree binary_tree_get_left(binary_tree tree);
void binary_tree_set_left(binary_tree tree, binary_tree left);
binary_tree binary_tree_get_right(binary_tree tree);
void binary_tree_set_right(binary_tree tree, binary_tree right);
binary_tree binary_tree_add_root(binary_tree left, binary_tree right, any data, generic_copy copy_fn);
void binary_tree_destroy(binary_tree *tree, generic_free free_fn);
void binary_tree_print(binary_tree tree, binary_tree_print_strategy strategy, generic_print print_fn);

#endif // __BINARY_TREE_H__