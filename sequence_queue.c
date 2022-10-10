#include "sequence_queue.h"

SequenceQueue *create_sequence_queue() {
    SequenceQueue *s = malloc(sizeof(SequenceQueue));
    if (s) {
        s->front = s->rear = SEQUENCE_QUEUE_CAPACITY - 1;
        s->size = 0;
    }
    return s;
}

void destroy_sequence_queue(SequenceQueue *s) { free(s); }

bool empty_sequence_queue(SequenceQueue *s) { return !s || !s->size; }

bool full_sequence_queue(SequenceQueue *s) {
    return s && s->size == SEQUENCE_QUEUE_CAPACITY;
}

bool push_sequence_queue(SequenceQueue *s, DataType d) {
    if (full_sequence_queue(s)) {
        return false;
    }
    s->rear = (s->rear + 1) % SEQUENCE_QUEUE_CAPACITY;
    s->data[s->rear] = d;
    ++s->size;
    return true;
}

bool pop_sequence_queue(SequenceQueue *s, DataType *d) {
    if (empty_sequence_queue(s)) {
        return false;
    }
    s->front = (s->front + 1) % SEQUENCE_QUEUE_CAPACITY;
    if (d) {
        *d = s->data[s->front];
    }
    --s->size;
    return true;
}

static void print(SequenceQueue *s) {
    assert(s);
    printf("[");
#if 0
    if (s->front < s->rear) {
        for (int i = s->front + 1; i <= s->rear; ++i) {
            printf("%d, ", DATAVALUE(int, s->data[i]));
        }
    } else if (!empty_sequence_queue(s)) {
        for (int i = s->front + 1; i < SEQUENCE_QUEUE_CAPACITY; ++i) {
            printf("%d, ", DATAVALUE(int, s->data[i]));
        }
        for (int i = 0; i <= s->rear; ++i) {
            printf("%d, ", DATAVALUE(int, s->data[i]));
        }
    }
#else
    if (!empty_sequence_queue(s)) {
        int rear =
            s->front < s->rear ? s->rear : s->rear + SEQUENCE_QUEUE_CAPACITY;
        for (int i = s->front + 1; i <= rear; ++i) {
            printf("%d, ",
                   DATAVALUE(int, s->data[i % SEQUENCE_QUEUE_CAPACITY]));
        }
    }
#endif
    printf("]\n");
}

static bool equals_int(DataType lhs, DataType rhs) {
    return DATAVALUE(int, lhs) == DATAVALUE(int, rhs);
}

void demo_sequence_queue() {
    equals = equals_int;
    SequenceQueue *s = create_sequence_queue();
    print(s);
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 9; ++i) {
        push_sequence_queue(s, array + i);
        print(s);
    }
    for (int i = 0; i < 9; ++i) {
        pop_sequence_queue(s, NULL);
        print(s);
    }
    destroy_sequence_queue(s);
}