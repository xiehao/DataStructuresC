#include "tree.h"

#include "stack.h"

#define TRAVERSE_TREE_RECURSIVELY

struct _node {
    DataType data;
    TreeNode *eldest_son;
    TreeNode *sibling;
};

struct _tree {
    TreeNode *head;
};

static TreeNode *create_tree_node(DataType d) {
    TreeNode *n = malloc(sizeof(TreeNode));
    if (n) {
        n->data = d;
        n->eldest_son = n->sibling = NULL;
    }
    return n;
}

Tree *create_tree() {
    Tree *t = malloc(sizeof(Tree));
    if (t) {
        t->head = create_tree_node(0);
    }
    return t;
}

void destroy_tree(Tree *t) {
    if (t) {
        free(t->head);
    }
    free(t);
}

TreeNode *attach_tree_node(TreeNode *p, TreeNode *n) {
    assert(p && n);
    n->sibling = p->eldest_son;
    p->eldest_son = n;
    return n;
}

TreeNode *insert_tree_node(TreeNode *p, DataType d) {
    if (!p) return p;
    TreeNode *n = create_tree_node(d);
    if (n) n = attach_tree_node(p, n);
    return n;
}

static void traverse_tree_preorder_recursively(TreeNode *n, VisitType v) {
    if (!n) return;
    v(n->data);
    for (n = n->eldest_son; n; n = n->sibling) {
        traverse_tree_preorder_recursively(n, v);
    }
}

static void visit_along_eldest(TreeNode *n, VisitType v, Stack **s) {
    Stack *buffer = create_stack();
    if (!buffer) return;
    for (; n; n = n->eldest_son) {
        v(n->data);
        TreeNode *p = n->eldest_son;
        if (p) {
            for (p = p->sibling; p; push_stack(buffer, p), p = p->sibling)
                ;
            for (; !is_stack_empty(buffer);
                 push_stack(*s, pop_stack(buffer).data))
                ;
        }
    }
    destroy_stack(buffer);
}

void traverse_tree_preorder(Tree *t, VisitType v) {
#ifdef TRAVERSE_TREE_RECURSIVELY
    traverse_tree_preorder_recursively(t->head->eldest_son, v);
#else
    Stack *buffer = create_stack();
    if (!buffer) return;
    DataType d;
    for (TreeNode *n = t->head->eldest_son;
         visit_along_eldest(n, v, &buffer), !is_stack_empty(buffer);
         pop_stack(buffer, &d), n = d)
        ;
    destroy_stack(buffer);
#endif
}

static void traverse_tree_postorder_recursively(TreeNode *n, VisitType v) {
    if (!n) return;
    for (TreeNode *p = n->eldest_son; p; p = p->sibling) {
        traverse_tree_postorder_recursively(p, v);
    }
    v(n->data);
}

void traverse_tree_postorder(Tree *t, VisitType v) {
#ifdef TRAVERSE_TREE_RECURSIVELY
    traverse_tree_postorder_recursively(t->head->eldest_son, v);
#else
    // TODO
#endif
}

static void print(DataType d) { printf("%d ", DATAVALUE(int, d)); }

void demo_tree() {
    Tree *t = create_tree();
    int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    TreeNode *n = insert_tree_node(t->head, array);
#define N 4
    TreeNode *p[N];
    for (int i = 0; i < N; ++i) {
        p[i] = insert_tree_node(n, array + i + 1);
    }
    for (int i = 0; i < N; ++i) {
        insert_tree_node(p[i], array + i + 1 + N);
        insert_tree_node(p[i], array + i + 1 + N + N);
    }
    traverse_tree_preorder(t, print);
    printf("\n");
    traverse_tree_postorder(t, print);
    printf("\n");
    destroy_tree(t);
}