#ifndef STACK_H
#define STACK_H

#include "vector.h"

typedef struct _stack Stack;

extern Stack *create_stack();

extern void destroy_stack(Stack *s);

extern bool push_stack(Stack *s, DataType d);

extern bool pop_stack(Stack *s, DataType *d);

extern ValidDataType top_stack(Stack *s);

extern Stack *make_stack_empty(Stack *s);

extern bool is_stack_empty(Stack *s);

extern void demo_stack();

#endif // STACK_H