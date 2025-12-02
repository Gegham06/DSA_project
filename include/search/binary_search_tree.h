#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

typedef struct node{
    int value;
    struct node *right;
    struct node *left;
}Node;

Node *create_node(int value);
void destroy_binary_search_tree(Node *root);
Node *binary_insert(Node *root, int target);
Node *binary_search(Node *root, int target);
Node *binary_search_recursive(Node *root, int target);
int delete_node(Node **root, int target);


#endif