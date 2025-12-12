#include "vector/c_vector.h"
#include <stdio.h>
#include <stdlib.h>

Vector *create_vector(int capacity){
    if (capacity <= 0) return NULL;

    Vector *vector = malloc(sizeof(Vector));

    if (vector == NULL) return NULL;

    vector->collection = malloc(sizeof(int) * capacity);
    if (vector->collection == NULL){
        free(vector);
        return NULL;
    }

    vector->capacity = capacity;
    vector->size = 0;
    return vector;
}

void destroy_vector(Vector *vector){
    if (vector == NULL) return;
    free(vector->collection);
    free(vector);
    return;
}

int current_size(Vector *vector){
    if (vector == NULL) return -1;
    return vector->size;
}

int current_capacity(Vector *vector){
    if (vector == NULL) return -1;
    return vector->capacity;
}

int isFull(Vector *vector){
    return (vector->size == vector->capacity) ? 1 : 0;
}

int add_at_end(Vector *vector, int value){
    if (vector == NULL) return -1;

    if (isFull(vector)){
        if (resize_auto(&vector) == -1) return -1;
    }
    
    vector->collection[vector->size] = value;
    vector->size++;
    return 1;
}

int remove_at_end(Vector *vector){
    if (vector == NULL || vector->size == 0) return -1;

    int removed_value = vector->collection[vector->size - 1];
    vector->size--;
    return removed_value;
}

int resize_auto(Vector **vector){
    if (vector == NULL || *vector == NULL) return -1;
    
    int new_capacity = (*vector)->capacity * 2;
    int *new_collection = realloc((*vector)->collection, sizeof(int) * new_capacity);
    
    if (new_collection == NULL) return -1;
    
    (*vector)->collection = new_collection;
    (*vector)->capacity = new_capacity;
    return 1;
}

int get_value_at_index(Vector *vector, int index){
    if (vector == NULL || vector->size == 0) return -1;

    if (vector->size <= index || index < 0) return -1;

    return vector->collection[index];
}

Vector *set_at_index(Vector *vector, int index, int value){
    Vector *set_at_index(Vector *vector, int index, int value) {
    if (vector == NULL || index < 0) return NULL;

    while (index >= vector->capacity) {
        if (resize_auto(&vector) == -1) return NULL;
    }

    if (index < vector->size) {
        for (int i = vector->size; i > index; i--) { // shifts elements to the right
            vector->collection[i] = vector->collection[i - 1];
        }
        vector->collection[index] = value;
        vector->size++;
    } 
    else { // index >= vector->size, fill gaps with 0 if needed
        for (int i = vector->size; i < index; i++) {
            vector->collection[i] = 0;
        }
        vector->collection[index] = value;
        vector->size = index + 1;
    }

    return vector;
}

}