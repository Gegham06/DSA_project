#include "binary_search_tree.h"
#include <stdio.h>
#include <stdlib.h>

/* Function prototypes for tree traversal */
void inorder_traversal(Node *root);
void preorder_traversal(Node *root);
void postorder_traversal(Node *root);

int main() {
    printf("=== BST Demo ===\n");

    // Create BST and insert nodes
    Node *root = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(values)/sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        if (root == NULL) {
            root = binary_insert(root, values[i]);
        } else {
            binary_insert(root, values[i]);
        }
    }

    // Diagram of the BST (ASCII)
    printf("\n=== Sample BST Diagram ===\n");
    printf("        50\n");
    printf("       /  \\\n");
    printf("     30    70\n");
    printf("    / \\    / \\\n");
    printf("  20  40  60  80\n");

    // Traversals
    printf("\n=== Inorder Traversal ===\n");
    inorder_traversal(root);
    printf("\n");

    printf("\n=== Preorder Traversal ===\n");
    preorder_traversal(root);
    printf("\n");

    printf("\n=== Postorder Traversal ===\n");
    postorder_traversal(root);
    printf("\n");

    // Clean up
    destroy_binary_search_tree(root);

    return 0;
}

void inorder_traversal(Node *root) {
    if (root == NULL) return;
    inorder_traversal(root->left);
    printf("%d ", root->value);
    inorder_traversal(root->right);
}

void preorder_traversal(Node *root) {
    if (root == NULL) return;
    printf("%d ", root->value);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

void postorder_traversal(Node *root) {
    if (root == NULL) return;
    postorder_traversal(root->left);
    postorder_traversal(root->right);
    printf("%d ", root->value);
}
