#include "binary_tree.h"

#include "linked_queue.h"
#include "stack.h"

struct _tree {
    BinaryTreeNode *head;
};

static bool is_head(BinaryTreeNode *n) {
    assert(n);
    return !n->data;
}

static bool is_leaf(BinaryTreeNode *n) {
    assert(n);
    return !n->left && !n->right;
}

static BinaryTreeNode *left_most_child(BinaryTreeNode *n) {
    assert(n);
    for (; n->left; n = n->left)
        ;
    return n;
}

static BinaryTreeNode *left_most_parent(BinaryTreeNode *n) {
    assert(n);
    for (; n->parent && n->parent->right == n; n = n->parent)
        ;
    return n;
}

static BinaryTreeNode *left_most_leaf(BinaryTreeNode *n) {
    assert(n);
    for (; n = left_most_child(n), n->right; n = n->right)
        ;
    return n;
}

BinaryTreeNode *create_binary_tree_node(DataType d) {
    BinaryTreeNode *n = malloc(sizeof(BinaryTreeNode));
    if (n) {
        n->data = d;
        n->left = n->right = n->parent = NULL;
    }
    return n;
}

BinaryTree *create_binary_tree() {
    BinaryTree *t = malloc(sizeof(BinaryTree));
    if (t) {
        t->head = create_binary_tree_node(NULL);
    }
    return t;
}

bool cleanup_binary_tree_by_node(BinaryTreeNode *n) {
    BinaryTreeNode *next = left_most_leaf(n);
    for (; next; n = next, next = successor_binary_tree_postorder(n), free(n))
        ;
    return true;
}

bool cleanup_binary_tree(BinaryTree *t) {
    return t && cleanup_binary_tree_by_node(t->head->left);
}

void destroy_binary_tree(BinaryTree *t) {
    if (!cleanup_binary_tree(t)) {
        return;
    }
    free(t->head);
    free(t);
}

static BinaryTreeNode *attach_left_binary_tree(BinaryTreeNode *p,
                                               BinaryTreeNode *n) {
    assert(n && p);
    if (p->left) {
        n->left = p->left;
        p->left->parent = n;
    }
    p->left = n;
    n->parent = p;
    return n;
}

static BinaryTreeNode *attach_right_binary_tree(BinaryTreeNode *p,
                                                BinaryTreeNode *n) {
    assert(n && p);
    if (p->right) {
        n->right = p->right;
        p->right->parent = n;
    }
    p->right = n;
    n->parent = p;
    return n;
}

bool insert_left_binary_tree(BinaryTreeNode *p, DataType d) {
    if (!p) {
        printf("Wrong insertion place!\n");
        return false;
    }
    BinaryTreeNode *n = create_binary_tree_node(d);
    return n && attach_left_binary_tree(p, n);
}

bool insert_right_binary_tree(BinaryTreeNode *p, DataType d) {
    if (!p) {
        printf("Wrong insertion place!\n");
        return false;
    }
    BinaryTreeNode *n = create_binary_tree_node(d);
    return n && attach_right_binary_tree(p, n);
}

static BinaryTreeNode *detach_left_binary_tree(BinaryTreeNode *p) {
    assert(p && p->left);
    BinaryTreeNode *c = p->left;
    p->left = NULL;
    c->parent = NULL;
    return c;
}

static BinaryTreeNode *detach_right_binary_tree(BinaryTreeNode *p) {
    assert(p && p->right);
    BinaryTreeNode *c = p->right;
    p->right = NULL;
    c->parent = NULL;
    return c;
}

bool remove_left_binary_tree(BinaryTreeNode *p) {
    if (!p) {
        printf("Wrong removal place!\n");
        return false;
    }
    BinaryTreeNode *c = detach_left_binary_tree(p);
    return cleanup_binary_tree_by_node(c);
}

bool remove_right_binary_tree(BinaryTreeNode *p) {
    if (!p) {
        printf("Wrong removal place!\n");
        return false;
    }
    BinaryTreeNode *c = detach_right_binary_tree(p);
    return cleanup_binary_tree_by_node(c);
}

BinaryTreeNode *binary_root(BinaryTree *t) {
    assert(t);
    return t->head->left;
}

BinaryTreeNode *left_child(BinaryTreeNode *p) {
    assert(p);
    return p->left;
}

BinaryTreeNode *right_child(BinaryTreeNode *p) {
    assert(p);
    return p->right;
}

BinaryTreeNode *binary_parent(BinaryTreeNode *n) {
    assert(n);
    return n->parent;
}

BinaryTreeNode *set_left_child(BinaryTreeNode *r, BinaryTreeNode *n) {
    assert(!r->left);
    r->left = n;
    n->parent = r;
    return r;
}

BinaryTreeNode *set_right_child(BinaryTreeNode *r, BinaryTreeNode *n) {
    assert(!r->right);
    r->right = n;
    n->parent = r;
    return r;
}

DataType binary_node_data(BinaryTreeNode *n) {
    assert(n);
    return n->data;
}

BinaryTreeNode *successor_binary_tree_preorder(BinaryTreeNode *n) {
    assert(n && n->parent);
    n = n->left ? n->left
                : (n->right ? n->right : left_most_parent(n)->parent->right);
    return n;
}

