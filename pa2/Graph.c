///////////////////////////////////
// Yukti Malhan
// ymalhan
// 2022 Winter CSE101 pa2
// Graph.c
// Implementation file for Graph ADT
////////////////////////////////////////

#include "Graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// private Graph object
typedef struct GraphObj {
  List *adj;   // List array for neighbors
  int *color;  // int array for color
  int *parent; // int array for parent of vertex
  int *dist;   // int array for ditance from source to vertex i
  int order;   // store number of vertices
  int size;    // store number of edges
  int source;  // label of vertex most recently used as source
} GraphObj;

// Constructors-Destructors-------------------------------------------
// newGraph()
// returns a graph object with n vertices and 0 edges
Graph newGraph(int n) {
  Graph G = malloc(sizeof(GraphObj)); // allocate with malloc
  G->adj =
      malloc(sizeof(List) * (n + 1)); // allocate list array with n+1 length
  G->color = malloc(sizeof(int) * (n + 1)); // int aray with n+1
  G->parent = malloc(sizeof(int) * (n + 1));
  G->dist = malloc(sizeof(int) * (n + 1));
  G->order = n;    // number of vertices is n
  G->size = 0;     // empty edges
  G->source = NIL; // NIL if BFS not called yet
  for (int i = 1; i <= n; i++) {
    G->adj[i] = newList(); // we loop through to create list indicies 1 to n
    G->parent[i] = NIL;    // nil if bfs not yet called
    G->dist[i] = INF;      // Inf if bfs not yet called
  }
  return (G);
}

// freeGraph()
// frees all heap memory associated with Graph *pG then sets *pG to NULL
void freeGraph(Graph *pG) {
  if (pG != NULL && *pG != NULL) {
    for (int i = 1; i <= (*pG)->order; i++) {
      freeList(&(*pG)->adj[i]); // free all the adj lists
    }
    free((*pG)->adj);
    free((*pG)->color); // free color, parent, dist
    free((*pG)->dist);
    free((*pG)->parent);
    free(*pG);
    *pG = NULL;
  }
}

// Access functions----------------------------------------------------------
// getOrder()
// returns order
int getOrder(Graph G) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: calling getOrder() on NULL graph\n");
    exit(EXIT_FAILURE);
  }
  return G->order;
}

// getSize()
// returns size
int getSize(Graph G) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: calling getSize() on NULL graph\n");
    exit(EXIT_FAILURE);
  }
  return G->size;
}

// getSource()
// returns source or nil if bfs not called
int getSource(Graph G) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: calling getSource() on NULL graph\n");
    exit(EXIT_FAILURE);
  }
  if (G->source == NIL) {
    return NIL; // return NIL if BFS not called -> value of -1
  } else {
    return G->source;
  }
}

// getParent()
// return parent vertex u or NIL if BFS not called
// precon: 1 <= u <= getOrder(G)
int getParent(Graph G, int u) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: calling getParent() on NULL graph\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > getOrder(G)) {
    return 0;
  }
  // if (u >= 1 && u <= getOrder(G)) { // if precond fine
  if (G->parent[u] == NIL) { // if parent at u is -1, return nil
    return NIL;
  } else {
    return G->parent[u]; // else return the parent vertex u
  }
}

// getDist()
// return distance from recent BFS source to u, or INF if not called
// precon: 1 <= u <= getOrder(G)
int getDist(Graph G, int u) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: calling getDist on NULL graph\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > getOrder(G)) {
    return 0;
  }
  if (G->dist[u] == INF) {
    return INF; // if dist -1 return INF
  } else {
    return G->dist[u]; // else return dist
  }
}

// getPath()
// appends to list L verticies of shortest path in G from source to u
// or appends to L the value of NIL if no such path exists
// precon: 1 <= u <= getOrder(G)
// precon: getSource(G) != NIL
// using print path from prof
void getPath(List L, Graph G, int u) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: calling getPath() on NULL graph\n");
    exit(EXIT_FAILURE);
  }
  if (L == NULL) {
    fprintf(stderr, "Graph Error: calling getPath() on NULL list\n");
    exit(EXIT_FAILURE);
  }
  if (getSource(G) == NIL) {
    // fprintf(stderr, "Graph Error: calling getPath() on NIL source\n");
    // exit(EXIT_FAILURE);
    return;
  }
  if (u < 1 || u > getOrder(G)) {
    return;
  }
  if (G->source == u) {
    append(L, u);
  } else if (G->parent[u] == NIL) {
    append(L, NIL); // append NIL
  } else {
    getPath(L, G, G->parent[u]);
    append(L, u);
  }
}

