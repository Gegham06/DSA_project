#include "c_graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ASSERT(condition, test_failed_ptr) \
    if (!(condition)) { \
        printf("    FAIL: %s\n", #condition); \
        *test_failed_ptr = 1; \
        return; \
    }

void test_bfs_pathfinding(int* test_failed) {
    c_graph_t* graph = graph_create(0);
    graph_add_vertex(graph, 0);
    graph_add_vertex(graph, 1);
    graph_add_vertex(graph, 2);
    graph_add_vertex(graph, 3);
    graph_add_edge(graph, 0, 1, 1);
    graph_add_edge(graph, 0, 2, 1);
    graph_add_edge(graph, 1, 3, 1);
    graph_add_edge(graph, 2, 3, 1);

    int path_len = 0;
    int* path = graph_bfs(graph, 0, 3, &path_len);
    ASSERT(path_len == 3, test_failed);

    bool path1 = (path[0] == 0 && path[1] == 1 && path[2] == 3);
    bool path2 = (path[0] == 0 && path[1] == 2 && path[2] == 3);
    ASSERT(path1 || path2, test_failed);

    free(path);
    graph_destroy(graph);
}

void test_dfs_traversal(int* test_failed) {
    c_graph_t* graph = graph_create(1); // Directed
    graph_add_vertex(graph, 0);
    graph_add_vertex(graph, 1);
    graph_add_vertex(graph, 2);
    graph_add_edge(graph, 0, 1, 1);
    graph_add_edge(graph, 0, 2, 1);

    int path_len = 0;
    int* path = graph_dfs(graph, 0, &path_len);
    ASSERT(path_len == 3, test_failed);
    // With the current implementation, this should be the traversal order.
    // A more robust test might need to account for different valid DFS orders.
    ASSERT(path[0] == 0 && path[1] == 2 && path[2] == 1, test_failed);
    free(path);
    graph_destroy(graph);
}

void test_dijkstra_shortest_path(int* test_failed) {
    c_graph_t* graph = graph_create(0);
    graph_add_vertex(graph, 0);
    graph_add_vertex(graph, 1);
    graph_add_vertex(graph, 2);
    graph_add_vertex(graph, 3);
    graph_add_edge(graph, 0, 1, 1);
    graph_add_edge(graph, 0, 2, 4);
    graph_add_edge(graph, 1, 2, 2);
    graph_add_edge(graph, 1, 3, 5);
    graph_add_edge(graph, 2, 3, 1);

    int path_len = 0;
    int* path = graph_dijkstra(graph, 0, 3, &path_len);
    ASSERT(path_len == 4, test_failed);
    ASSERT(path[0] == 0 && path[1] == 1 && path[2] == 2 && path[3] == 3, test_failed);
    free(path);
    graph_destroy(graph);
}
