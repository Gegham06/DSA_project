#include <stdio.h>
#include "include/c_vector.h"

int main() {
    printf("=== Vector Resize Example ===\n");
    
    // Create a small vector to demonstrate resizing
    Vector *vec = create_vector(2);
    if (!vec) {
        printf("Failed to create vector!\n");
        return 1;
    }
    
    printf("Initial - Capacity: %d, Size: %d\n", 
           current_capacity(vec), current_size(vec));
    
    // Fill the vector to trigger resize
    printf("\nFilling vector to trigger resize...\n");
    for (int i = 1; i <= 10; i++) {
        add_at_end(vec, i);
        printf("Added %d - Capacity: %d, Size: %d\n", 
               i, current_capacity(vec), current_size(vec));
        
        // Verify the data is correct
        if (get_value_at_index(vec, i-1) != i) {
            printf("ERROR: Data corruption at index %d!\n", i-1);
        }
    }
    
    printf("\nFinal state - Capacity: %d, Size: %d\n", 
           current_capacity(vec), current_size(vec));
    
    // Verify all data
    printf("\nVerifying all data...\n");
    for (int i = 0; i < current_size(vec); i++) {
        int value = get_value_at_index(vec, i);
        printf("vec[%d] = %d %s\n", i, value, 
               (value == i+1) ? "✓" : "✗ ERROR");
    }
    
    destroy_vector(vec);
    printf("\nResize example completed!\n");
    return 0;
}