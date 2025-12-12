cmake_minimum_required(VERSION 3.16)
project(my_project C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# -----------------------------
# Include directories
# -----------------------------
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

# -----------------------------
# Create the library: dsalib
# -----------------------------
add_library(
    dsalib 
    # Containers
    src/containers/queue.c 
    src/containers/stack.c

    # Math
    src/math/add.c

    # Search
    src/search/linear_search.c 
    src/search/binary_search_tree.c

    # Core structures
    src/c_hash_map.c
    src/c_vector.c
    src/graph.c

    # Graph algorithms (previously missing)
    src/bfs.c
    src/dfs.c
    src/dijkstra.c
)

target_include_directories(dsalib PUBLIC include)

# -----------------------------
# Playground / examples
# -----------------------------
add_subdirectory(playground)

# -----------------------------
# Tests
# -----------------------------
enable_testing()
add_subdirectory(tests)

