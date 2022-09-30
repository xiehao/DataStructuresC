#if !defined(VECTOR_H)
#define VECTOR_H

#include "common.h"

typedef struct {
    DataType *data;
    int size;
    int capacity;
} Vector;

extern Vector *create_vector();
extern void destroy_vector(Vector *v);

extern bool insert_vector(Vector *v, int k, DataType d);
extern bool remove_vector_by_index(Vector *v, int k);

extern bool push_back_vector(Vector *v, DataType d);
extern bool pop_back_vector(Vector *v);

extern int search_vector(Vector *v, DataType d);

extern void demo_vector();

#endif // VECTOR_H