// Manipulation procedures---------------------------------------------------
// makeNull()
// deletes all edges of G, restoring to og state
void makeNull(Graph G) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: calling makeNull on Null Graph\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i <= G->order; i++) {
    clear(G->adj[i]); // clear list of vertices to delete edges
  }
  for (int i = 1; i <= G->order; i++) {
    G->color[i] = 0;
    G->dist[i] = 0;
    G->parent[i] = 0;
  } // clear the lists and reset to OG state
  G->size = 0;
  G->source = NIL;
}

// addEdge()
// inserts a new edge joining u to v
// u is added to adjacency List of v, and v to adjacency List of u
// precon: int arguments must be 1 to getOrder(G)
void addEdge(Graph G, int u, int v) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: calling addEdge() on Null graph\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
    fprintf(stderr, "Graph Error: calling addEdge() on incorrect arguments\n");
    exit(EXIT_FAILURE);
  }
  addArc(G, u, v);
  addArc(G, v, u); // just do add arc for u to v and v to u
  G->size--;       // decremet size, cuz we increase twice from arc
}

// addArc()
// inserts new directed edge from u to v
// v is added to adjacency List of u but not u to List of v
// precon: int arguments must be 1 to getOrder(G)
void addArc(Graph G, int u, int v) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: calling addArc() on Null graph\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
    fprintf(stderr, "Graph Error: calling addArc() on incorrect arguments\n");
    exit(EXIT_FAILURE);
  }
  moveFront(G->adj[u]);
  while (index(G->adj[u]) != -1 && get(G->adj[u]) < v) {
    moveNext(G->adj[u]); // while v is > than adj u just move on
  }
  if (index(G->adj[u]) == -1) {
    append(G->adj[u], v); // if empty then append v
  } else {
    insertBefore(G->adj[u], v); // else v > u insert before
  }
  G->size++; // incement size
}

// BFS()
// runs BFS algorithm, source s, setting color, dist, parent, source
// using bfs pseudo from prof and pseudo explanation from textbook bfs
void BFS(Graph G, int s) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: calling addArc() on Null graph\n");
    exit(EXIT_FAILURE);
  }
  G->source = s; // save s in source
  for (int x = 1; x <= getOrder(G); x++) {
    G->color[x] = 0; // color white
    G->dist[x] = INF;
    G->parent[x] = NIL;
  }
  G->color[s] = 1; // color gray, source discovered
  G->dist[s] = 0;
  G->parent[s] = NIL;
  List Q = newList(); // new list, "enqueue" s
  append(Q, s);
  while (length(Q) > 0) { // while list not empty
    int x =
        front(Q); // "dequeue" by saving front in x and then deleteing from list
    deleteFront(Q);
    for (moveFront(G->adj[x]); index(G->adj[x]) >= 0;
         moveNext(G->adj[x])) { // loop thru adj list starting at source
      int y = get(G->adj[x]);
      if (G->color[y] == 0) { // if y undiscovered
        G->color[y] = 1;      // discover y
        G->dist[y] = G->dist[x] + 1;
        G->parent[y] = x;
        append(Q, y); // "enqueue"
      }
    }
    G->color[x] = 2; // color black, finish x
  }
  freeList(&Q); // free list
}

// Other operations------------------------------------------------------
// printGraph()
// prints adjacency list rep of G to file pointed to by out
void printGraph(FILE *out, Graph G) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: calling printGraph() on Null graph\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i <= getOrder(G); i++) {
    fprintf(out, "%d: ", i); // loop thru size of graph and print each index
    moveFront(G->adj[i]);    // move to front of adj
    while (index(G->adj[i]) != NIL) {      // while adj  index isnt nil
      fprintf(out, "%d ", get(G->adj[i])); // print paths
      moveNext(G->adj[i]);                 // move to next
    }
    fprintf(out, "\n"); // print new line between each output
  }
}
