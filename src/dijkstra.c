#include "include/c_graph_internal.h"
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>

/*
 * Function: get_max_vertex_id
 * ---------------------------
 * Helper function that finds the maximum vertex ID in the graph.
 *
 * graph: pointer to the graph structure
 *
 * returns: the largest vertex ID, or -1 if no vertices exist
 */
static int get_max_vertex_id(c_graph_t* graph) {
    int max_id = -1;
    c_graph_vertex_t* current = graph->vertices;
    while(current) {
        if (current->id > max_id) {
            max_id = current->id; // Update max_id if current vertex ID is larger
        }
        current = current->next;
    }
    return max_id;
}

/*
 * Function: min_distance
 * ----------------------
 * Helper function that finds the vertex with the minimum distance value
 * from the set of vertices not yet included in the shortest path tree.
 *
 * dist: array of distances from the start vertex
 * spt_set: boolean array indicating if vertex is included in shortest path
 * max_id: maximum vertex ID in the graph
 *
 * returns: index of the vertex with the minimum distance, -1 if none found
 */
static int min_distance(double* dist, bool* spt_set, int max_id) {
    double min = DBL_MAX;
    int min_index = -1;

    for (int v = 0; v <= max_id; v++) {
        if (spt_set[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v; // Store index of vertex with smallest tentative distance
        }
    }
    return min_index;
}

/*
 * Function: graph_dijkstra
 * ------------------------
 * Implements Dijkstra's algorithm to find the shortest path between
 * start_id and end_id in the graph.
 *
 * graph: pointer to the graph structure
 * start_id: ID of the starting vertex
 * end_id: ID of the destination vertex
 * path_len: pointer to an integer to store the length of the path
 *
 * returns: array of vertex IDs representing the shortest path
 *          or NULL if no path exists or input is invalid
 */
int* graph_dijkstra(c_graph_t* graph, int start_id, int end_id, int* path_len) {
    if (!graph || !path_len) {
        if (path_len) *path_len = 0;
        return NULL;
    }

    int max_id = get_max_vertex_id(graph);
    if (max_id < 0) {
        *path_len = 0;
        return NULL;
    }

    // Allocate memory for distances, visited set, and parent tracking
    double* dist = (double*)malloc((max_id + 1) * sizeof(double));
    bool* spt_set = (bool*)calloc(max_id + 1, sizeof(bool));
    int* parent = (int*)malloc((max_id + 1) * sizeof(int));

    if (!dist || !spt_set || !parent) {
        free(dist);
        free(spt_set);
        free(parent);
        *path_len = 0;
        return NULL;
    }

    // Initialize distances to maximum and parents to -1
    for (int i = 0; i <= max_id; i++) {
        dist[i] = DBL_MAX;
        parent[i] = -1;
    }
    dist[start_id] = 0; // Distance from start vertex to itself is zero

    // Main loop of Dijkstra's algorithm
    for (int count = 0; count < max_id; count++) {
        int u = min_distance(dist, spt_set, max_id); // Pick vertex with minimum distance
        if (u == -1 || u == end_id) break; // Stop if no reachable vertex or reached end

        spt_set[u] = true; // Mark vertex as processed

        // Find the corresponding vertex in the graph
        c_graph_vertex_t* u_vertex = graph->vertices;
        while(u_vertex && u_vertex->id != u) {
            u_vertex = u_vertex->next;
        }

        // Update distances for adjacent vertices
        if (u_vertex) {
            c_graph_edge_t* edge = u_vertex->edges;
            while(edge) {
                int v = edge->dest_id;
                if (!spt_set[v] && dist[u] != DBL_MAX && dist[u] + edge->weight < dist[v]) {
                    dist[v] = dist[u] + edge->weight;
                    parent[v] = u; // Store predecessor for path reconstruction
                }
                edge = edge->next;
            }
        }
    }

    free(dist);
    free(spt_set);

    // Check if end vertex is reachable
    if (parent[end_id] == -1 && start_id != end_id) {
        free(parent);
        *path_len = 0;
        return NULL;
    }

    // Determine length of the path
    int* path = NULL;
    int count = 0;
    int current = end_id;
    while (current != -1) {
        count++;
        current = parent[current];
    }

    // Allocate array to store path vertices
    path = (int*)malloc(count * sizeof(int));
    if (!path) {
        free(parent);
        *path_len = 0;
        return NULL;
    }

    *path_len = count;

    // Fill path array from end to start
    current = end_id;
    for (int i = count - 1; i >= 0; i--) {
        path[i] = current;
        current = parent[current];
    }

    free(parent);
    return path;
}

