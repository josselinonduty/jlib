#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "base/generic.h"
#include "types/binary_tree.h"

binary_tree binary_tree_create(any data, generic_copy copy_fn)
{
    binary_tree tree = (binary_tree)malloc(sizeof(binary_tree_node));
    if (NULL == tree)
    {
        errno = ENOMEM;
        return NULL;
    }

    binary_tree_set_data(tree, data, copy_fn);
    binary_tree_set_left(tree, NULL);
    binary_tree_set_right(tree, NULL);
    return tree;
}

bool binary_tree_is_leaf(binary_tree tree)
{
    return (NULL == tree->left && NULL == tree->right);
}

any binary_tree_get_data(binary_tree tree)
{
    return tree->data;
}

void binary_tree_set_data(binary_tree tree, any data, generic_copy copy_fn)
{
    tree->data = copy_fn(data);
}

binary_tree binary_tree_get_left(binary_tree tree)
{
    if (binary_tree_is_leaf(tree))
    {
        errno = ENOMEM;
        return NULL;
    }

    return tree->left;
}

void binary_tree_set_left(binary_tree tree, binary_tree left)
{
    tree->left = left;
}

binary_tree binary_tree_get_right(binary_tree tree)
{
    if (binary_tree_is_leaf(tree))
    {
        errno = ENOMEM;
        return NULL;
    }

    return tree->right;
}

void binary_tree_set_right(binary_tree tree, binary_tree right)
{
    tree->right = right;
}

binary_tree binary_tree_add_root(binary_tree left, binary_tree right, any data, generic_copy copy_fn)
{
    binary_tree tree = binary_tree_create(data, copy_fn);
    if (NULL == tree)
    {
        errno = ENOMEM;
        return NULL;
    }

    binary_tree_set_left(tree, left);
    binary_tree_set_right(tree, right);
    return tree;
}

void binary_tree_destroy(binary_tree *tree, generic_free free_fn)
{
    if (NULL == *tree)
    {
        return;
    }

    free_fn(binary_tree_get_data(*tree));
    binary_tree_destroy(&(*tree)->left, free_fn);
    binary_tree_destroy(&(*tree)->right, free_fn);
    free(*tree);
    *tree = NULL;
}

void binary_tree_print(binary_tree tree, binary_tree_print_strategy strategy, generic_print print_fn)
{
    if (NULL == tree)
    {
        return;
    }

    switch (strategy)
    {
    case ROOT_LEFT_RIGHT:
        print_fn(binary_tree_get_data(tree));
        binary_tree_print(binary_tree_get_left(tree), strategy, print_fn);
        binary_tree_print(binary_tree_get_right(tree), strategy, print_fn);
        break;
    case LEFT_ROOT_RIGHT:
        binary_tree_print(binary_tree_get_left(tree), strategy, print_fn);
        print_fn(binary_tree_get_data(tree));
        binary_tree_print(binary_tree_get_right(tree), strategy, print_fn);
        break;
    case LEFT_RIGHT_ROOT:
        binary_tree_print(binary_tree_get_left(tree), strategy, print_fn);
        binary_tree_print(binary_tree_get_right(tree), strategy, print_fn);
        print_fn(binary_tree_get_data(tree));
        break;
    default:
        break;
    }
}