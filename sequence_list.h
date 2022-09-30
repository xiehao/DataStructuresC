#ifndef SEQUENCE_LIST_H
#define SEQUENCE_LIST_H

#include "common.h"

#define SEQUENCE_LIST_CAPACITY 256
// static const int SEQUENCE_LIST_CAPACITY = 256;

typedef struct {
    DataType data[SEQUENCE_LIST_CAPACITY];
    int last;
} SequenceList;

extern SequenceList *create_sequence_list();
extern void destroy_sequence_list(SequenceList *s);

extern bool insert_sequence_list(SequenceList *s, int k, DataType d);
extern bool remove_sequence_list(SequenceList *s, int k, DataType *p);

extern int search_sequence_list(SequenceList *s, DataType d);
extern int search_sequence_list_reversely(SequenceList *s, DataType d);

extern bool append_sequence_list(SequenceList *s, DataType d);

extern bool empty_sequence_list(SequenceList *s);
extern bool full_sequence_list(SequenceList *s);

extern void demo_sequence_list();

extern SequenceList *merge_sequence_lists(SequenceList *sa, SequenceList *sb);
extern SequenceList *merge_sequence_lists_descendingly(SequenceList *sa,
                                                       SequenceList *sb);

#endif // SEQUENCE_LIST_H