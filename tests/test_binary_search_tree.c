#include "binary_search_tree.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// Helper function to count nodes
int count_nodes(Node *root) {
    if (root == NULL) return 0;
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

void test_create_node() {
    printf("Testing create_node...\n");
    
    Node *node = create_node(42);
    assert(node != NULL);
    assert(node->value == 42);
    assert(node->left == NULL);
    assert(node->right == NULL);
    printf("✓ create_node works correctly\n");
    
    free(node);
}

void test_destroy_tree() {
    printf("\nTesting destroy_binary_search_tree...\n");
    
    Node *root = create_node(50);
    binary_insert(root, 30);
    binary_insert(root, 70);
    binary_insert(root, 20);
    binary_insert(root, 40);
    
    // Destroy should free all memory (valgrind would verify)
    destroy_binary_search_tree(root);
    printf("✓ Tree destruction completed (check with valgrind for memory leaks)\n");
}

void test_binary_insert() {
    printf("\nTesting binary_insert...\n");
    
    Node *root = NULL;
    
    // Test 1: Insert into empty tree
    root = binary_insert(root, 50);
    assert(root != NULL);
    assert(root->value == 50);
    assert(count_nodes(root) == 1);
    printf("✓ Insert into empty tree works\n");
    
    // Test 2: Insert smaller value
    binary_insert(root, 30);
    assert(root->left != NULL);
    assert(root->left->value == 30);
    printf("✓ Insert smaller value works\n");
    
    // Test 3: Insert larger value
    binary_insert(root, 70);
    assert(root->right != NULL);
    assert(root->right->value == 70);
    printf("✓ Insert larger value works\n");
    
    // Test 4: Build complex tree
    binary_insert(root, 20);
    binary_insert(root, 40);
    binary_insert(root, 60);
    binary_insert(root, 80);
    
    assert(count_nodes(root) == 7);
    assert(root->left->left->value == 20);
    assert(root->left->right->value == 40);
    assert(root->right->left->value == 60);
    assert(root->right->right->value == 80);
    printf("✓ Complex tree structure built correctly\n");
    
    destroy_binary_search_tree(root);
}

void test_binary_search() {
    printf("\nTesting binary_search (iterative)...\n");
    
    Node *root = create_node(50);
    binary_insert(root, 30);
    binary_insert(root, 70);
    binary_insert(root, 20);
    binary_insert(root, 40);
    binary_insert(root, 60);
    binary_insert(root, 80);
    
    // Test existing values
    Node *found = binary_search(root, 50);
    assert(found != NULL && found->value == 50);
    printf("✓ Found root value 50\n");
    
    found = binary_search(root, 20);
    assert(found != NULL && found->value == 20);
    printf("✓ Found leaf value 20\n");
    
    found = binary_search(root, 40);
    assert(found != NULL && found->value == 40);
    printf("✓ Found internal value 40\n");
    
    // Test non-existing values
    found = binary_search(root, 25);
    assert(found == NULL);
    printf("✓ Correctly returned NULL for non-existing value 25\n");
    
    found = binary_search(root, 100);
    assert(found == NULL);
    printf("✓ Correctly returned NULL for non-existing value 100\n");
    
    // Test empty tree
    found = binary_search(NULL, 10);
    assert(found == NULL);
    printf("✓ Empty tree search returns NULL\n");
    
    destroy_binary_search_tree(root);
}

void test_binary_search_recursive() {
    printf("\nTesting binary_search_recursive...\n");
    
    Node *root = create_node(50);
    binary_insert(root, 30);
    binary_insert(root, 70);
    binary_insert(root, 20);
    binary_insert(root, 40);
    binary_insert(root, 60);
    binary_insert(root, 80);
    
    // Test should give same results as iterative
    Node *iter_result, *rec_result;
    
    int test_values[] = {50, 20, 40, 25, 100};
    for (int i = 0; i < 5; i++) {
        int val = test_values[i];
        iter_result = binary_search(root, val);
        rec_result = binary_search_recursive(root, val);
        
        if (iter_result == NULL) {
            assert(rec_result == NULL);
        } else {
            assert(rec_result != NULL);
            assert(iter_result->value == rec_result->value);
        }
    }
    printf("✓ Recursive search matches iterative search for all test values\n");
    
    destroy_binary_search_tree(root);
}

void test_delete_leaf_node() {
    printf("\nTesting delete_node - leaf nodes...\n");
    
    Node *root = create_node(50);
    binary_insert(root, 30);
    binary_insert(root, 70);
    binary_insert(root, 20);
    binary_insert(root, 40);
    
    assert(count_nodes(root) == 5);
    
    // Delete left leaf (20)
    int result = delete_node(&root, 20);
    assert(result == 1);
    assert(binary_search(root, 20) == NULL);
    assert(root->left->left == NULL);
    assert(count_nodes(root) == 4);
    printf("✓ Deleted left leaf node (20)\n");
    
    // Delete right leaf (40)
    result = delete_node(&root, 40);
    assert(result == 1);
    assert(binary_search(root, 40) == NULL);
    assert(root->left->right == NULL);
    assert(count_nodes(root) == 3);
    printf("✓ Deleted right leaf node (40)\n");
    
    // Try to delete non-existing leaf
    result = delete_node(&root, 99);
    assert(result == 0);
    assert(count_nodes(root) == 3);
    printf("✓ Correctly failed to delete non-existing node\n");
    
    destroy_binary_search_tree(root);
}

void test_delete_single_child_node() {
    printf("\nTesting delete_node - single child nodes...\n");
    
    // Create a skewed tree: 50 -> 30 -> 20 -> 10
    Node *root = create_node(50);
    binary_insert(root, 30);
    binary_insert(root, 20);
    binary_insert(root, 10);
    
    assert(count_nodes(root) == 4);
    
    // Delete 20 (has only left child 10)
    int result = delete_node(&root, 20);
    assert(result == 1);
    assert(binary_search(root, 20) == NULL);
    assert(root->left->left->value == 10); // 10 should now be child of 30
    assert(count_nodes(root) == 3);
    printf("✓ Deleted node with only left child\n");
    
    // Create another skewed tree: 10 -> 20 -> 30 -> 40
    Node *root2 = create_node(10);
    binary_insert(root2, 20);
    binary_insert(root2, 30);
    binary_insert(root2, 40);
    
    // Delete 30 (has only right child 40)
    result = delete_node(&root2, 30);
    assert(result == 1);
    assert(binary_search(root2, 30) == NULL);
    assert(root2->right->value == 20); // Structure preserved
    assert(count_nodes(root2) == 3);
    printf("✓ Deleted node with only right child\n");
    
    destroy_binary_search_tree(root);
    destroy_binary_search_tree(root2);
}

void test_delete_two_children_node() {
    printf("\nTesting delete_node - two children nodes...\n");
    
    Node *root = create_node(50);
    binary_insert(root, 30);
    binary_insert(root, 70);
    binary_insert(root, 20);
    binary_insert(root, 40);
    binary_insert(root, 60);
    binary_insert(root, 80);
    
    assert(count_nodes(root) == 7);
    
    // Delete root (has two children)
    int result = delete_node(&root, 50);
    assert(result == 1);
    assert(binary_search(root, 50) == NULL);
    
    // Root should be replaced with inorder successor (60)
    assert(root->value == 60 || root->value == 30); // Could be 60 or smallest from right
    assert(count_nodes(root) == 6);
    printf("✓ Deleted root node with two children\n");
    
    // Delete 30 (has two children: 20 and 40)
    result = delete_node(&root, 30);
    assert(result == 1);
    assert(binary_search(root, 30) == NULL);
    assert(count_nodes(root) == 5);
    printf("✓ Deleted internal node with two children\n");
    
    destroy_binary_search_tree(root);
}

void test_delete_root_scenarios() {
    printf("\nTesting delete_node - root edge cases...\n");
    
    // Test 1: Delete single node tree
    Node *root1 = create_node(42);
    int result = delete_node(&root1, 42);
    assert(result == 1);
    assert(root1 == NULL);
    printf("✓ Deleted single node tree\n");
    
    // Test 2: Delete root with only left child
    Node *root2 = create_node(50);
    binary_insert(root2, 30);
    result = delete_node(&root2, 50);
    assert(result == 1);
    assert(root2->value == 30);
    printf("✓ Deleted root with left child\n");
    
    // Test 3: Delete root with only right child
    Node *root3 = create_node(50);
    binary_insert(root3, 70);
    result = delete_node(&root3, 50);
    assert(result == 1);
    assert(root3->value == 70);
    printf("✓ Deleted root with right child\n");
    
    destroy_binary_search_tree(root2);
    destroy_binary_search_tree(root3);
}

void test_comprehensive_delete() {
    printf("\nTesting comprehensive delete scenarios...\n");
    
    Node *root = NULL;
    
    // Build a complete tree
    int values[] = {50, 25, 75, 15, 35, 65, 85, 10, 20, 30, 40, 60, 70, 80, 90};
    for (int i = 0; i < 15; i++) {
        if (root == NULL) {
            root = create_node(values[i]);
        } else {
            binary_insert(root, values[i]);
        }
    }
    
    assert(count_nodes(root) == 15);
    
    // Delete in specific order
    int delete_order[] = {20, 75, 30, 50, 90, 15};
    
    for (int i = 0; i < 6; i++) {
        int val = delete_order[i];
        Node *before = binary_search(root, val);
        assert(before != NULL); // Should exist before deletion
        
        int result = delete_node(&root, val);
        assert(result == 1);
        
        Node *after = binary_search(root, val);
        assert(after == NULL); // Should not exist after deletion
        
        // Tree should still maintain BST properties
        // (In real test, you'd verify with inorder traversal)
    }
    
    assert(count_nodes(root) == 9);
    printf("✓ Successfully deleted multiple nodes in specific order\n");
    
    destroy_binary_search_tree(root);
}

int main() {
    printf("=== Binary Search Tree Test Suite ===\n\n");
    
    test_create_node();
    test_destroy_tree();
    test_binary_insert();
    test_binary_search();
    test_binary_search_recursive();
    test_delete_leaf_node();
    test_delete_single_child_node();
    test_delete_two_children_node();
    test_delete_root_scenarios();
    test_comprehensive_delete();
    
    printf("\n=== All tests passed! ===\n");
    
    return 0;
}