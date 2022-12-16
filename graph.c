#include "graph.h"

#include "linked_queue.h"
#include "vector.h"

struct _vertex {
    DataType data;
    int index;
    Vector *neighbors;
    bool visited;
};

struct _edge {
    Vertex *from;
    Vertex *to;
    unsigned weight;
};

struct _adjacency_matrix {
    Vertex *vertices;
    unsigned **weights;
    int size;
};

struct _adjacency_list {
    Vector *vertices;
    Vector *edges;
};

Vertex *create_vertex(DataType d, int i) {
    Vertex *v = malloc(sizeof(Vertex));
    if (v) {
        v->data = d;
        v->index = i;
        v->neighbors = create_vector(1);
        v->visited = false;
    }
    return v;
}

void destroy_vertex(Vertex *v) {
    if (v) {
        destroy_vector(v->neighbors);
    }
    free(v);
}

static Vertex *get_vertex_at(Vector *v, int k) {
    return *vector_at(v, k);
}

Edge *create_edge(Vertex *f, Vertex *t, int w) {
    Edge *e = malloc(sizeof(Edge));
    if (e) {
        e->from = f;
        e->to = t;
        e->weight = w;
    }
    return e;
}

static Edge *get_edge_at(Vector *v, int k) {
    return *vector_at(v, k);
}

static void initiate_vertices(AdjacencyMatrix *m) {
    int n = m->size;
    m->vertices = malloc(sizeof(Vertex) * n);
    for (int i = 0; i < n; ++i) {
        m->vertices[i].index = i;
        m->vertices[i].visited = false;
    }
}

static void initiate_weights(AdjacencyMatrix *m) {
    int n = m->size;
    m->weights = malloc(sizeof(int *) * n);
    for (int i = 0; i < n; ++i) {
        m->weights[i] = malloc(sizeof(int) * n);
        for (int j = 0; j < n; ++j) {
            m->weights[i][j] = -1;
        }
    }
}

AdjacencyMatrix *create_adjacency_matrix(int n) {
    AdjacencyMatrix *matrix = malloc(sizeof(AdjacencyMatrix));
    if (matrix) {
        matrix->size = n;
        initiate_vertices(matrix);
        initiate_weights(matrix);
    }
    return matrix;
}

void destroy_adjacency_matrix(AdjacencyMatrix *m) {
    if (m) {
        for (int i = 0; i < m->size; ++i) {
            free(m->weights[i]);
        }
        free(m->weights);
        free(m->vertices);
    }
    free(m);
}

AdjacencyList *create_adjacency_list() {
    AdjacencyList *list = malloc(sizeof(AdjacencyList));
    if (list) {
        list->vertices = create_vector(1);
        list->edges = create_vector(1);
    }
    return list;
}

void destroy_adjacency_list(AdjacencyList *l) {
    if (l) {
        int n_vertices = size_of_vector(l->vertices);
        for (int i = 0; i < n_vertices; ++i) {
            destroy_vertex((Vertex *)*vector_at(l->vertices, i));
        }
        destroy_vector(l->vertices);
        int n_edges = size_of_vector(l->edges);
        for (int i = 0; i < n_edges; ++i) {
            free((Edge *)*vector_at(l->edges, i));
        }
        destroy_vector(l->edges);
    }
    free(l);
}

static bool in_range(int k, int n) { return 0 <= k && k < n; }

Vertex *vertex_at(AdjacencyMatrix *m, int k) {
    assert(m && in_range(k, m->size));
    return m->vertices + k;
}

void set_edge(AdjacencyMatrix *m, Edge *e) {
    assert(m && e);
    int from = e->from->index;
    int to = e->to->index;
    if (in_range(from, m->size) && in_range(to, m->size)) {
        m->weights[from][to] = e->weight;
    }
}

void connect_in_matrix(AdjacencyMatrix *m, int f, int t, int w) {
    assert(m && in_range(f, m->size) && in_range(t, m->size));
    m->weights[f][t] = w;
}

void disconnect_in_matrix(AdjacencyMatrix *m, int f, int t) {
    assert(m && in_range(f, m->size) && in_range(t, m->size));
    m->weights[f][t] = -1;
}

