#include "binary_search_tree.h"
#include <stdio.h>
#include <stdlib.h>

Node *create_node(int value){
    if (value == NULL) return NULL;

    Node *node = malloc(sizeof(Node));

    if (node == NULL) return NULL;
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void destroy_binary_search_tree(Node *root){
    if (root == NULL) return;

    destroy_binary_search_tree(root->right);
    destroy_binary_search_tree(root->left);

    free(root);
}

Node *binary_insert(Node *root, int value){
    if (root == NULL && value != NULL){
        Node *new_node = create_node(value);

        if (new_node == NULL) return NULL; // free(new_node) should i write it or not?

        return new_node;
    }


    Node *current = root;
    Node *parent = NULL;

    while (current != NULL){
        parent = current;

        if (value < current->value) // or it should be <=?
            current = current->left;
        else
            current = current->right; 
    }

    Node *newNode = create_node(value);

    if (newNode == NULL) return NULL;

    if (value < parent->value)
        parent->left = newNode;
    else
        parent->right = newNode;

    return newNode; // or i should return integer (1 or 0)??
}

Node *binary_search(Node *root, int target){
    if (root == NULL) return NULL;

    Node *current = root;

    while (current != NULL){
        if (current->value == target) return current;

        if (target > current->value){
            current = current->right;
        }
        else{
            current = current->left;
        }
    }

    return NULL; // maybe it should return integer
}

Node *binary_search_recursive(Node *root, int target){
    if (root == NULL) return NULL;

    if (target == root->value) return root;

    if (target > root->value) {
        return binary_search_recursive(root->right, target);
    }
    else{
        return binary_search_recursive(root->left, target);
    }
}

int delete_node(Node **root, int target){
    if (*root == NULL) return 0;

    if (target < *(root)->value){
        return delete_node(&(*root)->left, value);
    }
    else if (target > *(root)->value){
        return delete(&(*root)->right, value);
    }
    else{
        Node *temp_node = *root;

        if ((*root)->left == NULL && (*root)->right == NULL) { //it has no children at all
            free(*root);
            *root = NULL;
        }
        else if ((*root)->left == NULL) { // has only one child which is on the right side
            *root = (*root)->right;
            free(temp);
        }
        else if ((*root)->right == NULL) { // left side child
            *root = (*root)->left;
            free(temp);
        }
        else { //has two children, removing parent and replacing it with his child(greatest)
            Node *min_node_right_child = (*root)->right;

            while (min_node_right_child->left){
                min_node_right_child = minRight->left;
            }

            (*root)->value = min_node_right_child->value;
            delete(&(*root)->right, min_node_right_child->value);
        }
    return 1;
    }
}