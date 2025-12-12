#include "include/c_vector.h"
#include "c_vector.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Function: create_vector
 * -----------------------
 * Allocates and initializes a new vector with the given capacity.
 *
 * capacity: initial capacity of the vector
 *
 * returns: pointer to the created Vector, or NULL if allocation fails or capacity is invalid
 */
Vector *create_vector(int capacity){
    if (capacity <= 0) return NULL;

    Vector *vector = malloc(sizeof(Vector));
    if (vector == NULL) return NULL;

    vector->collection = malloc(sizeof(int) * capacity);
    if (vector->collection == NULL){
        free(vector);
        return NULL;
    }

    vector->capacity = capacity;  // Set initial capacity
    vector->size = 0;             // Initialize size to 0
    return vector;
}

/*
 * Function: destroy_vector
 * ------------------------
 * Frees memory allocated for the vector and its elements.
 *
 * vector: pointer to the Vector to destroy
 *
 * returns: void
 */
void destroy_vector(Vector *vector){
    if (vector == NULL) return;
    free(vector->collection);
    free(vector);
}

/*
 * Function: current_size
 * ----------------------
 * Returns the current number of elements in the vector.
 *
 * vector: pointer to the Vector
 *
 * returns: size of the vector, or -1 if vector is NULL
 */
int current_size(Vector *vector){
    if (vector == NULL) return -1;
    return vector->size;
}

/*
 * Function: current_capacity
 * --------------------------
 * Returns the total capacity of the vector.
 *
 * vector: pointer to the Vector
 *
 * returns: capacity of the vector, or -1 if vector is NULL
 */
int current_capacity(Vector *vector){
    if (vector == NULL) return -1;
    return vector->capacity;
}

/*
 * Function: isFull
 * ----------------
 * Checks whether the vector has reached its capacity.
 *
 * vector: pointer to the Vector
 *
 * returns: 1 if full, 0 otherwise
 */
int isFull(Vector *vector){
    return (vector->size == vector->capacity) ? 1 : 0;
}

/*
 * Function: add_at_end
 * --------------------
 * Adds a value to the end of the vector, resizing if necessary.
 *
 * vector: pointer to the Vector
 * value: integer value to add
 *
 * returns: 1 if successful, -1 if error occurs
 */
int add_at_end(Vector *vector, int value){
    if (vector == NULL) return -1;

    if (isFull(vector)){
        if (resize_auto(&vector) == -1) return -1;
    }
    
    vector->collection[vector->size] = value;
    vector->size++;
    return 1;
}

/*
 * Function: remove_at_end
 * -----------------------
 * Removes and returns the last element in the vector.
 *
 * vector: pointer to the Vector
 *
 * returns: value of removed element, or -1 if vector is NULL or empty
 */
int remove_at_end(Vector *vector){
    if (vector == NULL || vector->size == 0) return -1;

    int removed_value = vector->collection[vector->size - 1];
    vector->size--;
    return removed_value;
}

/*
 * Function: resize_auto
 * ---------------------
 * Doubles the capacity of the vector when it becomes full.
 *
 * vector: pointer to a pointer to the Vector
 *
 * returns: 1 if successful, -1 if memory allocation fails
 */
int resize_auto(Vector **vector){
    if (vector == NULL || *vector == NULL) return -1;
    
    int new_capacity = (*vector)->capacity * 2;
    int *new_collection = realloc((*vector)->collection, sizeof(int) * new_capacity);
    
    if (new_collection == NULL) return -1;
    
    (*vector)->collection = new_collection;
    (*vector)->capacity = new_capacity;
    return 1;
}

/*
 * Function: get_value_at_index
 * ----------------------------
 * Returns the value at a specific index in the vector.
 *
 * vector: pointer to the Vector
 * index: position to access
 *
 * returns: value at the index, or -1 if invalid index or empty vector
 */
int get_value_at_index(Vector *vector, int index){
    if (vector == NULL || vector->size == 0) return -1;

    if (index < 0 || index >= vector->size) return -1;

    return vector->collection[index];
}

/*
 * Function: set_at_index
 * ----------------------
 * Inserts or updates a value at a specific index in the vector.
 * If index exceeds current size, fills intermediate positions with 0.
 * Resizes vector automatically if necessary.
 *
 * vector: pointer to the Vector
 * index: position to insert/update
 * value: integer value to set
 *
 * returns: pointer to the updated vector, or NULL if allocation fails
 */
Vector *set_at_index(Vector *vector, int index, int value){
    if (vector == NULL || index < 0) return NULL;

    // Resize vector until it can hold the target index
    while (index >= vector->capacity) {
        if (resize_auto(&vector) == -1) return NULL;
    }

    if (index < vector->size) {
        // Shift elements to the right to make room
        for (int i = vector->size; i > index; i--) {
            vector->collection[i] = vector->collection[i - 1];
        }
        vector->collection[index] = value;
        vector->size++;
    } 
    else {
        // Fill any gaps with 0 if index is beyond current size
        for (int i = vector->size; i < index; i++) {
            vector->collection[i] = 0;
        }
        vector->collection[index] = value;
        vector->size = index + 1;
    }

    return vector;
}
