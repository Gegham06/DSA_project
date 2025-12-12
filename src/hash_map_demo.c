#include "c_hash_map.h"
#include <stdio.h>

int main() {
    // Create a hash map with 5 buckets
    HashMap *map = create_hash_map(5);

    printf("=== Inserting keys ===\n");
    hash_map_insert(map, "apple", "10");
    hash_map_insert(map, "banana", "20");
    hash_map_insert(map, "grape", "30");
    hash_map_insert(map, "peach", "40"); // example collision
    hash_map_insert(map, "plum",  "50"); // example collision
    printf("Keys inserted successfully.\n\n");

    printf("=== Retrieving keys ===\n");
    printf("apple: %s\n", hash_map_get(map, "apple"));
    printf("banana: %s\n", hash_map_get(map, "banana"));
    printf("grape: %s\n", hash_map_get(map, "grape"));
    printf("peach: %s\n", hash_map_get(map, "peach"));
    printf("plum:  %s\n\n", hash_map_get(map, "plum"));

    printf("=== Collision handling example ===\n");
    printf("peach: %s, plum: %s\n", hash_map_get(map, "peach"), hash_map_get(map, "plum"));

    // Delete a key and show result
    hash_map_delete(map, "banana");
    printf("\nAfter deleting 'banana':\n");
    printf("banana: %s\n", hash_map_get(map, "banana"));

    // Destroy the map to free memory
    destroy_hash_map(map);

    return 0;
}
