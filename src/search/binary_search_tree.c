#include "include/binary_search_tree.h"
#include <stdio.h>
#include <stdlib.h>

/* 
 * Function: create_node
 * ---------------------
 * Allocates and initializes a new BST node with a given value.
 *
 * value: The integer value to store in the node.
 *
 * returns: Pointer to the newly created node, or NULL on allocation failure.
 */
Node *create_node(int value){
    Node *node = malloc(sizeof(Node));
    if (node == NULL) return NULL;

    node->value = value;   /* Store the value */
    node->left = NULL;     /* Initialize left child as NULL */
    node->right = NULL;    /* Initialize right child as NULL */

    return node;
}

/* 
 * Function: destroy_binary_search_tree
 * ------------------------------------
 * Recursively frees all nodes in the BST.
 *
 * root: Pointer to the root node of the tree.
 */
void destroy_binary_search_tree(Node *root){
    if (root == NULL) return;

    /* Recursively destroy right and left subtrees */
    destroy_binary_search_tree(root->right);
    destroy_binary_search_tree(root->left);

    free(root); /* Free current node */
}

/* 
 * Function: binary_insert
 * -----------------------
 * Inserts a value into the BST. If the tree is empty, creates a new root.
 *
 * root: Pointer to the root node.
 * value: Value to insert.
 *
 * returns: Pointer to the newly inserted node, or NULL on failure.
 */
Node *binary_insert(Node *root, int value){
    if (root == NULL){
        Node *new_node = create_node(value);
        return new_node; /* Return new root */
    }

    Node *current = root;
    Node *parent = NULL;

    /* Traverse tree to find insertion point */
    while (current != NULL){
        parent = current;
        if (value < current->value)
            current = current->left;
        else
            current = current->right; 
    }

    /* Create new node */
    Node *newNode = create_node(value);
    if (newNode == NULL) return NULL;

    /* Attach new node to parent */
    if (value < parent->value)
        parent->left = newNode;
    else
        parent->right = newNode;

    return newNode;
}

/* 
 * Function: binary_search
 * -----------------------
 * Iteratively searches for a target value in the BST.
 *
 * root: Pointer to the root node.
 * target: Value to search for.
 *
 * returns: Pointer to the node containing the target, or NULL if not found.
 */
Node *binary_search(Node *root, int target){
    Node *current = root;

    while (current != NULL){
        if (current->value == target) return current;
        if (target > current->value)
            current = current->right;
        else
            current = current->left;
    }

    return NULL;
}

/* 
 * Function: binary_search_recursive
 * ---------------------------------
 * Recursively searches for a target value in the BST.
 *
 * root: Pointer to the root node.
 * target: Value to search for.
 *
 * returns: Pointer to the node containing the target, or NULL if not found.
 */
Node *binary_search_recursive(Node *root, int target){
    if (root == NULL) return NULL;

    if (target == root->value) return root;

    if (target > root->value) 
        return binary_search_recursive(root->right, target);
    else
        return binary_search_recursive(root->left, target);
}

/* 
 * Function: delete_node
 * ---------------------
 * Deletes a node with a specified value from the BST.
 *
 * root: Pointer to the root pointer of the tree.
 * target: Value to delete.
 *
 * returns: 1 if deletion was successful, 0 if node not found.
 */
int delete_node(Node **root, int target){
    if (*root == NULL) return 0;

    if (target < (*root)->value){
        return delete_node(&(*root)->left, target);
    }
    else if (target > (*root)->value){
        return delete_node(&(*root)->right, target);
    }
    else{
        Node *temp_node = *root;

        /* Case 1: No children */
        if ((*root)->left == NULL && (*root)->right == NULL) {
            free(*root);
            *root = NULL;
        }
        /* Case 2: Only right child */
        else if ((*root)->left == NULL) {
            *root = (*root)->right;
            free(temp_node);
        }
        /* Case 3: Only left child */
        else if ((*root)->right == NULL) {
            *root = (*root)->left;
            free(temp_node);
        }
        /* Case 4: Two children */
        else {
            Node *min_node_right_child = (*root)->right;

            /* Find the smallest node in the right subtree */
            while (min_node_right_child->left){
                min_node_right_child = min_node_right_child->left;
            }

            /* Replace value and delete the successor node */
            (*root)->value = min_node_right_child->value;
            delete_node(&(*root)->right, min_node_right_child->value);
        }
        return 1;
    }
}
