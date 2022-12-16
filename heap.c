#include "heap.h"

#include "vector.h"

struct _heap {
    Vector *_;
    CompareType compare;
};

static int i_parent(int k) { return (k - 1) >> 1; }

static int i_left(int k) { return (k << 1) + 1; }

static int i_right(int k) { return (k << 1) + 2; }

static DataType *at(Heap *h, int k) {
    assert(h);
    return vector_at(h->_, k);
}

static void print_heap(Heap *h) {
    printf("(");
    for (int i = 0; i < size_of_heap(h); ++i) {
        printf("%d, ", DATAVALUE(int, *at(h, i)));
    }
    printf(")\n");
}

static bool percolate_up(Heap *h, int k) {
    for (; k > 0 && h->compare(at(h, k), at(h, i_parent(k))) < 0;
         swap_data(at(h, k), at(h, i_parent(k))), k = i_parent(k))
        ;
    return true;
}

static bool percolate_down(Heap *h, int k) {
    int n = size_of_heap(h);
    for (;;) {
        DataType *p_left = at(h, i_left(k));
        if (!p_left) break;
        DataType *p = at(h, k);
        DataType *p_right = at(h, i_right(k));
        if (!p_right) {
            if (h->compare(p_left, p) < 0) swap_data(p, p_left);
            break;
        } else {
            DataType *smallest = smaller_of(
                p, smaller_of(p_left, p_right, h->compare), h->compare);
            if (smallest == p) break;
            swap_data(p, smallest == p_left ? p_left : p_right);
            k = smallest == p_left ? i_left(k) : i_right(k);
        }
    }
    return true;
}

Heap *create_heap(CompareType c) {
    Heap *h = malloc(sizeof(Heap));
    if (h) {
        h->_ = create_vector(4);
        h->compare = c;
    }
    return h;
}

Heap *create_heap_from_array(DataType d[], int n, CompareType c) {
    Heap *h = create_heap(c);
    if (h) {
        for (int i = 0; i < n; ++i) {
            push_heap(h, d[i]);
            print_heap(h);
        }
    }
    return h;
}

void destroy_heap(Heap *h) {
    if (h) {
        destroy_vector(h->_);
    }
    free(h);
}

int size_of_heap(Heap *h) {
    assert(h && h->_);
    return size_of_vector(h->_);
}

bool push_heap(Heap *h, DataType d) {
    push_back_vector(h->_, d);
    return percolate_up(h, size_of_vector(h->_) - 1);
}

ValidDataType pop_heap(Heap *h) {
    if (!at(h, 0)) return (ValidDataType){.valid = false};
    ValidDataType top = {.data = *at(h, 0), .valid = true};
    ValidDataType last = pop_back_vector(h->_);
    if (size_of_heap(h) > 0) {
        *at(h, 0) = last.data;
        percolate_down(h, 0);
    }
    return top;
}

ValidDataType top_heap(Heap *h) {
    DataType *p = at(h, 0);
    return p ? (ValidDataType){.data = *p, .valid = true}
             : (ValidDataType){.valid = false};
}

static int compare_ints(DataType *lhs, DataType *rhs) {
    int left = DATAVALUE(int, *lhs);
    int right = DATAVALUE(int, *rhs);
    return left < right ? -1 : (left > right ? 1 : 0);
}

void demo_heap() {
    int n = 6;
    int raw_data[] = {21, 25, 22, 10, 25, 18};
    DataType *data = malloc(sizeof(int *) * n);
    for (int i = 0; i < n; ++i) {
        data[i] = raw_data + i;
    }
    Heap *h = create_heap_from_array(data, n, compare_ints);
    for (int i = 0; i < n; ++i) {
        ValidDataType p = pop_heap(h);
        if (p.valid) {
            printf("popped: %d\n", DATAVALUE(int, p.data));
        }
    }
    free(data);
    destroy_heap(h);
}