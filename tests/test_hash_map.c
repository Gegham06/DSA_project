#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "c_hash_map.h"

// Test 1: Basic creation and destruction
void test_create_destroy() {
    printf("Test 1: Create and Destroy... ");
    
    HashMap *map = create_hash_map(10);
    assert(map != NULL);
    assert(map->capacity == 10);
    assert(map->buckets != NULL);
    
    destroy_hash_map(map);
    printf("✓\n");
}

// Test 2: Basic insert and get
void test_insert_get() {
    printf("Test 2: Insert and Get... ");
    
    HashMap *map = create_hash_map(10);
    
    // Test successful insert
    assert(hash_map_insert(map, "key1", "value1") >= 0);
    assert(hash_map_insert(map, "key2", "value2") >= 0);
    
    // Test retrieval
    char *val1 = hash_map_get(map, "key1");
    char *val2 = hash_map_get(map, "key2");
    
    assert(val1 != NULL);
    assert(val2 != NULL);
    assert(strcmp(val1, "value1") == 0);
    assert(strcmp(val2, "value2") == 0);
    
    // Test non-existent key
    assert(hash_map_get(map, "nonexistent") == NULL);
    
    destroy_hash_map(map);
    printf("✓\n");
}

// Test 3: Update existing key
void test_update() {
    printf("Test 3: Update existing key... ");
    
    HashMap *map = create_hash_map(10);
    
    // Insert initial value
    hash_map_insert(map, "key", "old_value");
    assert(strcmp(hash_map_get(map, "key"), "old_value") == 0);
    
    // Update value
    int result = hash_map_insert(map, "key", "new_value");
    assert(result == 1); // Should return 1 for update
    
    // Verify update
    assert(strcmp(hash_map_get(map, "key"), "new_value") == 0);
    
    destroy_hash_map(map);
    printf("✓\n");
}

// Test 4: Delete operations
void test_delete() {
    printf("Test 4: Delete operations... ");
    
    HashMap *map = create_hash_map(10);
    
    // Insert some values
    hash_map_insert(map, "key1", "value1");
    hash_map_insert(map, "key2", "value2");
    hash_map_insert(map, "key3", "value3");
    
    // Delete existing key
    int delete_result = hash_map_delete(map, "key2");
    assert(delete_result == 1); // Should return 1 for successful delete
    
    // Verify deletion
    assert(hash_map_get(map, "key2") == NULL);
    
    // Verify other keys still exist
    assert(hash_map_get(map, "key1") != NULL);
    assert(hash_map_get(map, "key3") != NULL);
    
    // Delete non-existent key
    delete_result = hash_map_delete(map, "nonexistent");
    assert(delete_result == 0); // Should return 0 for non-existent key
    
    destroy_hash_map(map);
    printf("✓\n");
}

// Test 5: NULL handling
void test_null_handling() {
    printf("Test 5: NULL handling... ");
    
    // Test with NULL map
    assert(hash_map_insert(NULL, "key", "value") == -1);
    assert(hash_map_get(NULL, "key") == NULL);
    assert(hash_map_delete(NULL, "key") == -1);
    
    // Test with NULL key/value
    HashMap *map = create_hash_map(10);
    assert(hash_map_insert(map, NULL, "value") == -1);
    assert(hash_map_insert(map, "key", NULL) == -1);
    assert(hash_map_get(map, NULL) == NULL);
    assert(hash_map_delete(map, NULL) == -1);
    
    destroy_hash_map(map);
    printf("✓\n");
}

// Test 6: Collision handling
void test_collisions() {
    printf("Test 6: Collision handling... ");
    
    // Create very small map to force collisions
    HashMap *map = create_hash_map(2);
    
    // Insert multiple keys (will collide in 2 buckets)
    hash_map_insert(map, "a", "value_a");
    hash_map_insert(map, "b", "value_b");
    hash_map_insert(map, "c", "value_c");
    hash_map_insert(map, "d", "value_d");
    
    // All should be retrievable
    assert(hash_map_get(map, "a") != NULL);
    assert(hash_map_get(map, "b") != NULL);
    assert(hash_map_get(map, "c") != NULL);
    assert(hash_map_get(map, "d") != NULL);
    
    // Delete from chain
    hash_map_delete(map, "b");
    assert(hash_map_get(map, "b") == NULL);
    assert(hash_map_get(map, "a") != NULL);
    assert(hash_map_get(map, "c") != NULL);
    assert(hash_map_get(map, "d") != NULL);
    
    destroy_hash_map(map);
    printf("✓\n");
}

// Test 7: Memory allocation failure simulation
void test_memory_handling() {
    printf("Test 7: Memory handling... ");
    
    // Test zero capacity
    assert(create_hash_map(0) == NULL);
    
    // Test negative capacity
    assert(create_hash_map(-5) == NULL);
    
    // Note: Can't easily test malloc failures without mocking
    
    printf("✓\n");
}

// Test 8: Hash function consistency
void test_hash_function() {
    printf("Test 8: Hash function consistency... ");
    
    // Same string should produce same hash
    unsigned int hash1 = hash_function("test");
    unsigned int hash2 = hash_function("test");
    assert(hash1 == hash2);
    
    // Different strings should (usually) produce different hashes
    unsigned int hash3 = hash_function("test1");
    unsigned int hash4 = hash_function("test2");
    // Note: There's a small chance of collision, but very unlikely
    
    // Empty string should work
    unsigned int hash5 = hash_function("");
    
    printf("✓\n");
}

int main() {
    printf("Running Hash Map Test Suite\n");
    printf("===========================\n\n");
    
    test_create_destroy();
    test_insert_get();
    test_update();
    test_delete();
    test_null_handling();
    test_collisions();
    test_memory_handling();
    test_hash_function();
    
    printf("\nAll tests passed! ✓\n");
    
    return 0;
}