# 创建库目标
add_library(dsa
    lib/common.c
    lib/linked_list.c
    lib/sequence_list.c
    lib/vector.c
    lib/sequence_stack.c
    lib/linked_stack.c
    lib/stack.c
    lib/heap.c
    lib/hanoi.c
    lib/maze.c
    lib/sequence_queue.c
    lib/linked_queue.c
    lib/tree.c
    lib/binary_tree.c
    # binary_search_tree.c
    lib/huffman.c
    lib/graph.c
    lib/sorting.c
    lib/searching.c
)

# 设置包含目录
target_include_directories(dsa
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

# 创建可执行文件
add_executable(dsa-demo main.c)
target_link_libraries(dsa-demo PRIVATE dsa) 
