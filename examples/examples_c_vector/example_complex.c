#include <stdio.h>
#include "include/c_vector.h"

int main() {
    printf("=== Complex Vector Operations ===\n");
    
    Vector *vec = create_vector(5);
    if (!vec) {
        printf("Failed to create vector!\n");
        return 1;
    }
    
    // Test 1: Mixed operations
    printf("Test 1: Mixed add/remove operations\n");
    for (int i = 0; i < 8; i++) {
        add_at_end(vec, i * 5);
        if (i % 3 == 2) {  // Remove every 3rd addition
            int removed = remove_at_end(vec);
            printf("Added %d, Removed %d - Size: %d\n", 
                   i * 5, removed, current_size(vec));
        }
    }
    
    // Test 2: Set operations
    printf("\nTest 2: Set operations\n");
    printf("Before set: ");
    for (int i = 0; i < current_size(vec); i++) {
        printf("%d ", get_value_at_index(vec, i));
    }
    printf("\n");
    
    // Modify some values
    set_at_index(vec, 1, 999);
    set_at_index(vec, 3, 888);
    
    printf("After set:  ");
    for (int i = 0; i < current_size(vec); i++) {
        printf("%d ", get_value_at_index(vec, i));
    }
    printf("\n");
    
    // Test 3: Edge cases
    printf("\nTest 3: Edge cases\n");
    printf("Getting out-of-bounds index: %d\n", get_value_at_index(vec, 100));
    printf("Setting out-of-bounds index: %d\n", set_at_index(vec, 100, 123));
    
    // Test 4: Empty vector operations
    printf("\nTest 4: Emptying vector\n");
    while (current_size(vec) > 0) {
        remove_at_end(vec);
    }
    printf("Empty vector size: %d\n", current_size(vec));
    printf("Remove from empty: %d\n", remove_at_end(vec));
    
    destroy_vector(vec);
    printf("\nComplex example completed!\n");
    return 0;
}