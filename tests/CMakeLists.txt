enable_testing()

# 添加链表测试
add_executable(test_linked_list
    unit/test_linked_list.c
)

target_link_libraries(test_linked_list
    PRIVATE
    dsa
    Criterion::Criterion
)

add_test(NAME test_linked_list COMMAND test_linked_list) 