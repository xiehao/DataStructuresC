#include "sequence_stack.h"

SequenceStack *create_sequence_stack() {
    SequenceStack *s = malloc(sizeof(SequenceStack));
    if (s) {
        s->_ = create_sequence_list();
    }
    return s;
}

void destroy_sequence_stack(SequenceStack *s) {
    if (!s) {
        return;
    }
    destroy_sequence_list(s->_);
    free(s);
}

bool empty_sequence_stack(SequenceStack *s) {
    return !s || empty_sequence_list(s->_);
}

bool push_sequence_stack(SequenceStack *s, DataType d) {
    return s && insert_sequence_list(s->_, s->_->last + 1, d);
}

bool pop_sequence_stack(SequenceStack *s, DataType *p) {
    return s && remove_sequence_list(s->_, s->_->last, p);
}

bool top_sequence_stack(SequenceStack *s, DataType *p) {
    if (empty_sequence_stack(s) || !p) {
        return false;
    }
    *p = s->_->data[s->_->last];
    return true;
}

static void print(SequenceStack *s) {
    if (!s) {
        return;
    }
    printf("(");
    for (int i = 0; i <= s->_->last; ++i) {
        printf("%d, ", DATAVALUE(int, s->_->data[i]));
    }
    printf(")\n");
}

static bool equals_int(DataType lhs, DataType rhs) {
    return DATAVALUE(int, lhs) == DATAVALUE(int, rhs);
}

void demo_sequence_stack() {
    equals = equals_int;
    int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    SequenceStack *s = create_sequence_stack();
    print(s);
    DataType d;
    for (int i = 0; i < 10; ++i) {
        push_sequence_stack(s, array + i);
        print(s);
        top_sequence_stack(s, &d);
        printf("top: %d\n", DATAVALUE(int, d));
    }
    for (int i = 0; i < 10; ++i) {
        pop_sequence_stack(s, &d);
        print(s);
        printf("pop: %d\n", DATAVALUE(int, d));
    }
    destroy_sequence_stack(s);
}