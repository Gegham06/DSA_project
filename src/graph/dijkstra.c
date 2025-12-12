#include "c_graph_internal.h"
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>

// Helper function to get the max vertex ID
static int get_max_vertex_id(c_graph_t* graph) {
    int max_id = -1;
    c_graph_vertex_t* current = graph->vertices;
    while(current) {
        if (current->id > max_id) {
            max_id = current->id;
        }
        current = current->next;
    }
    return max_id;
}

// Helper to find the vertex with the minimum distance
static int min_distance(double* dist, bool* spt_set, int max_id) {
    double min = DBL_MAX;
    int min_index = -1;

    for (int v = 0; v <= max_id; v++) {
        if (spt_set[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

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

    for (int i = 0; i <= max_id; i++) {
        dist[i] = DBL_MAX;
        parent[i] = -1;
    }
    dist[start_id] = 0;

    for (int count = 0; count < max_id; count++) {
        int u = min_distance(dist, spt_set, max_id);
        if (u == -1 || u == end_id) break;

        spt_set[u] = true;

        c_graph_vertex_t* u_vertex = graph->vertices;
        while(u_vertex && u_vertex->id != u) {
            u_vertex = u_vertex->next;
        }

        if (u_vertex) {
            c_graph_edge_t* edge = u_vertex->edges;
            while(edge) {
                int v = edge->dest_id;
                if (!spt_set[v] && dist[u] != DBL_MAX && dist[u] + edge->weight < dist[v]) {
                    dist[v] = dist[u] + edge->weight;
                    parent[v] = u;
                }
                edge = edge->next;
            }
        }
    }

    free(dist);
    free(spt_set);

    if (parent[end_id] == -1 && start_id != end_id) {
        free(parent);
        *path_len = 0;
        return NULL;
    }

    int* path = NULL;
    int count = 0;
    int current = end_id;
    while (current != -1) {
        count++;
        current = parent[current];
    }

    path = (int*)malloc(count * sizeof(int));
    if (!path) {
        free(parent);
        *path_len = 0;
        return NULL;
    }

    *path_len = count;
    current = end_id;
    for (int i = count - 1; i >= 0; i--) {
        path[i] = current;
        current = parent[current];
    }

    free(parent);
    return path;
}
