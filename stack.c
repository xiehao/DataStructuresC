#include "stack.h"

struct _stack {
    Vector *_;
};

Stack *create_stack() {
    Stack *s = malloc(sizeof(Stack));
    if (s) {
        s->_ = create_vector(1);
    }
    return s;
}

void destroy_stack(Stack *s) {
    if (s) {
        destroy_vector(s->_);
    }
    free(s);
}

bool push_stack(Stack *s, DataType d) {
    if (!s) {
        return false;
    }
    return push_back_vector(s->_, d);
}

bool pop_stack(Stack *s, DataType *d) {
    if (!s) {
        return false;
    }
    return pop_back_vector(s->_, d);
}

bool top_stack(Stack *s, DataType *d) {
    if (!s) {
        return false;
    }
    return get_vector_value_at(s->_, size_of_vector(s->_) - 1, d);
}

Stack *make_stack_empty(Stack *s) {
    if (s) {
        make_vector_empty(s->_);
    }
    return s;
}

bool is_stack_empty(Stack *s) { return !s || is_vector_empty(s->_); }

void demo_stack() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Stack *s = create_stack();
    for (int i = 0; i < 10; ++i) {
        push_stack(s, array + i);
    }
    DataType d;
    printf("(");
    while (!is_stack_empty(s)) {
        if (pop_stack(s, &d)) {
            printf("%d, ", DATAVALUE(int, d));
        }
    }
    printf(")\n");
    destroy_stack(s);
}