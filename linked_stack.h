#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include "linked_list.h"

typedef struct {
    LinkedList *_;
} LinkedStack;

extern LinkedStack *create_linked_stack();
extern void destroy_linked_stack(LinkedStack *s);

extern bool empty_linked_stack(LinkedStack *s);
extern bool top_linked_stack(LinkedStack *s, DataType *p);

extern bool push_linked_stack(LinkedStack *s, DataType d);
extern bool pop_linked_stack(LinkedStack *s, DataType *p);

extern void demo_linked_stack();

#endif // LINKED_STACK_H