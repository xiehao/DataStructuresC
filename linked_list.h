#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "common.h"

typedef struct LinkedNode {
    DataType data;
    struct LinkedNode *next;
} LinkedNode;

typedef struct {
    LinkedNode *head;
} LinkedList;

extern LinkedList *create_linked_list();
extern bool cleanup_linked_list(LinkedList *s);
extern void destroy_linked_list(LinkedList *s);

extern LinkedNode *search_linked_by_index(LinkedList *s, int k);
extern LinkedNode *search_linked_by_data(LinkedList *s, DataType d);
extern bool insert_before_linked_by_index(LinkedList *s, int k, DataType d);
extern bool insert_after_linked_by_index(LinkedList *s, int k, DataType d);
extern bool remove_linked_by_index(LinkedList *s, int k, DataType *p);

extern bool add_front_linked_list(LinkedList *s, DataType d);
extern bool remove_front_linked_list(LinkedList *s, DataType *p);

extern int get_linked_list_length(LinkedList *s);

extern void demo_linked_list();

#endif // LINKED_LIST_H