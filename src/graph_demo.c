#include "c_graph.h"
#include "c_graph_internal.h"
#include <stdio.h>
#include <stdlib.h>

void print_graph(c_graph_t* graph) {
    printf("Graph structure:\n");
    c_graph_vertex_t* vertex = graph->vertices;
    while (vertex) {
        printf("Vertex %d: ", vertex->id);
        c_graph_edge_t* edge = vertex->edges;
        while (edge) {
            printf("-> %d(w=%.1f) ", edge->dest_id, edge->weight);
            edge = edge->next;
        }
        printf("\n");
        vertex = vertex->next;
    }
}

void print_path(int* path, int path_len) {
    if (!path || path_len <= 0) {
        printf("No path found.\n");
        return;
    }
    for (int i = 0; i < path_len; i++) {
        printf("%d", path[i]);
        if (i < path_len - 1) printf(" -> ");
    }
    printf("\n");
}

int main() {
    c_graph_t* graph = graph_create(1); // directed

    // Add vertices
    for (int i = 0; i < 5; i++) graph_add_vertex(graph, i);

    // Add edges
    graph_add_edge(graph, 0, 1, 2.0);
    graph_add_edge(graph, 0, 2, 4.0);
    graph_add_edge(graph, 1, 2, 1.0);
    graph_add_edge(graph, 1, 3, 7.0);
    graph_add_edge(graph, 2, 4, 3.0);
    graph_add_edge(graph, 3, 4, 1.0);

    print_graph(graph);

    int dfs_len = 0;
    int* dfs_path = graph_dfs(graph, 0, &dfs_len);
    printf("\nDFS from 0:\n");
    print_path(dfs_path, dfs_len);
    free(dfs_path);

    int bfs_len = 0;
    int* bfs_path = graph_bfs(graph, 0, 4, &bfs_len);
    printf("\nBFS from 0 to 4:\n");
    print_path(bfs_path, bfs_len);
    free(bfs_path);

    int dijkstra_len = 0;
    int* dijkstra_path = graph_dijkstra(graph, 0, 4, &dijkstra_len);
    printf("\nDijkstra shortest path from 0 to 4:\n");
    print_path(dijkstra_path, dijkstra_len);
    free(dijkstra_path);

    graph_destroy(graph);

    return 0;
}
