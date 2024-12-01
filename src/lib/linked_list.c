#include "linked_list.h"

LinkedNode *create_linked_node(DataType d) {
    LinkedNode *n = malloc(sizeof(LinkedNode));
    if (n) {
        n->data = d;
        n->next = NULL;
    }
    return n;
}

LinkedList *create_linked_list() {
    LinkedList *s = malloc(sizeof(LinkedList));
    if (s) {
        s->head = create_linked_node(NULL);
    }
    return s;
}

LinkedNode *search_linked_by_index(LinkedList *s, int k) {
    LinkedNode *p = s->head;
    for (int i = 0; p != NULL && i < k; ++i, p = p->next)
        ;
    return p;
}

LinkedNode *search_linked_by_data(LinkedList *s, DataType d, EqualType e) {
    LinkedNode *p = s->head->next;
    for (; p != NULL && !e(p->data, d); p = p->next)
        ;
    return p;
}

LinkedNode *attach_after_node(LinkedNode *p, LinkedNode *n) {
    assert(p && n);
    n->next = p->next;
    p->next = n;
    return n;
}

bool insert_after_linked_by_index(LinkedList *s, int k, DataType d) {
    LinkedNode *p = search_linked_by_index(s, k);
    if (!p) {
        printf("Wrong insert index!\n");
        return false;
    }
    LinkedNode *n = create_linked_node(d);
    return n && attach_after_node(p, n);
}

bool insert_before_linked_by_index(LinkedList *s, int k, DataType d) {
    return insert_after_linked_by_index(s, k - 1, d);
}

LinkedNode *detach_after_node(LinkedNode *q) {
    assert(q && q->next);
    LinkedNode *p = q->next;
    q->next = p->next;
    return p;
}

bool remove_linked_by_index(LinkedList *s, int k, DataType *d) {
    LinkedNode *q = search_linked_by_index(s, k - 1);
    if (!q || !q->next) {
        printf("Wrong remove index!\n");
        return false;
    }
    LinkedNode *p = detach_after_node(q);
    if (d) {
        *d = p->data;
    }
    free(p);
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
        if (!remove_front_linked_list(s, NULL)) {
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
        printf("%d, ", DATAVALUE(int, p->data));
    }
    printf(")\n");
}

void demo_linked_list() {
    int array[] = {1, 2, 3, 4, 5};

    LinkedList *s = create_linked_list();
    print(s);
    printf("length: %d\n", get_linked_list_length(s));

    add_front_linked_list(s, array + 0);
    printf("length: %d\n", get_linked_list_length(s));
    add_front_linked_list(s, array + 1);
    print(s);
    printf("length: %d\n", get_linked_list_length(s));

    printf("%p\n", search_linked_by_data(s, array + 0, equal_ints));
    printf("%p\n", search_linked_by_data(s, array + 1, equal_ints));
    printf("%p\n", search_linked_by_data(s, array + 2, equal_ints));

    insert_after_linked_by_index(s, 3, array + 2);
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