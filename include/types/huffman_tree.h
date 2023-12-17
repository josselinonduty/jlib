#ifndef __HUFFMAN_TREE_H__
#define __HUFFMAN_TREE_H__

#include <stdbool.h>
#include "base/generic.h"
#include "base/binary_tree.h"
#include "types/statistic.h"

typedef binary_tree huffman_tree;

huffman_tree huffman_tree_create(any value);
void huffman_tree_destroy(huffman_tree *tree);
void huffman_tree_print(any tree);
stat *huffman_tree_get_data(binary_tree tree);
huffman_tree huffman_tree_get_left(binary_tree tree);
huffman_tree huffman_tree_get_right(binary_tree tree);
void huffman_tree_set_data(binary_tree tree, any value);
void huffman_tree_set_left(binary_tree tree, binary_tree left);
void huffman_tree_set_right(binary_tree tree, binary_tree right);
any huffman_tree_copy(any t);
bool huffman_tree_compare(any a, any b);
void huffman_tree_free(any tree);

#endif // __HUFFMAN_TREE_H__