BinaryTreeNode *successor_binary_tree_inorder(BinaryTreeNode *n) {
    assert(n && n->parent);
    n = n->right ? left_most_child(n->right) : left_most_parent(n)->parent;
    return is_head(n) ? NULL : n;
}

BinaryTreeNode *successor_binary_tree_postorder(BinaryTreeNode *n) {
    assert(n && n->parent);
    BinaryTreeNode *parent = n->parent;
    BinaryTreeNode *right = parent->right;
    n = (!right || right == n) ? parent : left_most_leaf(right);
    return is_head(n) ? NULL : n;
}

void traverse_binary_tree_preorder_recursively(BinaryTreeNode *p, VisitType v) {
    if (!p) {
        return;
    }
    v(p->data);
    traverse_binary_tree_preorder_recursively(p->left, v);
    traverse_binary_tree_preorder_recursively(p->right, v);
}

void traverse_binary_tree_inorder_recursively(BinaryTreeNode *p, VisitType v) {
    if (!p) {
        return;
    }
    traverse_binary_tree_inorder_recursively(p->left, v);
    v(p->data);
    traverse_binary_tree_inorder_recursively(p->right, v);
}

void traverse_binary_tree_postorder_recursively(BinaryTreeNode *p,
                                                VisitType v) {
    if (!p) {
        return;
    }
    traverse_binary_tree_postorder_recursively(p->left, v);
    traverse_binary_tree_postorder_recursively(p->right, v);
    v(p->data);
}

void traverse_binary_tree_level_order(BinaryTreeNode *p, VisitType v) {
    LinkedQueue *buffer = create_linked_queue();
    if (!buffer) {
        return;
    }
    push_linked_queue(buffer, p);
    while (!empty_linked_queue(buffer)) {
        pop_linked_queue(buffer, (DataType *)(&p));
        v(p->data);
        if (p->left) {
            push_linked_queue(buffer, p->left);
        }
        if (p->right) {
            push_linked_queue(buffer, p->right);
        }
    }
    destroy_linked_queue(buffer);
}

static void visit_along_left_binary_tree(BinaryTreeNode *p, VisitType v,
                                         Stack **s) {
    for (; p; p = p->left) {
        v(p->data);
        if (p->right) {
            push_stack(*s, p->right);
        }
    }
}

void traverse_binary_tree_preorder(BinaryTreeNode *p, VisitType v) {
    Stack *buffer = create_stack();
    if (!buffer) {
        return;
    }
    DataType d;
    for (; visit_along_left_binary_tree(p, v, &buffer), !is_stack_empty(buffer);
         pop_stack(buffer, &d), p = d)
        ;
    destroy_stack(buffer);
}

void traverse_binary_tree_preorder_no_stack(BinaryTreeNode *p, VisitType v) {
    for (; p; v(p->data), p = successor_binary_tree_preorder(p))
        ;
}

static void go_along_left_binary_tree(BinaryTreeNode *p, Stack **s) {
    for (; p; push_stack(*s, p), p = p->left)
        ;
}

void traverse_binary_tree_inorder(BinaryTreeNode *p, VisitType v) {
    Stack *buffer = create_stack();
    if (!buffer) {
        return;
    }
    DataType d;
    for (; go_along_left_binary_tree(p, &buffer), !is_stack_empty(buffer);
         p = p->right) {
        pop_stack(buffer, &d);
        p = d;
        v(p->data);
    }
    destroy_stack(buffer);
}

void traverse_binary_tree_inorder_no_stack(BinaryTreeNode *p, VisitType v) {
    p = left_most_child(p);
    for (; p; v(p->data), p = successor_binary_tree_inorder(p))
        ;
}

void traverse_binary_tree_postorder_no_stack(BinaryTreeNode *p, VisitType v) {
    p = left_most_leaf(p);
    for (; p; v(p->data), p = successor_binary_tree_postorder(p))
        ;
}

static void print(DataType d) { printf("%d, ", DATAVALUE(int, d)); }

void demo_binary_tree() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    BinaryTree *t = create_binary_tree();
    for (int i = 0; i < 4; ++i) {
        insert_left_binary_tree(t->head, array + i);
        insert_right_binary_tree(t->head->left, array + i + 4);
    }
    traverse_binary_tree_level_order(t->head->left, print);
    printf(" level order\n");
    printf("---------------------------------------\n");
    traverse_binary_tree_preorder_recursively(t->head->left, print);
    printf(" preorder recursive\n");
    traverse_binary_tree_preorder(t->head->left, print);
    printf(" preorder\n");
    traverse_binary_tree_preorder_no_stack(t->head->left, print);
    printf(" preorder no stack\n");
    printf("---------------------------------------\n");
    traverse_binary_tree_inorder_recursively(t->head->left, print);
    printf(" inorder recursive\n");
    traverse_binary_tree_inorder(t->head->left, print);
    printf(" inorder\n");
    traverse_binary_tree_inorder_no_stack(t->head->left, print);
    printf(" inorder no stack\n");
    printf("---------------------------------------\n");
    traverse_binary_tree_postorder_recursively(t->head->left, print);
    printf(" postorder recursive\n");
    traverse_binary_tree_postorder_no_stack(t->head->left, print);
    printf(" postorder no stack\n");
    destroy_binary_tree(t);
}