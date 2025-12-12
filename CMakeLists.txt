cmake_minimum_required(VERSION 3.16)
project(my_project C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Create library
add_library(
    dsalib
    src/graph/graph.c
    src/graph/bfs.c
    src/graph/dfs.c
    src/graph/dijkstra.c
    src/vector/c_vector.c
    src/hash_map/c_hash_map.c
    src/bst/binary_search_tree.c
)

target_include_directories(dsalib PUBLIC include)

# Enable testing
enable_testing()
add_subdirectory(test)

# Add a custom target to run tests
add_custom_target(
    test_runner
    COMMAND ctest --output-on-failure
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
