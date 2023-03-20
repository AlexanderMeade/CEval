#ifndef VECTOR_H
#define VECTOR_H
    
typedef struct {
    size_t size;
    size_t item_size;
    void **items;
}Vector;

Vector *Vector_init(const size_t size_of_items);

void Vector_push(Vector *vector, void *item);

void *Vector_get(Vector *vector, size_t index);
#endif
