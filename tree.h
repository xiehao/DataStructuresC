#ifndef TREE_H
#define TREE_H

#include "common.h"

typedef struct _node TreeNode;

typedef struct _tree Tree;

extern Tree *create_tree();

extern void destroy_tree();

extern TreeNode *attach_tree_node(TreeNode *p, TreeNode *n);

extern TreeNode *insert_tree_node(TreeNode *p, DataType d);

extern void demo_tree();

#endif // TREE_H