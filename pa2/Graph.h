///////////////////////////////////
// Yukti Malhan
// ymalhan
// 2022 Winter CSE101 pa2
// Graph.h
// Header file for Graph ADT
////////////////////////////////////////

#pragma once
#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define NIL -1
#define INF -2

typedef struct GraphObj *Graph;

// Constructors-Destructors ------------------------------
Graph newGraph(int n);
void freeGraph(Graph *pG);

// Access functions -------------------------------------
int getOrder(Graph G); // return corresponding field values
int getSize(Graph G);
int getSource(Graph G); // returns source vertex recently used in BFS() or NIL
int getParent(Graph G, int u); // return parent vertex u in BFS or NIL
int getDist(Graph G, int u);   // returns distance from recent BFS source
                               // to vertex or INF
void getPath(List L, Graph G,
             int u); // appends to L the vertices of shortest path or NIL

// Manipulation procedures --------------------------------
void makeNull(Graph G);              // deletes all edges of G, original state
void addEdge(Graph G, int u, int v); // inserts new edge joining u to v
void addArc(Graph G, int u, int v);  // inserts new directed edge from u to v
void BFS(Graph G, int s); // runs BFS algorithm on Graph G with source s

// Other operations ----------------------------------------
void printGraph(FILE *out,
                Graph G); // prints the adjacency list rep of G to out
