#include "c_graph_internal.h"
#include "c_graph.h"
#include <stdlib.h>
#include <stdbool.h>

/*
 * Function: get_max_vertex_id
 * ---------------------------
 * Helper function that finds the maximum vertex ID in the graph.
 *
 * graph: pointer to the graph structure
 *
 * returns: the largest vertex ID, or -1 if the graph has no vertices
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
 * Function: dfs_util
 * ------------------
 * Recursive helper function for Depth-First Search (DFS).
 * Visits a vertex, marks it as visited, and explores all unvisited adjacent vertices.
 *
 * graph: pointer to the graph structure
 * u: current vertex ID
 * visited: boolean array tracking visited vertices
 * path: array to store the traversal order
 * path_index: pointer to current index in the path array
 *
 * returns: void
 */
static void dfs_util(c_graph_t* graph, int u, bool* visited, int* path, int* path_index) {
    visited[u] = true;                  // Mark current vertex as visited
    path[(*path_index)++] = u;          // Record vertex in path

    // Locate the vertex structure corresponding to u
    c_graph_vertex_t* u_vertex = graph->vertices;
    while(u_vertex && u_vertex->id != u) {
        u_vertex = u_vertex->next;
    }

    // Recursively visit all adjacent vertices that are not yet visited
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

/*
 * Function: graph_dfs
 * -------------------
 * Performs a Depth-First Search (DFS) starting from a specified vertex.
 * Returns the order of traversal as an array of vertex IDs.
 *
 * graph: pointer to the graph structure
 * start_id: ID of the starting vertex
 * path_len: pointer to store the length of the resulting path
 *
 * returns: array of vertex IDs in DFS traversal order, or NULL if an error occurs
 */
int* graph_dfs(c_graph_t* graph, int start_id, int* path_len) {
    if (!graph || !path_len) {
        if (path_len) *path_len = 0;
        return NULL; // Invalid input
    }

    int max_id = get_max_vertex_id(graph);
    if (max_id < 0) {
        *path_len = 0;
        return NULL; // Graph is empty
    }

    // Allocate memory for visited flags and traversal path
    bool* visited = (bool*)calloc(max_id + 1, sizeof(bool));
    int* path = (int*)malloc((max_id + 1) * sizeof(int));
    if (!visited || !path) {
        free(visited);
        free(path);
        *path_len = 0;
        return NULL; // Memory allocation failed
    }

    int path_index = 0; // Initialize path index
    dfs_util(graph, start_id, visited, path, &path_index); // Perform DFS

    *path_len = path_index;

    // Resize path array to match actual traversal length
    int* result_path = (int*)realloc(path, path_index * sizeof(int));
    if (!result_path && path_index > 0) {
        free(path); // realloc failed, free original memory
        *path_len = 0;
        return NULL;
    }

    free(visited); // Free temporary visited array
    return result_path;
}

