#ifndef HUFFMAN_H
#define HUFFMAN_H

#ifdef LINKED_STORAGE_IMPLEMENTATION

#include "binary_tree.h"

extern BinaryTreeNode *create_huffman_tree(int w[], int n);

#else

#include "common.h"

typedef struct _node HuffmanNode;

extern HuffmanNode *create_huffman_tree(int w[], int n);

#endif

extern void demo_huffman();

#endif // HUFFMAN_H