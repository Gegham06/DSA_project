#include "c_graph_internal.h"
#include <stdlib.h>
#include <stdbool.h>

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

// Recursive DFS utility
static void dfs_util(c_graph_t* graph, int u, bool* visited, int* path, int* path_index) {
    visited[u] = true;
    path[(*path_index)++] = u;

    c_graph_vertex_t* u_vertex = graph->vertices;
    while(u_vertex && u_vertex->id != u) {
        u_vertex = u_vertex->next;
    }

    if (u_vertex) {
        c_graph_edge_t* edge = u_vertex->edges;
        while (edge) {
            int v = edge->dest_id;
            if (!visited[v]) {
                dfs_util(graph, v, visited, path, path_index);
            }
            edge = edge->next;
        }
    }
}

int* graph_dfs(c_graph_t* graph, int start_id, int* path_len) {
    if (!graph || !path_len) {
        if (path_len) *path_len = 0;
        return NULL;
    }

    int max_id = get_max_vertex_id(graph);
     if (max_id < 0) {
         *path_len = 0;
         return NULL;
    }

    bool* visited = (bool*)calloc(max_id + 1, sizeof(bool));
    int* path = (int*)malloc((max_id + 1) * sizeof(int));
    if (!visited || !path) {
        free(visited);
        free(path);
        *path_len = 0;
        return NULL;
    }

    int path_index = 0;
    dfs_util(graph, start_id, visited, path, &path_index);

    *path_len = path_index;

    // Shrink the path array to the actual size
    int* result_path = (int*)realloc(path, path_index * sizeof(int));
    if (!result_path && path_index > 0) {
        free(path); // realloc failed, free original
        *path_len = 0;
        return NULL;
    }

    free(visited);
    return result_path;
}
