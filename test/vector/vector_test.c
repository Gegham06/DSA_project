// test_vector.c
#include "vector/c_vector.h"
#include <stdio.h>

int main() {
    // Test create and basic functions
    Vector *vec = create_vector(2);
    printf("Size: %d, Capacity: %d\n", current_size(vec), current_capacity(vec));
    
    // Test add operations
    add_at_end(vec, 10);
    add_at_end(vec, 20);
    add_at_end(vec, 30);  // This should trigger resize
    
    printf("After adds - Size: %d, Capacity: %d\n", current_size(vec), current_capacity(vec));
    
    // Test get/set operations
    printf("Value at index 1: %d\n", get_value_at_index(vec, 1));
    set_at_index(vec, 1, 99);
    printf("After set - Value at index 1: %d\n", get_value_at_index(vec, 1));
    
    // Test remove
    printf("Removed: %d\n", remove_at_end(vec));
    printf("After remove - Size: %d\n", current_size(vec));
    
    destroy_vector(vec);
    return 0;
}