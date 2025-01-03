#include "vector.h"

#include <memory.h>

struct _vector {
    DataType *data;
    int size;
    int capacity;
};

static bool index_out_of_range(Vector *v, int k) {
    return k < 0 || k >= v->size;
}

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
    if (!v) return NULL;
    
    v->size = 0;
    v->capacity = c < 1 ? 1 : c;
    v->data = malloc(sizeof(DataType) * v->capacity);
    if (!v->data) {
        free(v);
        return NULL;
    }
    return v;
}

void destroy_vector(Vector *v) {
    if (v) {
        free(v->data);
    }
    free(v);
}

static bool reallocate_vector(Vector *v, int c) {
    assert(v && c > 0);
    DataType *new_data = realloc(v->data, sizeof(DataType) * c);
    if (!new_data) {
        return false;
    }
    v->data = new_data;
    v->capacity = c;
    return true;
}

static bool grow_vector(Vector *v) {
    return reallocate_vector(v, v->capacity << 1);
}

static bool shrink_vector(Vector *v) {
    if (!v || v->capacity <= 1) return false;
    
    int new_capacity = v->capacity / 2;
    if (new_capacity < 1) new_capacity = 1;
    
    return reallocate_vector(v, new_capacity);
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

ValidDataType remove_vector_by_index(Vector *v, int k) {
    if (wrong_remove_index(v, k)) {
        return (ValidDataType){.valid = false};
    }
    ValidDataType result = {.data = v->data[k], .valid = true};
    for (int i = k; i < v->size; ++i) {
        v->data[i] = v->data[i + 1];
    }
    if (--v->size * 4 < v->capacity) {
        shrink_vector(v);
    }
    return result;
}

bool push_back_vector(Vector *v, DataType d) {
    return insert_vector_by_index(v, v->size, d);
}

ValidDataType pop_back_vector(Vector *v) {
    return remove_vector_by_index(v, v->size - 1);
}

int search_vector(Vector *v, DataType d, EqualType e) {
    int k = v->size - 1;
    for (; k >= 0 && !e(v->data[k], d); --k)
        ;
    return k;
}

DataType *vector_at(Vector *v, int k) {
    assert(v);
    return index_out_of_range(v, k) ? NULL : v->data + k;
}

int size_of_vector(Vector *v) { return v->size; }

bool is_vector_empty(Vector *v) { return !v->size; }

Vector *make_vector_empty(Vector *v) {
    if (v && reallocate_vector(v, 1)) {
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
    remove_vector_by_index(v, 2);
    print(v);
    printf("Index of 3 is %d\n", search_vector(v, array + 3, equal_ints));
    printf("Index of 10 is %d\n", search_vector(v, array + 10, equal_ints));
    for (int i = 0; i < 10; ++i) {
        pop_back_vector(v);
        print(v);
    }
    destroy_vector(v);
}