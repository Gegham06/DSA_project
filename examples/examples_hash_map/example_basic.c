#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "include/c_hash_map.h"

int main() {
    printf("=== Basic Hash Map Example ===\n\n");
    
    // Create a hash map with capacity 10
    HashMap *map = create_hash_map(10);
    if (!map) {
        printf("Failed to create hash map!\n");
        return 1;
    }
    
    printf("Created hash map with capacity: %d\n\n", map->capacity);
    
    // Insert some key-value pairs
    printf("Inserting key-value pairs:\n");
    printf("---------------------------\n");
    
    const char *test_data[][2] = {
        {"name", "John Doe"},
        {"age", "30"},
        {"city", "New York"},
        {"occupation", "Software Engineer"},
        {"email", "john@example.com"}
    };
    
    for (int i = 0; i < 5; i++) {
        const char *key = test_data[i][0];
        const char *value = test_data[i][1];
        
        int result = hash_map_insert(map, key, value);
        if (result >= 0) {
            printf("Inserted: %s -> %s\n", key, value);
        } else {
            printf("Failed to insert: %s\n", key);
        }
    }
    
    // Retrieve values
    printf("\nRetrieving values:\n");
    printf("-------------------\n");
    
    for (int i = 0; i < 5; i++) {
        const char *key = test_data[i][0];
        char *value = hash_map_get(map, key);
        
        if (value) {
            printf("Found: %s -> %s\n", key, value);
        } else {
            printf("Not found: %s\n", key);
        }
    }
    
    // Test updating a value
    printf("\nUpdating value for 'city':\n");
    printf("---------------------------\n");
    hash_map_insert(map, "city", "San Francisco");
    printf("Updated city to: %s\n", hash_map_get(map, "city"));
    
    // Test non-existent key
    printf("\nTesting non-existent key:\n");
    printf("--------------------------\n");
    char *not_found = hash_map_get(map, "nonexistent");
    if (not_found == NULL) {
        printf("Key 'nonexistent' not found (correct!)\n");
    }
    
    // Delete a key
    printf("\nDeleting key 'age':\n");
    printf("--------------------\n");
    int delete_result = hash_map_delete(map, "age");
    if (delete_result == 1) {
        printf("Successfully deleted 'age'\n");
    }
    
    // Verify deletion
    char *deleted_value = hash_map_get(map, "age");
    if (deleted_value == NULL) {
        printf("Verified: 'age' is no longer in the map\n");
    }
    
    // Clean up
    destroy_hash_map(map);
    printf("\nExample completed successfully!\n");
    
    return 0;
}