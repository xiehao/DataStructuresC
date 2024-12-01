cmake_minimum_required(VERSION 3.27)
project(dsa-c 
    VERSION 0.1.0 
    LANGUAGES C
    DESCRIPTION "Data Structures and Algorithms in C"
)

# 添加 cmake 模块路径
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# 设置编译选项
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# 添加编译选项
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 设置构建类型
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# 启用测试
enable_testing()

# 查找 Criterion
find_package(Criterion REQUIRED)

# 添加子目录
add_subdirectory(src)
add_subdirectory(tests)
