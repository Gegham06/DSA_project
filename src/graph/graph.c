#include "c_graph_internal.h"
#include <stdlib.h>

static c_graph_vertex_t* find_vertex(c_graph_t* graph, int id);
static int remove_edge_from_vertex(c_graph_vertex_t* vertex, int dest_id);

static c_graph_vertex_t* find_vertex(c_graph_t* graph, int id) {
    c_graph_vertex_t* current = graph->vertices;
    while (current) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

c_graph_t* graph_create(int directed) {
    c_graph_t* graph = (c_graph_t*)malloc(sizeof(c_graph_t));
    if (graph) {
        graph->directed = directed;
        graph->vertices = NULL;
    }
    return graph;
}

int graph_add_vertex(c_graph_t* graph, int id) {
    if (!graph || find_vertex(graph, id)) {
        return -1; // Graph is null or vertex already exists
    }

    c_graph_vertex_t* new_vertex = (c_graph_vertex_t*)malloc(sizeof(c_graph_vertex_t));
    if (!new_vertex) return -1;

    new_vertex->id = id;
    new_vertex->edges = NULL;
    new_vertex->next = graph->vertices;
    graph->vertices = new_vertex;

    return 0;
}

int graph_remove_vertex(c_graph_t* graph, int id) {
    if (!graph) return -1;

    c_graph_vertex_t* vertex_to_remove = find_vertex(graph, id);
    if (!vertex_to_remove) return -1;

    // Remove the vertex from the list
    if (graph->vertices == vertex_to_remove) {
        graph->vertices = vertex_to_remove->next;
    } else {
        c_graph_vertex_t* current = graph->vertices;
        while (current->next && current->next != vertex_to_remove) {
            current = current->next;
        }
        if (current->next) {
            current->next = vertex_to_remove->next;
        }
    }

    // Free edges of the removed vertex
    c_graph_edge_t* edge = vertex_to_remove->edges;
    while (edge) {
        c_graph_edge_t* temp = edge;
        edge = edge->next;
        free(temp);
    }
    free(vertex_to_remove);

    // Remove all edges pointing to the deleted vertex
    c_graph_vertex_t* temp_vertex = graph->vertices;
    while (temp_vertex) {
        remove_edge_from_vertex(temp_vertex, id);
        temp_vertex = temp_vertex->next;
    }

    return 0;
}

static int remove_edge_from_vertex(c_graph_vertex_t* vertex, int dest_id) {
    if (!vertex) return -1;

    c_graph_edge_t* prev_edge = NULL;
    c_graph_edge_t* curr_edge = vertex->edges;
    while (curr_edge && curr_edge->dest_id != dest_id) {
        prev_edge = curr_edge;
        curr_edge = curr_edge->next;
    }

    if (curr_edge) {
        if (prev_edge) {
            prev_edge->next = curr_edge->next;
        } else {
            vertex->edges = curr_edge->next;
        }
        free(curr_edge);
        return 0;
    }
    return -1; // Edge not found
}

int graph_remove_edge(c_graph_t* graph, int src_id, int dest_id) {
    if (!graph) return -1;

    c_graph_vertex_t* src_vertex = find_vertex(graph, src_id);
    if (!src_vertex) return -1;

    int result = remove_edge_from_vertex(src_vertex, dest_id);

    if (!graph->directed) {
        c_graph_vertex_t* dest_vertex = find_vertex(graph, dest_id);
        if (dest_vertex) {
            remove_edge_from_vertex(dest_vertex, src_id);
        }
    }

    return result;
}

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

int graph_add_edge(c_graph_t* graph, int src_id, int dest_id, double weight) {
    if (!graph) return -1;

    c_graph_vertex_t* src_vertex = find_vertex(graph, src_id);
    c_graph_vertex_t* dest_vertex = find_vertex(graph, dest_id);

    if (!src_vertex || !dest_vertex) return -1;

    c_graph_edge_t* new_edge = (c_graph_edge_t*)malloc(sizeof(c_graph_edge_t));
    if (!new_edge) return -1;

    new_edge->dest_id = dest_id;
    new_edge->weight = weight;
    new_edge->next = src_vertex->edges;
    src_vertex->edges = new_edge;

    if (!graph->directed) {
        c_graph_edge_t* new_edge_back = (c_graph_edge_t*)malloc(sizeof(c_graph_edge_t));
        if (!new_edge_back) {
            // Clean up the forward edge if the reverse edge allocation fails
            src_vertex->edges = new_edge->next;
            free(new_edge);
            return -1;
        }
        new_edge_back->dest_id = src_id;
        new_edge_back->weight = weight;
        new_edge_back->next = dest_vertex->edges;
        dest_vertex->edges = new_edge_back;
    }

    return 0;
}
