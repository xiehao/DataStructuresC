#ifndef SEQUENCE_STACK
#define SEQUENCE_STACK

#include "sequence_list.h"

typedef struct {
    SequenceList *_;
} SequenceStack;

extern SequenceStack *create_sequence_stack();
extern void destroy_sequence_stack(SequenceStack *s);

extern bool empty_sequence_stack(SequenceStack *s);

extern bool push_sequence_stack(SequenceStack *s, DataType d);
extern bool pop_sequence_stack(SequenceStack *s, DataType *p);

extern bool top_sequence_stack(SequenceStack *s, DataType *p);

extern void demo_sequence_stack();

#endif // SEQUENCE_STACK