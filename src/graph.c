#include "c_graph_internal.h"
#include "c_graph.h"
#include <stdlib.h>

/*
 * Function: graph_create
 * ----------------------
 * Allocates and initializes a new graph structure.
 *
 * directed: 1 for directed graph, 0 for undirected graph
 *
 * returns: pointer to the created graph, or NULL if allocation fails
 */
c_graph_t* graph_create(int directed) {
    c_graph_t* graph = (c_graph_t*)malloc(sizeof(c_graph_t));
    if (graph) {
        graph->directed = directed;
        graph->vertices = NULL;  // Initialize vertex list as empty
    }
    return graph;
}

/*
 * Function: graph_add_vertex
 * --------------------------
 * Adds a new vertex with the specified ID to the graph.
 *
 * graph: pointer to the graph structure
 * id: unique identifier for the new vertex
 *
 * returns: 0 if successful, -1 if vertex already exists or graph is NULL
 */
int graph_add_vertex(c_graph_t* graph, int id) {
    if (!graph) return -1;

    // Check for existing vertex with same ID
    c_graph_vertex_t* current = graph->vertices;
    while(current) {
        if (current->id == id) {
            return -1; // Vertex already exists
        }
        current = current->next;
    }

    // Allocate memory for new vertex
    c_graph_vertex_t* new_vertex = (c_graph_vertex_t*)malloc(sizeof(c_graph_vertex_t));
    if (!new_vertex) return -1;

    new_vertex->id = id;
    new_vertex->edges = NULL;  // Initialize edge list as empty
    new_vertex->next = graph->vertices;  // Insert at the beginning
    graph->vertices = new_vertex;

    return 0;
}

/*
 * Function: graph_remove_vertex
 * -----------------------------
 * Removes the vertex with the specified ID and all associated edges.
 *
 * graph: pointer to the graph structure
 * id: ID of the vertex to remove
 *
 * returns: 0 if successful, -1 if vertex not found or graph is NULL
 */
int graph_remove_vertex(c_graph_t* graph, int id) {
    if (!graph) return -1;

    c_graph_vertex_t* prev_vertex = NULL;
    c_graph_vertex_t* curr_vertex = graph->vertices;
    while(curr_vertex && curr_vertex->id != id) {
        prev_vertex = curr_vertex;
        curr_vertex = curr_vertex->next;
    }

    if (!curr_vertex) return -1; // Vertex not found

    // Remove vertex from linked list
    if (prev_vertex) {
        prev_vertex->next = curr_vertex->next;
    } else {
        graph->vertices = curr_vertex->next;
    }

    // Free all edges of the removed vertex
    c_graph_edge_t* edge = curr_vertex->edges;
    while(edge) {
        c_graph_edge_t* temp = edge;
        edge = edge->next;
        free(temp);
    }
    free(curr_vertex);

    // Remove all edges pointing to the deleted vertex
    c_graph_vertex_t* temp_vertex = graph->vertices;
    while(temp_vertex) {
        graph_remove_edge(graph, temp_vertex->id, id);
        temp_vertex = temp_vertex->next;
    }

    return 0;
}

/*
 * Function: graph_remove_edge
 * ---------------------------
 * Removes the edge from src_id to dest_id. For undirected graphs, also removes the reverse edge.
 *
 * graph: pointer to the graph structure
 * src_id: source vertex ID
 * dest_id: destination vertex ID
 *
 * returns: 0 if successful, -1 if source or destination vertex not found
 */
int graph_remove_edge(c_graph_t* graph, int src_id, int dest_id) {
    if (!graph) return -1;

    // Find source vertex
    c_graph_vertex_t* src_vertex = graph->vertices;
    while(src_vertex && src_vertex->id != src_id) {
        src_vertex = src_vertex->next;
    }
    if (!src_vertex) return -1;

    // Remove edge from source to destination
    c_graph_edge_t* prev_edge = NULL;
    c_graph_edge_t* curr_edge = src_vertex->edges;
    while (curr_edge && curr_edge->dest_id != dest_id) {
        prev_edge = curr_edge;
        curr_edge = curr_edge->next;
    }
    if (curr_edge) {
        if (prev_edge) {
            prev_edge->next = curr_edge->next;
        } else {
            src_vertex->edges = curr_edge->next;
        }
        free(curr_edge);
    }

    // If undirected, remove reverse edge
    if (!graph->directed) {
        c_graph_vertex_t* dest_vertex = graph->vertices;
        while(dest_vertex && dest_vertex->id != dest_id) {
            dest_vertex = dest_vertex->next;
        }
        if (dest_vertex) {
            prev_edge = NULL;
            curr_edge = dest_vertex->edges;
            while (curr_edge && curr_edge->dest_id != src_id) {
                prev_edge = curr_edge;
                curr_edge = curr_edge->next;
            }
            if (curr_edge) {
                if (prev_edge) {
                    prev_edge->next = curr_edge->next;
                } else {
                    dest_vertex->edges = curr_edge->next;
                }
                free(curr_edge);
            }
        }
    }

    return 0;
}

/*
 * Function: graph_destroy
 * -----------------------
 * Frees all memory allocated for the graph, including vertices and edges.
 *
 * graph: pointer to the graph structure
 *
 * returns: void
 */
void graph_destroy(c_graph_t* graph) {
    if (!graph) return;

    c_graph_vertex_t* current_vertex = graph->vertices;
    while (current_vertex) {
        c_graph_edge_t* current_edge = current_vertex->edges;
        while (current_edge) {
            c_graph_edge_t* temp_edge = current_edge;
            current_edge = current_edge->next;
            free(temp_edge);
        }
        c_graph_vertex_t* temp_vertex = current_vertex;
        current_vertex = current_vertex->next;
        free(temp_vertex);
    }
    free(graph);
}

/*
 * Function: graph_add_edge
 * ------------------------
 * Adds an edge from src_id to dest_id with a given weight.
 * For undirected graphs, also adds the reverse edge.
 *
 * graph: pointer to the graph structure
 * src_id: source vertex ID
 * dest_id: destination vertex ID
 * weight: weight of the edge
 *
 * returns: 0 if successful, -1 if vertices not found or allocation fails
 */
int graph_add_edge(c_graph_t* graph, int src_id, int dest_id, double weight) {
    if (!graph) return -1;

    c_graph_vertex_t* src_vertex = NULL;
    c_graph_vertex_t* dest_vertex = NULL;
    c_graph_vertex_t* current = graph->vertices;

    // Find source and destination vertices
    while (current) {
        if (current->id == src_id) src_vertex = current;
        if (current->id == dest_id) dest_vertex = current;
        current = current->next;
    }
    if (!src_vertex || !dest_vertex) return -1;

    // Add edge from source to destination
    c_graph_edge_t* new_edge = (c_graph_edge_t*)malloc(sizeof(c_graph_edge_t));
    if (!new_edge) return -1;
    new_edge->dest_id = dest_id;
    new_edge->weight = weight;
    new_edge->next = src_vertex->edges;
    src_vertex->edges = new_edge;

    // If undirected, add reverse edge
    if (!graph->directed) {
        c_graph_edge_t* new_edge_back = (c_graph_edge_t*)malloc(sizeof(c_graph_edge_t));
        if (!new_edge_back) return -1;
        new_edge_back->dest_id = src_id;
        new_edge_back->weight = weight;
        new_edge_back->next = dest_vertex->edges;
        dest_vertex->edges = new_edge_back;
    }

    return 0;
}
