///////////////////////////////////
// Yukti Malhan
// ymalhan
// 2022 Winter CSE101 pa2
// GraphTest.c
// Test Client for Graph ADT
///////////////////////////////////

#include "Graph.h"

int main() {
  Graph G = newGraph(5);
  // printf("\ncleared\n\n");
  // printGraph(stdout, G);
  addEdge(G, 1, 2);
  addEdge(G, 2, 3);
  addEdge(G, 2, 4);
  addEdge(G, 4, 5);
  addEdge(G, 1, 4);
  // printf("\n\nwith edges\n\n");
  // printGraph(stdout, G);

  makeNull(G);
  // printGraph(stdout, G);

  addArc(G, 1, 2);
  addArc(G, 2, 3);
  addArc(G, 2, 4);
  addArc(G, 4, 5);
  addArc(G, 1, 4);
  printGraph(stdout, G);

  List L = newList();
  BFS(G, 4);
  // printf("distance 1 to 4: %d\n", getDist(G, 1));
  // printf("shortest path 1 to 4 is: ");
  getPath(L, G, 1);
  // printList(stdout, L);
  clear(L);

  printf("\n");

  makeNull(G);
  addEdge(G, 1, 2);
  addEdge(G, 2, 3);
  addEdge(G, 2, 4);
  addEdge(G, 4, 5);
  addEdge(G, 1, 4);
  BFS(G, 4);
  printf("distance 1 to 4: %d\n", getDist(G, 1));
  printf("shortest path 1 to 4 is: ");
  getPath(L, G, 1);
  printList(stdout, L);
  printf("\n");
  clear(L);

  freeGraph(&G);

  Graph D = newGraph(10);
  Graph U = newGraph(10);

  for (int i = 1; i < 11; i += 2) {
    for (int j = 5; j < 9; j++) {
      addEdge(U, i, j);
      addArc(D, i, j);
    }
  }
  BFS(D, 3);
  BFS(U, 3);
  printf("order d: %d\n", getOrder(D));
  printf("order u: %d\n", getOrder(U));
  printf("size d: %d\n", getSize(D));
  printf("size u: %d\n", getSize(U));
  printf("source d: %d\n", getSource(D));
  printf("source u: %d\n", getSource(U));
  printf("parent d: %d\n", getParent(D, 3));
  printf("parent u: %d\n", getParent(U, 8));
  getPath(L, D, 4);
  getPath(L, U, 5);
  printList(stdout, L);
  printf("\n");
  printGraph(stdout, D);
  printGraph(stdout, U);
  freeGraph(&D);
  freeGraph(&U);
  freeList(&L);
}
