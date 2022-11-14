#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdbool.h>

#include "common.h"

typedef struct _node {
    DataType data;
    struct _node *left;
    struct _node *right;
    struct _node *parent;
} BinaryTreeNode;

typedef struct _tree BinaryTree;

extern BinaryTreeNode *create_binary_tree_node(DataType d);

extern BinaryTree *create_binary_tree();

extern void destroy_binary_tree(BinaryTree *t);

extern BinaryTreeNode *binary_root(BinaryTree *t);

extern BinaryTreeNode *left_child(BinaryTreeNode *p);

extern BinaryTreeNode *right_child(BinaryTreeNode *p);

extern BinaryTreeNode *binary_parent(BinaryTreeNode *n);

extern BinaryTreeNode *set_left_child(BinaryTreeNode *r, BinaryTreeNode *n);

extern BinaryTreeNode *set_right_child(BinaryTreeNode *r, BinaryTreeNode *n);

extern DataType binary_node_data(BinaryTreeNode *n);

extern bool insert_left_binary_tree(BinaryTreeNode *p, DataType d);

extern bool insert_right_binary_tree(BinaryTreeNode *p, DataType d);

extern BinaryTreeNode *successor_binary_tree_preorder(BinaryTreeNode *n);

extern BinaryTreeNode *successor_binary_tree_inorder(BinaryTreeNode *n);

extern BinaryTreeNode *successor_binary_tree_postorder(BinaryTreeNode *n);

extern void traverse_binary_tree_preorder_recursively(BinaryTreeNode *p,
                                                      VisitType v);

extern void traverse_binary_tree_inorder_recursively(BinaryTreeNode *p,
                                                     VisitType v);

extern void traverse_binary_tree_postorder_recursively(BinaryTreeNode *p,
                                                       VisitType v);

extern void traverse_binary_tree_level_order_recursively(BinaryTreeNode *p,
                                                         VisitType v);

extern void traverse_binary_tree_preorder(BinaryTreeNode *p, VisitType v);

extern void traverse_binary_tree_inorder(BinaryTreeNode *p, VisitType v);
extern void traverse_binary_tree_inorder_no_stack(BinaryTreeNode *p,
                                                  VisitType v);

extern void traverse_binary_tree_postorder(BinaryTreeNode *p, VisitType v);
extern void traverse_binary_tree_postorder_no_stack(BinaryTreeNode *p,
                                                    VisitType v);

extern void traverse_binary_tree_level_order(BinaryTreeNode *p, VisitType v);

extern void demo_binary_tree();

#endif // BINARY_TREE_H