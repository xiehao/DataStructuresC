#include "vector.h"

#include <memory.h>

static bool wrong_insert_index(Vector *v, int k) {
    bool wrong = k < 0 || k > v->size;
    if (wrong) {
        printf("Wrong insert index!\n");
    }
    return wrong;
}

static bool wrong_remove_index(Vector *v, int k) {
    bool wrong = k < 0 || k >= v->size;
    if (wrong) {
        printf("Wrong remove index!\n");
    }
    return wrong;
}

Vector *create_vector(int c) {
    Vector *v = malloc(sizeof(Vector));
    v->data = malloc(sizeof(Vector) * c);
    v->size = 0;
    v->capacity = c < 1 ? 1 : c;
    return v;
}

void destroy_vector(Vector *v) {
    free(v->data);
    free(v);
}

static bool reallocate_vector(Vector *v, int c) {
    DataType *new_data = malloc(sizeof(DataType) * c);
    if (!new_data) {
        printf("Memory allocation failed when growing vector!\n");
        return false;
    }
    memcpy(new_data, v->data, sizeof(DataType) * v->size);
    free(v->data);
    v->data = new_data;
    v->capacity = c;
    return true;
}

static bool grow_vector(Vector *v) {
    return reallocate_vector(v, v->capacity << 1);
}

static bool shrink_vector(Vector *v) {
    return reallocate_vector(v, (v->capacity + 1) >> 1);
}

bool insert_vector_by_index(Vector *v, int k, DataType d) {
    if (wrong_insert_index(v, k) ||
        (v->size >= v->capacity && !grow_vector(v))) {
        return false;
    }
    for (int i = v->size; i > k; --i) {
        v->data[i] = v->data[i - 1];
    }
    v->data[k] = d;
    ++v->size;
    return true;
}

bool remove_vector(Vector *v, int k) {
    if (wrong_remove_index(v, k)) {
        return false;
    }
    for (int i = k; i < v->size; ++i) {
        v->data[i] = v->data[i + 1];
    }
    --v->size;
    return v->size * 4 > v->capacity || shrink_vector(v);
}

bool push_back_vector(Vector *v, DataType d) {
    return insert_vector_by_index(v, v->size, d);
}

bool pop_back_vector(Vector *v) { return remove_vector(v, v->size - 1); }

int search_vector(Vector *v, DataType d) {
    int k = v->size - 1;
    for (; k >= 0 && !equals(v->data[k], d); --k)
        ;
    return k;
}

static void print(Vector *v) {
    if (!v) {
        return;
    }
    printf("(");
    for (int i = 0; i < v->size; ++i) {
        printf("%d, ", DATAVALUE(int, v->data[i]));
    }
    printf(")\n");
    printf("size: %d, capacity: %d\n", v->size, v->capacity);
}

static bool equals_int(DataType lhs, DataType rhs) {
    return DATAVALUE(int, lhs) == DATAVALUE(int, rhs);
}

void demo_vector() {
    equals = equals_int;
    int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1};
    Vector *v = create_vector(1);
    print(v);
    for (int i = 0; i < 10; ++i) {
        push_back_vector(v, array + i);
        print(v);
    }
    insert_vector_by_index(v, -1, array + 10);
    print(v);
    remove_vector(v, 2);
    print(v);
    printf("Index of 3 is %d\n", search_vector(v, array + 3));
    printf("Index of 10 is %d\n", search_vector(v, array + 10));
    for (int i = 0; i < 10; ++i) {
        pop_back_vector(v);
        print(v);
    }
    destroy_vector(v);
}