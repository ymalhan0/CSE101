///////////////////////////////////
// Yukti Malhan
// ymalhan
// 2022 Winter CSE101 pa3
// Graph.c
// Implementation file for Graph ADT
//////////////////////////////////////////

#include "Graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// private Graph object

typedef struct GraphObj {
  List *adj;
  int *color;
  int *parent;
  int *disc;
  int *fin;
  int order;
  int size;
  // int source;
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
  G->disc = malloc(sizeof(int) * (n + 1));
  G->fin = malloc(sizeof(int) * (n + 1));
  G->order = n; // number of vertices is n
  G->size = 0;  // empty edges
                // G->source = NIL; // NIL if BFS not called yet
  for (int i = 1; i <= n; i++) {
    G->adj[i] = newList(); // we loop through to create list indicies 1 to n
    G->parent[i] = NIL;    // nil if bfs not yet called
    G->disc[i] = UNDEF;
    G->fin[i] = UNDEF;
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
    free((*pG)->color); // free color, parent, times
    free((*pG)->disc);
    free((*pG)->fin);
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

// getDiscover()
// returns discover time
// precon: 1 <= u <= getOrder(G)
int getDiscover(Graph G, int u) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: calling getParent() on NULL graph\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > getOrder(G)) {
    return 0;
  } // exit if fail precon
  if (G->disc[u] == UNDEF) {
    return UNDEF;
  } else {
    return G->disc[u];
  } // return discovery time
}

// getFinish()
// returns finish time
// precon: 1 <= u <= getOrder(G)
int getFinish(Graph G, int u) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: calling getParent() on NULL graph\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > getOrder(G)) {
    return 0;
  } // exit if fail precon
  if (G->fin[u] == UNDEF) {
    return UNDEF;
  } else {
    return G->fin[u];
  } // return finish time
}

// Manipulation procedures---------------------------------------------------
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

// Visit()
// dfs helper, using professor pseudo but adding use of list
void Visit(Graph G, List S, int x, int *time) {
  G->disc[x] = ++(*time); // increment time
  G->color[x] = 1;        // set to gray, discover x
  int y;
  for (moveFront(G->adj[x]); index(G->adj[x]) >= 0; moveNext(G->adj[x])) {
    y = get(G->adj[x]);     // loop through all in adj[x]
    if (G->color[y] == 0) { // if white
      G->parent[y] = x;     // parent now x
      Visit(G, S, y, time); // recursion
    }
  }
  G->color[x] = 2; // finish x
  G->fin[x] = ++(*time);
  prepend(S, x); // save value in list
}

// DFS()
// runs dfs
// Pre: length(S)==getOrder(G)
// using professor pseudo but adding use of list to save values
void DFS(Graph G, List S) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: calling DFS() on Null graph\n");
    exit(EXIT_FAILURE);
  }
  if (length(S) != getOrder(G)) {
    return;
  }
  List L = copyList(S);
  clear(S); // copy S and clear, use copied for loop and S to call on
  int time = 0;
  for (moveFront(L); index(L) >= 0; moveNext(L)) { // for all x in V(G)
    int x = get(L);
    G->color[x] = 0;    // white
    G->parent[x] = NIL; // parent nil
    G->disc[x] = UNDEF;
    G->fin[x] = UNDEF;
  }
  for (moveFront(L); index(L) >= 0; moveNext(L)) { // main loop of DFS
    int x = get(L);
    if (G->color[x] == 0) {  // if white
      Visit(G, S, x, &time); // call visit
    }
    //   moveNext(L);
  }
  freeList(&L); // free L at end
}

// Other operations ----------------------------------------
// transpose()
// returns reference to a new graph object representing transpose of G
Graph transpose(Graph G) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: calling transpose() on Null graph\n");
    exit(EXIT_FAILURE);
  }
  Graph T = newGraph(G->order);         // new graph T of order
  for (int i = 1; i <= G->order; i++) { // 1 to n
    moveFront(G->adj[i]);               // move to front
    while (index(G->adj[i]) >= 0) {     // while index
      addArc(T, get(G->adj[i]), i);     // add arc to t, but flipped
      moveNext(G->adj[i]);              // move next
    }
  }
  T->size = G->size; // copy in size
  return T;
}

// copyGraph()
// returns reference to a new graph that is copy of G
Graph copyGraph(Graph G) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: calling copyGraph() on Null graph\n");
    exit(EXIT_FAILURE);
  }
  Graph C = newGraph(G->order);
  for (int i = 1; i <= getOrder(G); i++) {
    moveFront(G->adj[i]);
    while (index(G->adj[i]) != -1) {
      addArc(C, i, get(G->adj[i])); // basically transpose but change order of adding arc
      moveNext(G->adj[i]);
    }
  }
  C->size = G->size;
  return C;
}

// printGraph()
// prints adj list of G to file pointed by out
void printGraph(FILE *out, Graph G) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: calling printGraph() on Null graph\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i <= getOrder(G); i++) {
    fprintf(out, "\n%d: ", i); // loop thru size of graph and print each index
    moveFront(G->adj[i]);      // move to front of adj
    while (index(G->adj[i]) >= 0) {        // while adj  index isnt nil
      fprintf(out, "%d ", get(G->adj[i])); // print paths
      moveNext(G->adj[i]);                 // move to next
    }
  }
  fprintf(out, "\n"); // print new line between each output
}
