#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "c_hash_map.h"

// Helper function to print bucket information
void print_bucket_stats(HashMap *map) {
    printf("\nBucket Statistics:\n");
    printf("------------------\n");
    
    int empty_buckets = 0;
    int max_chain_length = 0;
    int total_nodes = 0;
    
    for (int i = 0; i < map->capacity; i++) {
        int chain_length = 0;
        HashNode *node = map->buckets[i];
        
        while (node != NULL) {
            chain_length++;
            total_nodes++;
            node = node->next;
        }
        
        if (chain_length == 0) {
            empty_buckets++;
        }
        
        if (chain_length > max_chain_length) {
            max_chain_length = chain_length;
        }
    }
    
    printf("Capacity: %d\n", map->capacity);
    printf("Total entries: %d\n", total_nodes);
    printf("Empty buckets: %d\n", empty_buckets);
    printf("Load factor: %.2f\n", (float)total_nodes / map->capacity);
    printf("Max chain length: %d\n", max_chain_length);
}

int main() {
    printf("=== Hash Map Collisions Example ===\n\n");
    
    // Create a very small hash map to force collisions
    HashMap *map = create_hash_map(3);
    if (!map) {
        printf("Failed to create hash map!\n");
        return 1;
    }
    
    printf("Created hash map with small capacity: %d\n", map->capacity);
    
    // Insert keys that will likely collide
    printf("\nInserting keys (will cause collisions):\n");
    printf("----------------------------------------\n");
    
    const char *keys[] = {
        "apple", "banana", "cherry", "date", "elderberry",
        "fig", "grape", "honeydew", "kiwi", "lemon"
    };
    
    for (int i = 0; i < 10; i++) {
        char value[20];
        sprintf(value, "Fruit_%d", i + 1);
        
        int result = hash_map_insert(map, keys[i], value);
        printf("Inserted: %s -> %s (bucket: %lu)\n", 
               keys[i], value, hash_function(keys[i]) % map->capacity);
    }
    
    // Print statistics
    print_bucket_stats(map);
    
    // Verify all keys can be retrieved correctly
    printf("\nVerifying all keys can be retrieved:\n");
    printf("-------------------------------------\n");
    
    int all_found = 1;
    for (int i = 0; i < 10; i++) {
        char *value = hash_map_get(map, keys[i]);
        if (value) {
            printf("✓ Found: %s -> %s\n", keys[i], value);
        } else {
            printf("✗ Missing: %s\n", keys[i]);
            all_found = 0;
        }
    }
    
    if (all_found) {
        printf("\nAll keys retrieved successfully despite collisions!\n");
    }
    
    // Test chained deletion
    printf("\nTesting deletion in chained buckets:\n");
    printf("-------------------------------------\n");
    
    // Delete a middle item in a chain
    printf("Deleting 'date'...\n");
    hash_map_delete(map, "date");
    
    // Verify deletion
    if (hash_map_get(map, "date") == NULL) {
        printf("✓ 'date' successfully deleted\n");
    }
    
    // Verify neighbors still exist
    printf("Checking neighbors still exist...\n");
    if (hash_map_get(map, "cherry") && hash_map_get(map, "elderberry")) {
        printf("✓ Neighbors still accessible\n");
    }
    
    // Print final statistics
    printf("\nFinal statistics after deletion:\n");
    print_bucket_stats(map);
    
    destroy_hash_map(map);
    printf("\nCollisions example completed!\n");
    
    return 0;
}