bool is_adjacent(AdjacencyMatrix *m, int f, int t) {
    assert(m && in_range(f, m->size) && in_range(t, m->size));
    return m->weights[f][t] != -1;
}

void clear_matrix_states(AdjacencyMatrix *m) {
    assert(m);
    for (int i = 0; i < m->size; ++i) {
        vertex_at(m, i)->visited = false;
    }
}

static void depth_first_search_matrix_core(AdjacencyMatrix *m, int k,
                                           VisitType v) {
    Vertex *vertex = vertex_at(m, k);
    v(vertex->data);
    vertex->visited = true;
    for (int i = 0; i < m->size; ++i) {
        if (is_adjacent(m, k, i) && !vertex_at(m, i)->visited) {
            depth_first_search_matrix_core(m, i, v);
        }
    }
}

void depth_first_search_matrix(AdjacencyMatrix *m, VisitType v) {
    assert(m);
    clear_matrix_states(m);
    for (int i = 0; i < m->size; ++i) {
        if (!vertex_at(m, i)->visited) {
            depth_first_search_matrix_core(m, i, v);
        }
    }
}

static void visit_vertex_and_push_queue(VisitType v, LinkedQueue *q,
                                        Vertex *x) {
    v(x->data);
    x->visited = true;
    push_linked_queue(q, x);
}

static void breadth_first_search_matrix_core(AdjacencyMatrix *m, int k,
                                             VisitType v) {
    LinkedQueue *buffer = create_linked_queue();
    if (!buffer) {
        return;
    }
    Vertex *from = vertex_at(m, k);
    visit_vertex_and_push_queue(v, buffer, from);
    while (!empty_linked_queue(buffer)) {
        pop_linked_queue(buffer, (DataType *)&from);
        for (int i = 0; i < m->size; ++i) {
            Vertex *to = vertex_at(m, i);
            if (is_adjacent(m, from->index, i) && !to->visited) {
                visit_vertex_and_push_queue(v, buffer, to);
            }
        }
    }
    destroy_linked_queue(buffer);
}

void breadth_first_search_matrix(AdjacencyMatrix *m, VisitType v) {
    assert(m);
    clear_matrix_states(m);
    for (int i = 0; i < m->size; ++i) {
        if (!vertex_at(m, i)->visited) {
            breadth_first_search_matrix_core(m, i, v);
        }
    }
}

void connect_in_list(AdjacencyList *l, int f, int t, int w) {
    int n_vertices = size_of_vector(l->vertices);
    assert(l && in_range(f, n_vertices) && in_range(t, n_vertices));
    Vertex *from = get_vertex_at(l->vertices, f);
    Vertex *to = get_vertex_at(l->vertices, t);
    if (from && to) {
        Edge *edge = create_edge(from, to, w);
        push_back_vector(l->edges, edge);
        push_back_vector(from->neighbors, edge);
    }
}

void disconnect_in_list(AdjacencyList *l, int f, int t) {
    int n_vertices = size_of_vector(l->vertices);
    assert(l && in_range(f, n_vertices) && in_range(t, n_vertices));
    // TODO
}

void clear_list_states(AdjacencyList *l) {
    assert(l);
    int n_vertices = size_of_vector(l->vertices);
    for (int i = 0; i < n_vertices; ++i) {
        get_vertex_at(l->vertices, i)->visited = false;
    }
}

static void depth_first_search_list_core(AdjacencyList *l, Vertex *x,
                                         VisitType v) {
    v(x->data);
    x->visited = true;
    int n_neighbors = size_of_vector(x->neighbors);
    for (int i = 0; i < n_neighbors; ++i) {
        Vertex *to = get_edge_at(x->neighbors, i)->to;
        if (!to->visited) {
            depth_first_search_list_core(l, to, v);
        }
    }
}

void depth_first_search_list(AdjacencyList *l, VisitType v) {
    assert(l);
    clear_list_states(l);
    int n_vertices = size_of_vector(l->vertices);
    for (int i = 0; i < n_vertices; ++i) {
        Vertex *x = get_vertex_at(l->vertices, i);
        if (x && !x->visited) {
            depth_first_search_list_core(l, x, v);
        }
    }
}

