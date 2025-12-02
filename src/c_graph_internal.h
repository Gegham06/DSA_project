#ifndef C_GRAPH_INTERNAL_H
#define C_GRAPH_INTERNAL_H

#include "../include/c_graph.h"

// Internal data structures
typedef struct c_graph_edge_t {
    int dest_id;
    double weight;
    struct c_graph_edge_t* next;
} c_graph_edge_t;

typedef struct c_graph_vertex_t {
    int id;
    c_graph_edge_t* edges;
    struct c_graph_vertex_t* next;
} c_graph_vertex_t;

struct c_graph_t {
    int directed;
    c_graph_vertex_t* vertices;
};

#endif // C_GRAPH_INTERNAL_H
