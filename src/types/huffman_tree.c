#include <stdbool.h>
#include "base/generic.h"
#include "base/binary_tree.h"
#include "types/statistic.h"
#include "types/huffman_tree.h"

huffman_tree huffman_tree_create(any value)
{
    return binary_tree_create(value, stat_copy);
}

void huffman_tree_destroy(huffman_tree *tree)
{
    binary_tree_destroy(tree, stat_free);
}

void huffman_tree_print(any tree)
{
    binary_tree_print(*(huffman_tree *)tree, ROOT_LEFT_RIGHT, stat_print);
}

stat *huffman_tree_get_data(binary_tree tree)
{
    return (stat *)binary_tree_get_data(tree);
}

huffman_tree huffman_tree_get_left(binary_tree tree)
{
    return binary_tree_get_left(tree);
}

huffman_tree huffman_tree_get_right(binary_tree tree)
{
    return binary_tree_get_right(tree);
}

void huffman_tree_set_data(binary_tree tree, any value)
{
    binary_tree_set_data(tree, value, stat_copy);
}

void huffman_tree_set_left(binary_tree tree, binary_tree left)
{
    binary_tree_set_left(tree, left);
}

void huffman_tree_set_right(binary_tree tree, binary_tree right)
{
    binary_tree_set_right(tree, right);
}

any huffman_tree_copy(any t)
{
    huffman_tree *tree = t;

    stat *root = huffman_tree_get_data(*tree);

    huffman_tree *copy = malloc(sizeof(binary_tree));
    *copy = huffman_tree_create(root);
    huffman_tree_set_left(*copy, huffman_tree_get_left(*tree));
    huffman_tree_set_right(*copy, huffman_tree_get_right(*tree));

    return copy;
}

bool huffman_tree_compare(any a, any b)
{
    huffman_tree *tree_a = a;
    huffman_tree *tree_b = b;

    stat *s_a = huffman_tree_get_data(*tree_a);
    stat *s_b = huffman_tree_get_data(*tree_b);
    if (binary_tree_is_leaf(*tree_a) && binary_tree_is_leaf(*tree_b))
    {
        if (s_a->count == s_b->count)
        {
            return s_a->byte < s_b->byte;
        }

        return s_a->count < s_b->count;
    }
    return s_a->count <= s_b->count;
}

void huffman_tree_free(any tree)
{
    huffman_tree_destroy((huffman_tree *)tree);
}