#include "binary_search_tree.h"
#include <stdio.h>
#include <stdlib.h>

// Helper function to print tree (in-order traversal)
void print_in_order(Node *root) {
    if (root == NULL) return;
    print_in_order(root->left);
    printf("%d ", root->value);
    print_in_order(root->right);
}

// Helper function to print tree structure (pre-order)
void print_tree_structure(Node *root, int depth) {
    if (root == NULL) {
        printf("%*sNULL\n", depth * 4, "");
        return;
    }
    
    printf("%*s%d\n", depth * 4, "", root->value);
    print_tree_structure(root->left, depth + 1);
    print_tree_structure(root->right, depth + 1);
}

// Helper function to count nodes
int count_nodes(Node *root) {
    if (root == NULL) return 0;
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

void example1_basic_operations() {
    printf("=== Example 1: Basic BST Operations ===\n\n");
    
    printf("1. Creating and inserting into BST:\n");
    Node *root = NULL;
    
    // Create initial tree
    int values[] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65, 75};
    printf("   Inserting values: ");
    for (int i = 0; i < 11; i++) {
        printf("%d ", values[i]);
        if (root == NULL) {
            root = create_node(values[i]);
        } else {
            binary_insert(root, values[i]);
        }
    }
    printf("\n\n");
    
    printf("2. Tree contents (in-order): ");
    print_in_order(root);
    printf("\n   Total nodes: %d\n\n", count_nodes(root));
    
    printf("3. Searching for values:\n");
    int search_values[] = {40, 65, 90, 25};
    for (int i = 0; i < 4; i++) {
        int val = search_values[i];
        Node *iter = binary_search(root, val);
        Node *rec = binary_search_recursive(root, val);
        
        printf("   Value %d: ", val);
        if (iter) {
            printf("FOUND (iterative & recursive agree)\n");
        } else {
            printf("NOT FOUND\n");
        }
    }
    printf("\n");
    
    printf("4. Tree structure (simplified):\n");
    printf("       50\n");
    printf("     /    \\\n");
    printf("    30     70\n");
    printf("   /  \\   /  \\\n");
    printf("  20  40 60   80\n");
    printf("     / \\   \\  / \\\n");
    printf("    35 45  65 75 NULL\n");
    printf("\n");
    
    destroy_binary_search_tree(root);
}

void example2_deletion_demo() {
    printf("=== Example 2: Deletion Demonstration ===\n\n");
    
    printf("Creating a BST:\n");
    Node *root = create_node(50);
    binary_insert(root, 30);
    binary_insert(root, 70);
    binary_insert(root, 20);
    binary_insert(root, 40);
    binary_insert(root, 60);
    binary_insert(root, 80);
    binary_insert(root, 35);
    binary_insert(root, 45);
    binary_insert(root, 65);
    binary_insert(root, 75);
    binary_insert(root, 85);
    
    printf("Initial tree (in-order): ");
    print_in_order(root);
    printf("\nNodes: %d\n\n", count_nodes(root));
    
    printf("1. Deleting leaf node (20):\n");
    printf("   Before: ");
    print_in_order(root);
    printf("\n");
    
    delete_node(&root, 20);
    
    printf("   After:  ");
    print_in_order(root);
    printf("\n   Nodes: %d\n\n", count_nodes(root));
    
    printf("2. Deleting node with one child (40 has children 35, 45):\n");
    printf("   Before: ");
    print_in_order(root);
    printf("\n");
    
    delete_node(&root, 40);
    
    printf("   After:  ");
    print_in_order(root);
    printf("\n   Nodes: %d\n\n", count_nodes(root));
    
    printf("3. Deleting node with two children (70 has children 60, 80):\n");
    printf("   Before: ");
    print_in_order(root);
    printf("\n");
    
    delete_node(&root, 70);
    
    printf("   After:  ");
    print_in_order(root);
    printf("\n   Nodes: %d\n\n", count_nodes(root));
    
    printf("4. Trying to delete non-existing node (99):\n");
    int result = delete_node(&root, 99);
    printf("   Result: %s (0 = failed, 1 = success)\n", result ? "Success" : "Failed");
    printf("   Nodes remain: %d\n\n", count_nodes(root));
    
    printf("5. Final tree state:\n");
    printf("   In-order: ");
    print_in_order(root);
    printf("\n");
    
    destroy_binary_search_tree(root);
}

void example3_interactive_demo() {
    printf("=== Example 3: Interactive BST Demo ===\n\n");
    
    Node *root = NULL;
    int choice, value;
    
    do {
        printf("\nCurrent tree (in-order): ");
        if (root == NULL) {
            printf("EMPTY");
        } else {
            print_in_order(root);
            printf("  (Nodes: %d)", count_nodes(root));
        }
        printf("\n\n");
        
        printf("1. Insert value\n");
        printf("2. Search value (iterative)\n");
        printf("3. Search value (recursive)\n");
        printf("4. Delete value\n");
        printf("5. Clear tree\n");
        printf("6. Show tree structure\n");
        printf("0. Exit\n");
        printf("\nChoose: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                if (root == NULL) {
                    root = create_node(value);
                } else {
                    binary_insert(root, value);
                }
                printf("Value %d inserted\n", value);
                break;
                
            case 2:
                printf("Enter value to search: ");
                scanf("%d", &value);
                Node *result = binary_search(root, value);
                if (result) {
                    printf("Value %d FOUND in tree\n", value);
                } else {
                    printf("Value %d NOT FOUND in tree\n", value);
                }
                break;
                
            case 3:
                printf("Enter value to search: ");
                scanf("%d", &value);
                result = binary_search_recursive(root, value);
                if (result) {
                    printf("Value %d FOUND in tree\n", value);
                } else {
                    printf("Value %d NOT FOUND in tree\n", value);
                }
                break;
                
            case 4:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                if (root == NULL) {
                    printf("Tree is empty!\n");
                } else {
                    int delete_result = delete_node(&root, value);
                    if (delete_result) {
                        printf("Value %d deleted successfully\n", value);
                    } else {
                        printf("Value %d not found for deletion\n", value);
                    }
                }
                break;
                
            case 5:
                destroy_binary_search_tree(root);
                root = NULL;
                printf("Tree cleared\n");
                break;
                
            case 6:
                printf("\nTree structure:\n");
                if (root == NULL) {
                    printf("EMPTY\n");
                } else {
                    print_tree_structure(root, 0);
                }
                break;
                
            case 0:
                printf("Exiting...\n");
                break;
                
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);
    
    if (root != NULL) {
        destroy_binary_search_tree(root);
    }
}

int main() {
    printf("=== Binary Search Tree Examples ===\n\n");
    
    example1_basic_operations();
    printf("\n" "="  "="  "="  "="  "="  "="  "="  "="  "="  "="  "="  "="  "="  "="  "="  "="  "="  "\n\n");
    example2_deletion_demo();
    printf("\n" "="  "="  "="  "="  "="  "="  "="  "="  "="  "="  "="  "="  "="  "="  "="  "="  "="  "\n\n");
    example3_interactive_demo();
    
    printf("\n=== Examples completed ===\n");
    return 0;
}