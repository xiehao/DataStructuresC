#include "sorting.h"

static void swap_elements(DataType *lhs, DataType *rhs) {
    DataType data = *lhs;
    *lhs = *rhs;
    *rhs = data;
}

static int compare_ints(DataType *lhs, DataType *rhs) {
    int left = DATAVALUE(int, *lhs);
    int right = DATAVALUE(int, *rhs);
    return left < right ? -1 : (left > right ? 1 : 0);
}

static void print_array(DataType *s, int n, int i) {
    printf("%d): ", i);
    for (int i = 0; i < n; ++i) {
        printf("%d, ", DATAVALUE(int, s[i]));
    }
    printf("\n");
}

/**
 * @brief Insert an element (with a target index) into a sorted sub-sequence
 * (from a first index to the index right before the target index)
 *
 * @param s the sequence
 * @param f the first index
 * @param t the target index
 * @param c the comparison function
 */
static void insert_element(DataType *s, int f, int t, CompareType c) {
    DataType element = s[t];
    int i = t;
    for (; i > f && c(&element, s + i - 1) < 0; --i) {
        s[i] = s[i - 1];
    }
    s[i] = element;
}

void insertion_sort(DataType *s, int f, int t, CompareType c) {
    for (int i = f; i < t; ++i) {
        insert_element(s, f, i, c);
        print_array(s, t, i + 1);
    }
}

/**
 * @brief Select the most wanted element (the minimum) in a pass of bubble
 * sort, by swapping the unordered pairs one by one.
 * 
 * @param s the sequence
 * @param f the from index
 * @param t the to index
 * @param c the comparison function
 */
static void bubble_select(DataType *s, int f, int t, CompareType c) {
    for (int i = t - 1; i > f; --i) {
        if (c(s + i - 1, s + i) > 0) {
            swap_elements(s + i - 1, s + i);
        }
    }
}

void bubble_sort(DataType *s, int f, int t, CompareType c) {
    for (int i = f; i < t; ++i) {
        bubble_select(s, i, t, c);
        print_array(s, t, i + 1);
    }
}

/**
 * @brief Select the most wanted element (the minimum) in a pass of selection
 * sort, by traversing the unordered subsequence one by one.
 *
 * @param s the sequence
 * @param f the from index
 * @param t the to index
 * @param c the comparison function
 * @return DataType* the pointer to the selected element
 */
static DataType *simple_select(DataType *s, int f, int t, CompareType c) {
    DataType *element = s + f;
    for (int i = f + 1; i < t; ++i) {
        if (c(element, s + i) > 0) {
            element = s + i;
        }
    }
    return element;
}

void selection_sort(DataType *s, int f, int t, CompareType c) {
    for (int i = f; i < t; ++i) {
        DataType *p = simple_select(s, i, t, c);
        if (p != s + i) {
            swap_elements(p, s + i);
        }
        print_array(s, t, i + 1);
    }
}

/**
 * @brief Partition process used for quick sort
 *
 * @param s the sequence
 * @param l the lower index
 * @param h the higher index
 * @param p the pivot index
 * @param c the comparison function
 * @return int the new index of the pivot after partition
 */
static int partition(DataType *s, int l, int h, int p, CompareType c) {
    if (l != p) {
        swap_elements(s + l, s + p);
    }
    DataType pivot = s[l];
    for (;;) {
        for (; l < h && c(&pivot, s + h) < 0; --h)
            ;
        if (l >= h) break;
        s[l++] = s[h];
        for (; l < h && c(s + l, &pivot) < 0; ++l)
            ;
        if (l >= h) break;
        s[h--] = s[l];
    }
    s[l] = pivot;
    return l;
}

/**
 * @brief The core function of quick sort, using recursion
 *
 * @param s the sequence
 * @param l the lower index
 * @param h the higher index
 * @param c the comparison function
 */
static void quick_sort_core(DataType *s, int l, int h, CompareType c) {
    if (l >= h) return;
    int m = partition(s, l, h, l, c);
    static int i = 0;
    print_array(s, 6, ++i);
    quick_sort_core(s, l, m - 1, c);
    quick_sort_core(s, m + 1, h, c);
}

void quick_sort(DataType *s, int f, int t, CompareType c) {
    quick_sort_core(s, f, t - 1, c);
}

/**
 * @brief Initiate the sequence for various sorting
 *
 * @param s the sequence
 * @param d the origial data
 * @param n the number of elements in the data
 */
static void initiate_sequence(DataType *s, int *d, int n) {
    for (int i = 0; i < n; ++i) {
        s[i] = d + i;
    }
    print_array(s, n, 0);
}

void demo_sorting() {
    int n = 6;
    int data[] = {21, 25, 22, 10, 25, 18};
    DataType *s = malloc(sizeof(int *) * n);
    printf("--------------insertion sort---------------\n");
    initiate_sequence(s, data, n);
    insertion_sort(s, 0, n, compare_ints);
    printf("--------------selection sort---------------\n");
    initiate_sequence(s, data, n);
    selection_sort(s, 0, n, compare_ints);
    printf("--------------bubble sort---------------\n");
    initiate_sequence(s, data, n);
    bubble_sort(s, 0, n, compare_ints);
    printf("--------------quick sort---------------\n");
    initiate_sequence(s, data, n);
    quick_sort(s, 0, n, compare_ints);
    print_array(s, n, 0);
    free(s);
}