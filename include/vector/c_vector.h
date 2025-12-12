#ifndef C_VECTOR_H
#define C_VECTOR_H

typedef struct vector{
    int *collection;
    int capacity;
    int size;
}Vector;

Vector *create_vector(int capacity);
void destroy_vector(Vector *vector);
int current_size(Vector *vector);
int current_capacity(Vector *vector);
int isFull(Vector *vector);
int add_at_end(Vector *vector, int value);
int remove_at_end(Vector *vector);
int resize_auto(Vector **vector);
int get_value_at_index(Vector *vector, int index);
Vector *set_at_index(Vector *vector, int index, int value);


#endif