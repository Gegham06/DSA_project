#include "../include/c_graph.h"
#include <stdio.h>
#include <stdlib.h>

#define ASSERT(condition, test_failed_ptr) \
    if (!(condition)) { \
        printf("    FAIL: %s\n", #condition); \
        *test_failed_ptr = 1; \
        return; \
    }

void test_graph_creation(int* test_failed) {
    c_graph_t* graph = graph_create(0);
    ASSERT(graph != NULL, test_failed);
    graph_destroy(graph);
}

void test_add_vertices_and_edges(int* test_failed) {
    c_graph_t* graph = graph_create(0);
    ASSERT(graph_add_vertex(graph, 1) == 0, test_failed);
    ASSERT(graph_add_vertex(graph, 2) == 0, test_failed);
    ASSERT(graph_add_edge(graph, 1, 2, 1.0) == 0, test_failed);
    graph_destroy(graph);
}

void test_duplicate_vertex(int* test_failed) {
    c_graph_t* graph = graph_create(0);
    ASSERT(graph_add_vertex(graph, 1) == 0, test_failed);
    ASSERT(graph_add_vertex(graph, 1) == -1, test_failed); // Should fail to add duplicate
    graph_destroy(graph);
}

void test_remove_operations(int* test_failed) {
    c_graph_t* graph = graph_create(0);
    graph_add_vertex(graph, 1);
    graph_add_vertex(graph, 2);
    graph_add_edge(graph, 1, 2, 1.0);
    ASSERT(graph_remove_edge(graph, 1, 2) == 0, test_failed);
    ASSERT(graph_remove_vertex(graph, 1) == 0, test_failed);
    graph_destroy(graph);
}
