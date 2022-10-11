#include "linked_queue.h"

LinkedQueue *create_linked_queue() {
    LinkedQueue *s = malloc(sizeof(LinkedQueue));
    if (s) {
        s->_ = create_linked_list();
        s->front = s->rear = s->_->head;
    }
    return s;
}

void destroy_linked_queue(LinkedQueue *s) {
    if (s) {
        destroy_linked_list(s->_);
        free(s);
    }
}

bool push_linked_queue(LinkedQueue *s, DataType d) {
    if (!s) {
        return false;
    }
    LinkedNode *n = create_linked_node(d);
    return n && (s->rear = attach_after_node(s->rear, n));
}

bool pop_linked_queue(LinkedQueue *s, DataType *d) {
    if (!s || !s->front->next) {
        return false;
    }
    LinkedNode *p = detach_after_node(s->front);
    if (d) {
        *d = p->data;
    }
    free(p);
    if (!s->front->next) {
        s->rear = s->front;
    }
    return true;
}

static void print(LinkedQueue *s) {
    if (!s) {
        return;
    }
    printf("[");
    for (LinkedNode *p = s->front; p != s->rear; p = p->next) {
        if (p->next) {
            printf("%d, ", DATAVALUE(int, p->next->data));
        }
    }
    printf("]\n");
}

static bool equals_int(DataType lhs, DataType rhs) {
    return DATAVALUE(int, lhs) == DATAVALUE(int, rhs);
}

void demo_linked_queue() {
    equals = equals_int;
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    LinkedQueue *s = create_linked_queue();
    print(s);
    for (int i = 0; i < 9; ++i) {
        push_linked_queue(s, array + i);
        print(s);
    }
    DataType d;
    for (int i = 0; i < 9; ++i) {
        pop_linked_queue(s, &d);
        printf("Popped: %d, ", DATAVALUE(int, d));
        print(s);
    }
    destroy_linked_queue(s);
}