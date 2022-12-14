#include <stdio.h>

#include "sequence_list.h"
#include "linked_list.h"
#include "vector.h"
#include "sequence_stack.h"
#include "linked_stack.h"
#include "stack.h"
#include "hanoi.h"
#include "maze.h"
#include "sequence_queue.h"
#include "linked_queue.h"
#include "tree.h"
#include "binary_tree.h"
#include "huffman.h"
#include "graph.h"
#include "sorting.h"
#include "heap.h"
#include "searching.h"

int main(int argc, char **argv) {
    printf("=============sequence list================\n");
    demo_sequence_list();
    printf("==============linked list=================\n");
    demo_linked_list();
    printf("=================vector===================\n");
    demo_vector();
    printf("=============sequence stack===============\n");
    demo_sequence_stack();
    printf("==============linked stack================\n");
    demo_linked_stack();
    printf("==================stack====================\n");
    demo_stack();
    printf("-------------------hanoi------------------\n");
    solve_hanoi();
    printf("-------------------maze-------------------\n");
    solve_maze();
    printf("=============sequence queue===============\n");
    demo_sequence_queue();
    printf("==============linked queue================\n");
    demo_linked_queue();
    printf("==================tree====================\n");
    demo_tree();
    printf("===============binary tree================\n");
    demo_binary_tree();
    printf("==================huffman==================\n");
    demo_huffman();
    printf("==================graph==================\n");
    demo_graph();
    printf("==================heap==================\n");
    demo_heap();
    printf("==================sorting==================\n");
    demo_sorting();
    printf("==================searching==================\n");
    demo_searching();
}
