#include "c_vector.h"
#include <stdio.h>

int main() {
    printf("=== Vector Demo ===\n");

    // Create vector with initial capacity 2
    Vector *vec = create_vector(2);
    printf("Initial capacity: %d\n", current_capacity(vec));

    // push_back / add_at_end and automatic resizing
    printf("\n=== Adding elements ===\n");
    int values[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        add_at_end(vec, values[i]);
        printf("Added %d, size: %d, capacity: %d\n", values[i], current_size(vec), current_capacity(vec));
    }

    // get elements
    printf("\n=== Getting elements ===\n");
    for (int i = 0; i < current_size(vec); i++) {
        printf("vec[%d] = %d\n", i, get_value_at_index(vec, i));
    }

    // set elements
    printf("\n=== Setting elements ===\n");
    set_at_index(vec, 2, 99); // change 3rd element
    for (int i = 0; i < current_size(vec); i++) {
        printf("vec[%d] = %d\n", i, get_value_at_index(vec, i));
    }

    // optional: set a value at index beyond current size
    printf("\n=== Setting element beyond current size ===\n");
    set_at_index(vec, 7, 77);
    for (int i = 0; i < current_size(vec); i++) {
        printf("vec[%d] = %d\n", i, get_value_at_index(vec, i));
    }

    destroy_vector(vec);
    return 0;
}
