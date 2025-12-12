#include "graph/c_graph.h"
#include <stdio.h>
#include <string.h>

// Test function signature
typedef void (*test_func)(int*);

// Test case registry
#define MAX_TESTS 50
static test_func test_suite[MAX_TESTS];
static const char* test_names[MAX_TESTS];
static int test_count = 0;

void register_test(test_func func, const char* name) {
    if (test_count < MAX_TESTS) {
        test_suite[test_count] = func;
        test_names[test_count] = name;
        test_count++;
    }
}

// Test assertion macros
#define ASSERT(condition, test_failed_ptr) \
    if (!(condition)) { \
        printf("    FAIL: %s\n", #condition); \
        *test_failed_ptr = 1; \
        return; \
    }

// Function declarations for tests to be added
void test_graph_creation(int* test_failed);
void test_add_vertices_and_edges(int* test_failed);
void test_bfs_pathfinding(int* test_failed);
void test_dfs_traversal(int* test_failed);
void test_dijkstra_shortest_path(int* test_failed);
void test_remove_operations(int* test_failed);
void test_duplicate_vertex(int* test_failed);

int main() {
    register_test(test_graph_creation, "Graph Creation");
    register_test(test_add_vertices_and_edges, "Add Vertices and Edges");
    register_test(test_bfs_pathfinding, "BFS Pathfinding");
    register_test(test_dfs_traversal, "DFS Traversal");
    register_test(test_dijkstra_shortest_path, "Dijkstra Shortest Path");
    register_test(test_remove_operations, "Remove Operations");
    register_test(test_duplicate_vertex, "Duplicate Vertex");

    int passed = 0;
    for (int i = 0; i < test_count; i++) {
        int test_failed = 0;
        printf("Running test: %s\n", test_names[i]);
        test_suite[i](&test_failed);
        if (!test_failed) {
            printf("    PASS\n");
            passed++;
        }
    }

    printf("\n%d/%d tests passed.\n", passed, test_count);
    return (passed == test_count) ? 0 : 1;
}
