#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "c_hash_map.h"

#define NUM_OPERATIONS 10000
#define KEY_LENGTH 10
#define VALUE_LENGTH 20

// Generate random string
char* random_string(int length) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char* str = malloc(length + 1);
    
    for (int i = 0; i < length; i++) {
        int key = rand() % (int)(sizeof(charset) - 1);
        str[i] = charset[key];
    }
    str[length] = '\0';
    
    return str;
}

int main() {
    printf("=== Hash Map Performance Test ===\n\n");
    
    srand(time(NULL));
    
    // Test different capacities
    int capacities[] = {10, 50, 100, 500, 1000};
    int num_capacities = sizeof(capacities) / sizeof(capacities[0]);
    
    for (int c = 0; c < num_capacities; c++) {
        int capacity = capacities[c];
        
        printf("\nTesting with capacity: %d\n", capacity);
        printf("===========================\n");
        
        clock_t start, end;
        double cpu_time_used;
        
        // Create hash map
        start = clock();
        HashMap *map = create_hash_map(capacity);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Create time: %.6f seconds\n", cpu_time_used);
        
        if (!map) {
            printf("Failed to create map!\n");
            continue;
        }
        
        // Insert performance
        start = clock();
        for (int i = 0; i < NUM_OPERATIONS; i++) {
            char* key = random_string(KEY_LENGTH);
            char* value = random_string(VALUE_LENGTH);
            
            hash_map_insert(map, key, value);
            
            free(key);
            free(value);
        }
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Insert %d items: %.6f seconds\n", NUM_OPERATIONS, cpu_time_used);
        printf("Average per insert: %.9f seconds\n", cpu_time_used / NUM_OPERATIONS);
        
        // Generate test keys for retrieval
        char** test_keys = malloc(NUM_OPERATIONS / 10 * sizeof(char*));
        for (int i = 0; i < NUM_OPERATIONS / 10; i++) {
            test_keys[i] = random_string(KEY_LENGTH);
        }
        
        // Retrieval performance
        int found_count = 0;
        start = clock();
        for (int i = 0; i < NUM_OPERATIONS / 10; i++) {
            char* value = hash_map_get(map, test_keys[i]);
            if (value != NULL) {
                found_count++;
            }
        }
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Retrieve %d items: %.6f seconds\n", NUM_OPERATIONS / 10, cpu_time_used);
        printf("Average per retrieve: %.9f seconds\n", cpu_time_used / (NUM_OPERATIONS / 10));
        printf("Hit rate: %.2f%%\n", (float)found_count / (NUM_OPERATIONS / 10) * 100);
        
        // Delete performance
        start = clock();
        for (int i = 0; i < NUM_OPERATIONS / 10; i++) {
            hash_map_delete(map, test_keys[i]);
        }
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Delete %d items: %.6f seconds\n", NUM_OPERATIONS / 10, cpu_time_used);
        printf("Average per delete: %.9f seconds\n", cpu_time_used / (NUM_OPERATIONS / 10));
        
        // Cleanup
        for (int i = 0; i < NUM_OPERATIONS / 10; i++) {
            free(test_keys[i]);
        }
        free(test_keys);
        
        destroy_hash_map(map);
    }
    
    printf("\nPerformance test completed!\n");
    printf("Note: Performance varies based on hash distribution and collision rate.\n");
    
    return 0;
}