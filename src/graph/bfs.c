#include "c_graph_internal.h"
#include <stdlib.h>
#include <stdbool.h>

// Simple queue implementation for BFS
typedef struct queue_node_t {
    int id;
    struct queue_node_t* next;
} queue_node_t;

typedef struct queue_t {
    queue_node_t* front;
    queue_node_t* rear;
} queue_t;

static queue_t* queue_create() {
    queue_t* q = (queue_t*)malloc(sizeof(queue_t));
    q->front = q->rear = NULL;
    return q;
}

static void queue_enqueue(queue_t* q, int id) {
    queue_node_t* new_node = (queue_node_t*)malloc(sizeof(queue_node_t));
    new_node->id = id;
    new_node->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = new_node;
        return;
    }
    q->rear->next = new_node;
    q->rear = new_node;
}

static int queue_dequeue(queue_t* q) {
    if (q->front == NULL) return -1;
    queue_node_t* temp = q->front;
    int id = temp->id;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return id;
}

static bool queue_is_empty(queue_t* q) {
    return q->front == NULL;
}

static void queue_destroy(queue_t* q) {
    while (!queue_is_empty(q)) {
        queue_dequeue(q);
    }
    free(q);
}

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

int* graph_bfs(c_graph_t* graph, int start_id, int end_id, int* path_len) {
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
    int* parent = (int*)malloc((max_id + 1) * sizeof(int));
    for (int i = 0; i <= max_id; ++i) {
        parent[i] = -1;
    }

    if (!visited || !parent) {
        free(visited);
        free(parent);
        *path_len = 0;
        return NULL;
    }

    queue_t* q = queue_create();
    visited[start_id] = true;
    queue_enqueue(q, start_id);

    bool found = false;
    while (!queue_is_empty(q)) {
        int u = queue_dequeue(q);

        if (u == end_id) {
            found = true;
            break;
        }

        c_graph_vertex_t* u_vertex = graph->vertices;
        while(u_vertex && u_vertex->id != u) {
            u_vertex = u_vertex->next;
        }

        if (u_vertex) {
            c_graph_edge_t* edge = u_vertex->edges;
            while (edge) {
                int v = edge->dest_id;
                if (!visited[v]) {
                    visited[v] = true;
                    parent[v] = u;
                    queue_enqueue(q, v);
                }
                edge = edge->next;
            }
        }
    }

    queue_destroy(q);
    free(visited);

    if (!found) {
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