static void breadth_first_search_list_core(AdjacencyList *l, Vertex *x,
                                           VisitType v) {
    LinkedQueue *buffer = create_linked_queue();
    if (!buffer) {
        return;
    }
    visit_vertex_and_push_queue(v, buffer, x);
    while (!empty_linked_queue(buffer)) {
        pop_linked_queue(buffer, (DataType *)&x);
        int n_neighbors = size_of_vector(x->neighbors);
        for (int i = 0; i < n_neighbors; ++i) {
            Vertex *to = get_edge_at(x->neighbors, i)->to;
            if (!to->visited) {
                visit_vertex_and_push_queue(v, buffer, to);
            }
        }
    }
    destroy_linked_queue(buffer);
}

void breadth_first_search_list(AdjacencyList *l, VisitType v) {
    assert(l);
    clear_list_states(l);
    int n_vertices = size_of_vector(l->vertices);
    for (int i = 0; i < n_vertices; ++i) {
        Vertex *x = get_vertex_at(l->vertices, i);
        if (!x->visited) {
            breadth_first_search_list_core(l, x, v);
        }
    }
}

static void print(DataType d) { printf("%c, ", 'A' - 1 + DATAVALUE(int, d)); }

void demo_graph() {
    int n_vertices = 8;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8};
    // adjacency matrix
    AdjacencyMatrix *matrix = create_adjacency_matrix(n_vertices);
    for (int i = 0; i < n_vertices; ++i) {
        vertex_at(matrix, i)->data = data + i;
    }
    connect_in_matrix(matrix, 0, 1, 1);
    connect_in_matrix(matrix, 1, 0, 1);
    connect_in_matrix(matrix, 0, 2, 1);
    connect_in_matrix(matrix, 2, 0, 1);
    connect_in_matrix(matrix, 1, 3, 1);
    connect_in_matrix(matrix, 3, 1, 1);
    connect_in_matrix(matrix, 1, 4, 1);
    connect_in_matrix(matrix, 4, 1, 1);
    connect_in_matrix(matrix, 3, 4, 1);
    connect_in_matrix(matrix, 4, 3, 1);
    connect_in_matrix(matrix, 2, 5, 1);
    connect_in_matrix(matrix, 5, 2, 1);
    connect_in_matrix(matrix, 2, 6, 1);
    connect_in_matrix(matrix, 6, 2, 1);
    connect_in_matrix(matrix, 5, 6, 1);
    connect_in_matrix(matrix, 6, 5, 1);
    connect_in_matrix(matrix, 3, 7, 1);
    connect_in_matrix(matrix, 7, 3, 1);
    depth_first_search_matrix(matrix, print);
    printf("\n");
    breadth_first_search_matrix(matrix, print);
    printf("\n");
    destroy_adjacency_matrix(matrix);
    // adjacency list
    AdjacencyList *list = create_adjacency_list();
    for (int i = 0; i < n_vertices; ++i) {
        Vertex *vertex = create_vertex(data + i, i);
        push_back_vector(list->vertices, vertex);
    }
    connect_in_list(list, 0, 1, 1);
    connect_in_list(list, 0, 2, 1);
    connect_in_list(list, 1, 0, 1);
    connect_in_list(list, 1, 3, 1);
    connect_in_list(list, 1, 4, 1);
    connect_in_list(list, 2, 0, 1);
    connect_in_list(list, 2, 5, 1);
    connect_in_list(list, 2, 6, 1);
    connect_in_list(list, 3, 1, 1);
    connect_in_list(list, 3, 4, 1);
    connect_in_list(list, 3, 7, 1);
    connect_in_list(list, 4, 1, 1);
    connect_in_list(list, 4, 3, 1);
    connect_in_list(list, 5, 2, 1);
    connect_in_list(list, 5, 6, 1);
    connect_in_list(list, 6, 2, 1);
    connect_in_list(list, 6, 5, 1);
    connect_in_list(list, 7, 3, 1);
    depth_first_search_list(list, print);
    printf("\n");
    breadth_first_search_list(list, print);
    printf("\n");
    destroy_adjacency_list(list);
}