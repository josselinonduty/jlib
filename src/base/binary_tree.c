#include <CUnit/CUnit.h>

#include "base/generic.h"
#include "base/int.h"
#include "base/binary_tree.h"

void test_binary_tree_create(void)
{
    int a = 1;
    binary_tree tree = binary_tree_create(&a, int_copy);

    CU_ASSERT_PTR_NOT_NULL(tree);
    CU_ASSERT_PTR_NOT_NULL(tree->data);
    CU_ASSERT_TRUE(binary_tree_is_leaf(tree));
    CU_ASSERT_TRUE(int_equal(binary_tree_get_data(tree), &a));

    CU_ASSERT_PTR_NULL(tree->left);
    CU_ASSERT_PTR_NULL(tree->right);

    binary_tree_destroy(&tree, int_free);
    CU_ASSERT_PTR_NULL(tree);
}

void test_binary_tree_add(void)
{
    int a = 1;
    int b = 2;
    int c = 3;
    binary_tree left = binary_tree_create(&b, int_copy);
    binary_tree right = binary_tree_create(&c, int_copy);

    binary_tree tree = binary_tree_add_root(left, right, &a, int_copy);

    CU_ASSERT_PTR_NOT_NULL(tree);
    CU_ASSERT_PTR_NOT_NULL(binary_tree_get_data(tree));
    CU_ASSERT_FALSE(binary_tree_is_leaf(tree));
    CU_ASSERT_TRUE(int_equal(binary_tree_get_data(tree), &a));

    CU_ASSERT_PTR_NOT_NULL(binary_tree_get_left(tree));
    CU_ASSERT_PTR_NOT_NULL(binary_tree_get_right(tree));

    CU_ASSERT_TRUE(int_equal(binary_tree_get_data(binary_tree_get_left(tree)), &b));
    CU_ASSERT_TRUE(int_equal(binary_tree_get_data(binary_tree_get_right(tree)), &c));

    binary_tree_destroy(&tree, int_free);
    CU_ASSERT_PTR_NULL(tree);
}

void test_binary_tree_add_overflow(void)
{
    long int count = 1000;

    binary_tree tree = NULL;
    binary_tree left = NULL;
    binary_tree right = NULL;
    for (int i = 0; i < count; i++)
    {
        int a = 1;
        int b = 2;
        int c = 3;
        left = binary_tree_create(&b, int_copy);
        right = binary_tree_create(&c, int_copy);

        tree = binary_tree_add_root(left, right, &a, int_copy);
        binary_tree_destroy(&tree, int_free);
    }

    for (int i = 0; i < count; i++)
    {
        tree = binary_tree_create(&i, int_copy);

        for (int j = 0; j < count; j++)
        {
            left = binary_tree_create(&j, int_copy);
            right = binary_tree_create(&j, int_copy);

            binary_tree_add_root(left, right, &j, int_copy);
        }

        binary_tree_destroy(&tree, int_free);
    }

    CU_ASSERT_PTR_NULL(tree);
}

void test_binary_tree_remove(void)
{
    int a = 1;
    int b = 2;
    int c = 3;
    binary_tree left = binary_tree_create(&b, int_copy);
    binary_tree right = binary_tree_create(&c, int_copy);

    binary_tree tree = binary_tree_add_root(left, right, &a, int_copy);

    CU_ASSERT_PTR_NOT_NULL(tree);
    CU_ASSERT_PTR_NOT_NULL(binary_tree_get_data(tree));
    CU_ASSERT_FALSE(binary_tree_is_leaf(tree));
    CU_ASSERT_TRUE(int_equal(binary_tree_get_data(tree), &a));

    CU_ASSERT_PTR_NOT_NULL(binary_tree_get_left(tree));
    CU_ASSERT_PTR_NOT_NULL(binary_tree_get_right(tree));

    CU_ASSERT_TRUE(int_equal(binary_tree_get_data(binary_tree_get_left(tree)), &b));
    CU_ASSERT_TRUE(int_equal(binary_tree_get_data(binary_tree_get_right(tree)), &c));

    binary_tree_destroy(&tree, int_free);
    CU_ASSERT_PTR_NULL(tree);
}