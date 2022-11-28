#ifndef GRAPH_H
#define GRAPH_H

#include "common.h"

typedef struct _vertex Vertex;

Vertex *create_vertex(DataType d, int i);

void destroy_vertex(Vertex *v);

typedef struct _edge Edge;

Edge *create_edge(Vertex *f, Vertex *t, int w);

///////////////////////Adjacency Matrix/////////////////////////////

typedef struct _adjacency_matrix AdjacencyMatrix;

AdjacencyMatrix *create_adjacency_matrix(int n);

void destroy_adjacency_matrix(AdjacencyMatrix *m);

bool is_adjacent(AdjacencyMatrix *m, int f, int t);

void connect_in_matrix(AdjacencyMatrix *m, int f, int t, int w);

void disconnect_in_matrix(AdjacencyMatrix *m, int f, int t);

void depth_first_search_matrix(AdjacencyMatrix *m, VisitType v);

void breadth_first_search_matrix(AdjacencyMatrix *m, VisitType v);

/////////////////////////Adjacency List/////////////////////////////

typedef struct _adjacency_list AdjacencyList;

AdjacencyList *create_adjacency_list();

void destroy_adjacency_list(AdjacencyList *l);

void connect_in_list(AdjacencyList *l, int f, int t, int w);

void disconnect_in_list(AdjacencyList *l, int f, int t);

///////////////////////////////Demo/////////////////////////////////

void demo_graph();

#endif // GRAPH_H