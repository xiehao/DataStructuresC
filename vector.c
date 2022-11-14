#include "vector.h"

#include <memory.h>

struct _vector {
    DataType *data;
    int size;
    int capacity;
};

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
    if (v) {
        free(v->data);
    }
    free(v);
}

static bool reallocate_vector(Vector *v, int c) {
    DataType *new_data = malloc(sizeof(DataType) * c);
    if (!new_data) {
        printf("Memory allocation failed when growing or shrinking vector!\n");
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

bool remove_vector_by_index(Vector *v, int k, DataType *d) {
    if (wrong_remove_index(v, k)) {
        return false;
    }
    if (d) {
        *d = v->data[k];
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

bool pop_back_vector(Vector *v, DataType *d) {
    return remove_vector_by_index(v, v->size - 1, d);
}

int search_vector(Vector *v, DataType d) {
    int k = v->size - 1;
    for (; k >= 0 && !equal(v->data[k], d); --k)
        ;
    return k;
}

bool get_vector_value_at(Vector *v, int k, DataType *d) {
    if (!v || !d) {
        printf("Null vector or data");
        return false;
    }
    if (k < 0 || k >= v->size) {
        printf("Index out of range!\n");
        return false;
    }
    *d = v->data[k];
    return true;
}

bool set_vector_value_at(Vector *v, int k, DataType d) {
    if (!v) {
        printf("Null vector or data");
        return false;
    }
    if (k < 0 || k >= v->size) {
        printf("Index out of range!\n");
        return false;
    }
    v->data[k] = d;
    return true;
}

int size_of_vector(Vector *v) { return v->size; }

bool is_vector_empty(Vector *v) { return !v->size; }

Vector *make_vector_empty(Vector *v) {
    if (v) {
        v->size = 0;
    }
    return v;
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

void demo_vector() {
    int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1};
    Vector *v = create_vector(1);
    print(v);
    for (int i = 0; i < 10; ++i) {
        push_back_vector(v, array + i);
        print(v);
    }
    insert_vector_by_index(v, -1, array + 10);
    print(v);
    remove_vector_by_index(v, 2, NULL);
    print(v);
    printf("Index of 3 is %d\n", search_vector(v, array + 3));
    printf("Index of 10 is %d\n", search_vector(v, array + 10));
    for (int i = 0; i < 10; ++i) {
        pop_back_vector(v, NULL);
        print(v);
    }
    destroy_vector(v);
}