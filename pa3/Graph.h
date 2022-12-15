///////////////////////////////////
// Yukti Malhan
// ymalhan
// 2022 Winter CSE101 pa3
// Graph.h
// Header file for Graph ADT
//////////////////////////////////////////
#pragma once
#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define NIL 0
#define UNDEF -1
typedef struct GraphObj *Graph;

// Constructors-Destructors ------------------------------
Graph newGraph(int n);
void freeGraph(Graph *pG);

// Access functions -------------------------------------
int getOrder(Graph G); // return corresponding field values
int getSize(Graph G);
int getParent(Graph G, int u);   // Pre: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u); // Pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u);   // Pre: 1<=u<=n=getOrder(G)

// Manipulation procedures --------------------------------
void addArc(Graph G, int u, int v);  // Pre: 1<=u<=n, 1<=v<=n
void addEdge(Graph G, int u, int v); // Pre: 1<=u<=n, 1<=v<=n
void DFS(Graph G, List S);           // Pre: length(S)==getOrder(G)

// Other operations ----------------------------------------
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE *out, Graph G);
