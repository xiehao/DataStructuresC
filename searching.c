#include "searching.h"

int linear_search(Vector *v, DataType d, EqualType e) {
    int k = size_of_vector(v) - 1;
    for (; k >= 0 && !e(*vector_at(v, k), d); --k)
        ;
    return k;
}

static int binary_search_core(Vector *v, int f, int t, DataType d,
                              CompareType c) {
    if (f > t) {
        return -1;
    }
    int middle = (f + t) >> 1;
    int compare = c(d, *vector_at(v, middle));
    if (compare < 0) {
        return binary_search_core(v, f, middle - 1, d, c);
    } else if (compare > 0) {
        return binary_search_core(v, middle + 1, t, d, c);
    } else {
        return middle;
    }
}

int binary_search(Vector *v, DataType d, CompareType c) {
    return binary_search_core(v, 0, size_of_vector(v) - 1, d, c);
}

static Vector *create_vector_from_array(int a[], int n) {
    Vector *vector = create_vector(n);
    if (vector) {
        for (int i = 0; i < n; ++i) {
            push_back_vector(vector, a + i);
        }
    }
    return vector;
}

void demo_searching() {
    int data[] = {7, 14, 18, 21, 23, 29, 31, 35, 38, 42, 46, 49, 52};
    int query = 52;
    Vector *v = create_vector_from_array(data, sizeof(data) / sizeof(data[0]));
    int result = linear_search(v, &query, equal_ints);
    printf("The index of %d is: %d\n", query, result);
    result = binary_search(v, &query, compare_ints);
    printf("The index of %d is: %d\n", query, result);
    destroy_vector(v);
}