#ifndef C_GRAPH_H
#define C_GRAPH_H

/**
 * @brief Opaque pointer to the graph structure.
 */
typedef struct c_graph_t c_graph_t;

/**
 * @brief Creates a new graph.
 *
 * @param directed 0 for undirected, 1 for directed.
 * @return A pointer to the newly created graph, or NULL on failure.
 */
c_graph_t* graph_create(int directed);

/**
 * @brief Destroys a graph and frees all associated memory.
 *
 * @param graph The graph to destroy.
 */
void graph_destroy(c_graph_t* graph);

/**
 * @brief Adds a vertex to the graph.
 *
 * @param graph The graph.
 * @param id The ID of the vertex to add.
 * @return 0 on success, -1 on failure.
 */
int graph_add_vertex(c_graph_t* graph, int id);

/**
 * @brief Adds an edge to the graph.
 *
 * @param graph The graph.
 * @param src_id The ID of the source vertex.
 * @param dest_id The ID of the destination vertex.
 * @param weight The weight of the edge.
 * @return 0 on success, -1 on failure.
 */
int graph_add_edge(c_graph_t* graph, int src_id, int dest_id, double weight);

/**
 * @brief Removes a vertex from the graph.
 *
 * @param graph The graph.
 * @param id The ID of the vertex to remove.
 * @return 0 on success, -1 on failure.
 */
int graph_remove_vertex(c_graph_t* graph, int id);

/**
 * @brief Removes an edge from the graph.
 *
 * @param graph The graph.
 * @param src_id The ID of the source vertex.
 * @param dest_id The ID of the destination vertex.
 * @return 0 on success, -1 on failure.
 */
int graph_remove_edge(c_graph_t* graph, int src_id, int dest_id);

/**
 * @brief Performs a Breadth-First Search to find the shortest path in an unweighted graph.
 *
 * @param graph The graph.
 * @param start_id The starting vertex ID.
 * @param end_id The ending vertex ID.
 * @param path_len A pointer to store the length of the path.
 * @return An array of vertex IDs representing the path, or NULL if no path is found. The caller must free this array.
 */
int* graph_bfs(c_graph_t* graph, int start_id, int end_id, int* path_len);

/**
 * @brief Performs a Depth-First Search traversal of the graph.
 *
 * @param graph The graph.
 * @param start_id The starting vertex ID.
 * @param path_len A pointer to store the length of the traversal path.
 * @return An array of vertex IDs representing the DFS traversal. The caller must free this array.
 */
int* graph_dfs(c_graph_t* graph, int start_id, int* path_len);

/**
 * @brief Finds the shortest path in a weighted graph using Dijkstra's algorithm.
 *
 * @param graph The graph.
 * @param start_id The starting vertex ID.
 * @param end_id The ending vertex ID.
 * @param path_len A pointer to store the length of the path.
 * @return An array of vertex IDs representing the shortest path, or NULL if no path is found. The caller must free this array.
 */
int* graph_dijkstra(c_graph_t* graph, int start_id, int end_id, int* path_len);

#endif // C_GRAPH_H
