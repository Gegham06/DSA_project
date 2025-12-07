cmake_minimum_required(VERSION 3.16)
project(my_project C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Create library
add_library(
    dsalib 
    src/containers/queue.c 
    src/containers/stack.c
    src/math/add.c 
    src/search/linear_search.c 
    src/search/binary_search_tree.c
    src/c_hash_map.c
    src/c_vector.c
    src/graph.c
)

target_include_directories(dsalib PUBLIC include)

add_subdirectory(playground)

# Enable testing
enable_testing()
add_subdirectory(tests)
