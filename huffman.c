#include "huffman.h"

#ifdef LINKED_STORAGE_IMPLEMENTATION

#include "vector.h"

static BinaryTreeNode *get_node(Vector *v, int k) {
    if (k < 0 || k >= size_of_vector(v)) return NULL;
    DataType d;
    get_vector_value_at(v, k, &d);
    return &DATAVALUE(BinaryTreeNode, d);
}

static int get_weight(Vector *v, int k) {
    return DATAVALUE(int, get_node(v, k)->data);
}

static void find_candidates(Vector *v, int *f, int *s) {
    assert(size_of_vector(v) > 1);
    int first_weight = get_weight(v, 0), second_weight = get_weight(v, 1);
    *f = 0, *s = 1;
    if (first_weight > second_weight) {
        first_weight = get_weight(v, 1), second_weight = get_weight(v, 0);
        *f = 1, *s = 0;
    }
    for (int k = 2; k < size_of_vector(v); ++k) {
        int weight = get_weight(v, k);
        if (weight < first_weight) {
            second_weight = first_weight, *s = *f;
            first_weight = weight, *f = k;
        } else if (weight < second_weight)
            second_weight = weight, *s = k;
    }
}

static BinaryTreeNode *merge_nodes(BinaryTreeNode *lhs, BinaryTreeNode *rhs) {
    int *data = malloc(sizeof(int));
    *data = DATAVALUE(int, binary_node_data(lhs)) +
            DATAVALUE(int, binary_node_data(rhs));
    BinaryTreeNode *root = create_binary_tree_node(data);
    root = set_left_child(root, lhs);
    root = set_right_child(root, rhs);
    return root;
}

static void swap_ints(int *lhs, int *rhs) {
    *lhs ^= *rhs, *rhs ^= *lhs, *lhs ^= *rhs;
}

static void merge_subtrees(Vector *v, int f, int s) {
    BinaryTreeNode *first = get_node(v, f);
    BinaryTreeNode *second = get_node(v, s);
    BinaryTreeNode *new = merge_nodes(first, second);
    if (f > s) swap_ints(&f, &s);
    set_vector_value_at(v, f, new);
    remove_vector_by_index(v, s, NULL);
}

BinaryTreeNode *create_huffman_tree(int w[], int n) {
    if (n < 1) return NULL;
    Vector *leaves = create_vector(n);
    for (int i = 0; i < n; ++i) {
        BinaryTreeNode *node = create_binary_tree_node(w + i);
        push_back_vector(leaves, node);
    }
    int first, second;
    for (; size_of_vector(leaves) > 1;) {
        find_candidates(leaves, &first, &second);
        merge_subtrees(leaves, first, second);
    }
    return get_node(leaves, 0);
}

static void print(DataType d) { printf("%d, ", DATAVALUE(int, d)); }

void demo_huffman() {
    int weights[] = {18, 32, 10, 14, 16, 4, 6};
    BinaryTreeNode *root = create_huffman_tree(weights, 7);
    traverse_binary_tree_inorder(root, print);
    printf("\n");
    traverse_binary_tree_preorder(root, print);
    printf("\n");
}

#else

struct _node {
    int weight;
    int left;
    int right;
    int parent;
};

static void find_candidates(HuffmanNode *t, int n, int *f, int *s) {
    assert(n > 1);
    int first_weight = INT_MAX, second_weight = INT_MAX;
    for (int i = 0; i < n; ++i) {
        if (-1 == t[i].parent) {
            int weight = t[i].weight;
            if (weight < first_weight) {
                second_weight = first_weight, *s = *f;
                first_weight = weight, *f = i;
            } else if (weight < second_weight) {
                second_weight = weight, *s = i;
            }
        }
    }
}

static void merge_subtrees(HuffmanNode *t, int p, int f, int s) {
    t[f].parent = t[s].parent = p;
    t[p].weight = t[f].weight + t[s].weight;
    t[p].left = f, t[p].right = s;
}

HuffmanNode *create_huffman_tree(int w[], int n) {
    int size = 2 * n - 1;
    HuffmanNode *tree = malloc(sizeof(HuffmanNode) * size);
    for (int i = 0; i < size; ++i) {
        tree[i].weight = INT_MAX;
        tree[i].left = tree[i].right = tree[i].parent = -1;
    }
    for (int i = 0; i < n; ++i) {
        tree[i].weight = w[i];
    }
    int first, second;
    for (int i = n; i < size; ++i) {
        find_candidates(tree, i, &first, &second);
        merge_subtrees(tree, i, first, second);
    }
    return tree;
}

int encoding(HuffmanNode *t, int i, int *k) {
    int code = 0;
    for (*k = 0; -1 != t[i].parent; i = t[i].parent, ++*k) {
        if (t[t[i].parent].right == i) {
            code |= (1 << *k);
        }
    }
    return code;
}

char decoding(HuffmanNode *t, int n, char *c, int b) {
    int k = n - 1;
    for (; c[b] && -1 != t[k].left;) {
        k = '1' == c[b++] ? t[k].right : t[k].left;
    }
    return 'A' + k;
}

static void print_huffman(HuffmanNode *t, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%5d:%5d%5d%5d%5d\n", i, t[i].weight, t[i].left, t[i].right,
               t[i].parent);
    }
}

static void print_code(int c, int k) {
    for (; k > 0;) {
        printf("%1d", (c >> --k) & 1);
    }
}

void demo_huffman() {
    int weights[] = {18, 32, 10, 14, 16, 4, 6};
    int n = sizeof(weights) / sizeof(weights[0]);
    HuffmanNode *root = create_huffman_tree(weights, n);
    print_huffman(root, 2 * n - 1);
    printf("encoding...\n");
    for (int i = 0; i < n; ++i) {
        printf("%c: ", i + 'A');
        int k, c = encoding(root, i, &k);
        print_code(c, k);
        printf("\n");
    }
    printf("decoding...\n");
    char c = decoding(root, 2 * n - 1, "0110", 2);
    printf("%c\n", c);
    free(root);
}

#endif