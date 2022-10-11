#include "linked_stack.h"

LinkedStack *create_linked_stack() {
    LinkedStack *s = malloc(sizeof(LinkedStack));
    if (s) {
        s->_ = create_linked_list();
    }
    return s;
}

void destroy_linked_stack(LinkedStack *s) {
    if (!s) {
        return;
    }
    destroy_linked_list(s->_);
    free(s);
}

bool empty_linked_stack(LinkedStack *s) { return !s || !s->_->head->next; }

bool top_linked_stack(LinkedStack *s, DataType *p) {
    if (empty_linked_stack(s) || !p) {
        return false;
    }
    *p = s->_->head->next->data;
    return true;
}

bool push_linked_stack(LinkedStack *s, DataType d) {
    return s && insert_after_linked_by_index(s->_, 0, d);
}

bool pop_linked_stack(LinkedStack *s, DataType *p) {
    return s && remove_linked_by_index(s->_, 1, p);
}

static void print(LinkedStack *s) {
    if (!s || !s->_) {
        return;
    }
    printf("(");
    LinkedNode *p = s->_->head->next;
    for (; p != NULL; p = p->next) {
        printf("%d, ", DATAVALUE(int, p->data));
    }
    printf(")\n");
}

static bool equals_int(DataType lhs, DataType rhs) {
    return DATAVALUE(int, lhs) == DATAVALUE(int, rhs);
}

void demo_linked_stack() {
    equals = equals_int;
    int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    LinkedStack *s = create_linked_stack();
    print(s);
    DataType d;
    for (int i = 0; i < 10; ++i) {
        push_linked_stack(s, array + i);
        print(s);
        top_linked_stack(s, &d);
        printf("top: %d\n", DATAVALUE(int, d));
    }
    for (int i = 0; i < 10; ++i) {
        pop_linked_stack(s, &d);
        print(s);
        printf("pop: %d\n", DATAVALUE(int, d));
    }
    destroy_linked_stack(s);
}