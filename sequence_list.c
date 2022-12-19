#include "sequence_list.h"

static bool wrong_insert_index(SequenceList *s, int k) {
    bool wrong = k < 0 || k > s->last + 1;
    if (wrong) {
        printf("Wrong insert index!\n");
    }
    return wrong;
}

static bool wrong_remove_index(SequenceList *s, int k) {
    bool wrong = k < 0 || k > s->last;
    if (wrong) {
        printf("Wrong remove index!\n");
    }
    return wrong;
}

bool empty_sequence_list(SequenceList *s) {
    bool empty = s->last == -1;
    if (empty) {
        printf("Empty sequence list!\n");
    }
    return empty;
}

bool full_sequence_list(SequenceList *s) {
    bool full = s->last + 1 == SEQUENCE_LIST_CAPACITY;
    if (full) {
        printf("Full sequence list!\n");
    }
    return full;
}

SequenceList *create_sequence_list() {
    SequenceList *s = malloc(sizeof(SequenceList));
    if (s) {
        s->last = -1;
    }
    return s;
}

void destroy_sequence_list(SequenceList *s) { free(s); }

bool insert_sequence_list(SequenceList *s, int k, DataType d) {
    if (full_sequence_list(s) || wrong_insert_index(s, k)) {
        return false;
    }
    for (int i = s->last; i >= k; --i) {
        s->data[i + 1] = s->data[i];
    }
    s->data[k] = d;
    ++s->last;
    return true;
}

bool remove_sequence_list(SequenceList *s, int k, DataType *p) {
    if (wrong_remove_index(s, k)) {
        return false;
    }
    if (p) {
        *p = s->data[k];
    }
    for (int i = k; i < s->last; ++i) {
        s->data[i] = s->data[i + 1];
    }
    --s->last;
    return true;
}

bool append_sequence_list(SequenceList *s, DataType d) {
    return insert_sequence_list(s, s->last + 1, d);
}

int search_sequence_list(SequenceList *s, DataType d, EqualType e) {
    int k = 0;
    for (; k <= s->last && !e(s->data[k], d); ++k)
        ;
    return s->last < k ? -1 : k;
}

int search_sequence_list_reversly(SequenceList *s, DataType d, EqualType e) {
    int k = s->last;
    for (; k >= 0 && !e(s->data[k], d); --k)
        ;
    return k;
}

static void print(SequenceList *s) {
    if (!s) {
        return;
    }
    printf("(");
    for (int i = 0; i <= s->last; ++i) {
        printf("%d, ", DATAVALUE(int, s->data[i]));
    }
    printf(")\n");
}

void demo_sequence_list() {
    SequenceList *s = create_sequence_list();
    print(s);

    int array[] = {1, 2, 3, 4, 5, 6};

    append_sequence_list(s, array + 0);
    append_sequence_list(s, array + 1);
    append_sequence_list(s, array + 2);
    append_sequence_list(s, array + 3);
    print(s);

    printf("Index of 1: %d\n", search_sequence_list(s, array + 0, equal_ints));
    printf("Index of 2: %d\n", search_sequence_list(s, array + 1, equal_ints));
    printf("Index of 3: %d\n", search_sequence_list(s, array + 2, equal_ints));
    printf("Index of 4: %d\n", search_sequence_list(s, array + 3, equal_ints));
    printf("Index of 5: %d\n", search_sequence_list(s, array + 4, equal_ints));

    printf("Index of 1: %d\n", search_sequence_list_reversly(s, array + 0, equal_ints));
    printf("Index of 2: %d\n", search_sequence_list_reversly(s, array + 1, equal_ints));
    printf("Index of 3: %d\n", search_sequence_list_reversly(s, array + 2, equal_ints));
    printf("Index of 4: %d\n", search_sequence_list_reversly(s, array + 3, equal_ints));
    printf("Index of 5: %d\n", search_sequence_list_reversly(s, array + 4, equal_ints));

    DataType d;
    remove_sequence_list(s, 3, &d);
    printf("removed: %d\n", DATAVALUE(int, d));
    print(s);
    remove_sequence_list(s, 3, &d);
    printf("removed: %d\n", DATAVALUE(int, d));
    print(s);

    SequenceList *sa = create_sequence_list();
    SequenceList *sb = create_sequence_list();

    append_sequence_list(sa, array + 0);
    append_sequence_list(sa, array + 2);
    append_sequence_list(sa, array + 4);
    append_sequence_list(sa, array + 5);
    printf("sa: ");
    print(sa);
    append_sequence_list(sb, array + 1);
    append_sequence_list(sb, array + 3);
    append_sequence_list(sb, array + 5);
    printf("sb: ");
    print(sb);

    SequenceList *sc = merge_sequence_lists(sa, sb);
    printf("sc: ");
    print(sc);

    SequenceList *sd = merge_sequence_lists_descendingly(sa, sb);
    printf("sd: ");
    print(sd);

    destroy_sequence_list(sb);
    destroy_sequence_list(sa);

    destroy_sequence_list(s);
}

SequenceList *merge_sequence_lists(SequenceList *sa, SequenceList *sb) {
    SequenceList *s = create_sequence_list();
    int ka = 0, kb = 0, k = 0;
    for (; ka <= sa->last && kb <= sb->last && !full_sequence_list(s); ++k) {
        DataType d =
            sa->data[ka] < sb->data[kb] ? sa->data[ka++] : sb->data[kb++];
        insert_sequence_list(s, k, d);
    }
    for (; ka <= sa->last && !full_sequence_list(s); ++k) {
        insert_sequence_list(s, k, sa->data[ka++]);
    }
    for (; kb <= sb->last && !full_sequence_list(s); ++k) {
        insert_sequence_list(s, k, sb->data[kb++]);
    }
    return s;
}

SequenceList *merge_sequence_lists_descendingly(SequenceList *sa,
                                                SequenceList *sb) {
    SequenceList *s = create_sequence_list();
    int ka = sa->last, kb = sb->last, k = 0;
    for (; ka >= 0 && kb >= 0 && !full_sequence_list(s); ++k) {
        DataType d =
            sa->data[ka] < sb->data[kb] ? sb->data[kb--] : sa->data[ka--];
        insert_sequence_list(s, k, d);
    }
    for (; ka >= 0 && !full_sequence_list(s); ++k) {
        insert_sequence_list(s, k, sa->data[ka--]);
    }
    for (; kb >= 0 && !full_sequence_list(s); ++k) {
        insert_sequence_list(s, k, sb->data[kb--]);
    }
    return s;
}