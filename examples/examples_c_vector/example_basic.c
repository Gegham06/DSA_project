#include <stdio.h>
#include "include/c_vector.h"

int main() {
    printf("=== Basic Vector Example ===\n");
    
    // Create a vector with capacity 3
    Vector *vec = create_vector(3);
    if (!vec) {
        printf("Failed to create vector!\n");
        return 1;
    }
    
    printf("Created vector - Capacity: %d, Size: %d\n", 
           current_capacity(vec), current_size(vec));
    
    // Add some elements
    printf("\nAdding elements...\n");
    for (int i = 1; i <= 5; i++) {
        if (add_at_end(vec, i * 10) == 1) {
            printf("Added %d - Capacity: %d, Size: %d\n", 
                   i * 10, current_capacity(vec), current_size(vec));
        } else {
            printf("Failed to add %d\n", i * 10);
        }
    }
    
    // Access elements
    printf("\nAccessing elements...\n");
    for (int i = 0; i < current_size(vec); i++) {
        printf("vec[%d] = %d\n", i, get_value_at_index(vec, i));
    }
    
    // Remove elements
    printf("\nRemoving elements from end...\n");
    while (current_size(vec) > 0) {
        int value = remove_at_end(vec);
        printf("Removed %d - Size: %d\n", value, current_size(vec));
    }
    
    destroy_vector(vec);
    printf("\nExample completed successfully!\n");
    return 0;
}