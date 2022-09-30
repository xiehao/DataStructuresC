cmake_minimum_required(VERSION 3.0.0)
project(dsa-c VERSION 0.1.0 LANGUAGES C)

add_executable(dsa-c main.c linked_list.c sequence_list.c vector.c sequence_stack.c linked_stack.c)

set_target_properties(dsa-c PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED ON
)
