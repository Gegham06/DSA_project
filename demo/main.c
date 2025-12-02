#include "../include/c_graph.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Create a graph representing a city map
    c_graph_t* city_map = graph_create(0); // Undirected graph

    // Add intersections (vertices)
    for (int i = 0; i < 6; i++) {
        graph_add_vertex(city_map, i);
    }

    // Add roads (edges) with travel times (weights)
    graph_add_edge(city_map, 0, 1, 7);
    graph_add_edge(city_map, 0, 2, 9);
    graph_add_edge(city_map, 0, 5, 14);
    graph_add_edge(city_map, 1, 2, 10);
    graph_add_edge(city_map, 1, 3, 15);
    graph_add_edge(city_map, 2, 3, 11);
    graph_add_edge(city_map, 2, 5, 2);
    graph_add_edge(city_map, 3, 4, 6);
    graph_add_edge(city_map, 4, 5, 9);

    // Find the fastest route from intersection 0 to 4
    int start_node = 0;
    int end_node = 4;
    int path_len = 0;
    int* path = graph_dijkstra(city_map, start_node, end_node, &path_len);

    if (path) {
        printf("Fastest route from %d to %d:\n", start_node, end_node);
        for (int i = 0; i < path_len; i++) {
            printf("%d %s", path[i], (i == path_len - 1) ? "" : "-> ");
        }
        printf("\n");
        free(path);
    } else {
        printf("No path found from %d to %d.\n", start_node, end_node);
    }

    // Clean up
    graph_destroy(city_map);

    return 0;
}
