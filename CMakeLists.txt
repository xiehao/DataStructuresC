cmake_minimum_required(VERSION 3.27)
project(dsa-c VERSION 0.1.0 LANGUAGES C)

add_executable(dsa-c main.c
    common.c
    linked_list.c
    sequence_list.c
    vector.c
    sequence_stack.c
    linked_stack.c
    stack.c
    heap.c
    hanoi.c
    maze.c
    sequence_queue.c
    linked_queue.c
    tree.c
    binary_tree.c
    # binary_search_tree.c
    huffman.c
    graph.c
    sorting.c
    searching.c
)

set_target_properties(dsa-c PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
)
