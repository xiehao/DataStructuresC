#include "linked_list.h"

LinkedNode *create_linked_node(DataType data) {
    LinkedNode *n = malloc(sizeof(LinkedNode));
    n->data = data;
    n->next = NULL;
    return n;
}

LinkedList *create_linked_list() {
    LinkedList *s = malloc(sizeof(LinkedList));
    s->head = create_linked_node(0);
    return s;
}

LinkedNode *search_linked_by_index(LinkedList *s, int k) {
    LinkedNode *p = s->head;
    for (int i = 0; p != NULL && i < k; ++i, p = p->next)
        ;
    return p;
}

LinkedNode *search_linked_by_data(LinkedList *s, DataType d) {
    LinkedNode *p = s->head->next;
    for (; p != NULL && p->data != d; p = p->next)
        ;
    return p;
}

LinkedNode *insert_after_linked_node(LinkedNode *p, DataType d) {
    LinkedNode *n = create_linked_node(d);
    n->next = p->next;
    p->next = n;
    return n;
}

bool insert_after_linked_by_index(LinkedList *s, int k, DataType d) {
    LinkedNode *p = search_linked_by_index(s, k);
    if (!p) {
        printf("Wrong insert index!\n");
        return p;
    }
    return insert_after_linked_node(p, d);
}

bool insert_before_linked_by_index(LinkedList *s, int k, DataType d) {
    return insert_after_linked_by_index(s, k - 1, d);
}

void remove_after_linked_node(LinkedNode *q) {
    LinkedNode *p = q->next;
    q->next = p->next;
    free(p);
}

bool remove_linked_by_index(LinkedList *s, int k, DataType *p) {
    LinkedNode *q = search_linked_by_index(s, k - 1);
    if (!q || !q->next) {
        printf("Wrong remove index!\n");
        return false;
    }
    if (p) {
        *p = q->next->data;
    }
    remove_after_linked_node(q);
    return true;
}

bool add_front_linked_list(LinkedList *s, DataType d) {
    return insert_after_linked_by_index(s, 0, d);
}

bool remove_front_linked_list(LinkedList *s, DataType *p) {
    return remove_linked_by_index(s, 1, p);
}

bool cleanup_linked_list(LinkedList *s) {
    if (!s) {
        return false;
    }
    for (; s->head->next != NULL;) {
        if (remove_front_linked_list(s, NULL)) {
            return false;
        }
    }
    return true;
}

void destroy_linked_list(LinkedList *s) {
    if (!cleanup_linked_list(s)) {
        return;
    }
    free(s->head);
    free(s);
}

int get_linked_list_length(LinkedList *s) {
    int length = -1;
    for (LinkedNode *p = s->head; p != NULL; p = p->next, ++length)
        ;
    return length;
}

static void print(LinkedList *s) {
    if (!s) {
        return;
    }
    printf("(");
    LinkedNode *p = s->head->next;
    for (; p != NULL; p = p->next) {
        printf("%d, ", p->data);
    }
    printf(")\n");
}

void demo_linked_list() {
    LinkedList *s = create_linked_list();
    print(s);
    printf("length: %d\n", get_linked_list_length(s));

    add_front_linked_list(s, 1);
    printf("length: %d\n", get_linked_list_length(s));
    add_front_linked_list(s, 2);
    print(s);
    printf("length: %d\n", get_linked_list_length(s));

    printf("%p\n", search_linked_by_data(s, 1));
    printf("%p\n", search_linked_by_data(s, 2));
    printf("%p\n", search_linked_by_data(s, 3));

    insert_after_linked_by_index(s, 3, 3);
    printf("length: %d\n", get_linked_list_length(s));

    remove_front_linked_list(s, NULL);
    print(s);
    printf("length: %d\n", get_linked_list_length(s));
    remove_front_linked_list(s, NULL);
    print(s);
    printf("length: %d\n", get_linked_list_length(s));
    remove_front_linked_list(s, NULL);
    print(s);
    printf("length: %d\n", get_linked_list_length(s));

    cleanup_linked_list(s);
    print(s);

    destroy_linked_list(s);
}