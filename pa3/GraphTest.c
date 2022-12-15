///////////////////////////////////
// Yukti Malhan
// ymalhan
// 2022 Winter CSE101 pa3
// GraphTest.c
// Test Client for Graph ADT
///////////////////////////////////

#include "Graph.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  Graph G = newGraph(9);
  List L = newList();

  for (int i = 1; i <= 9; i++)
    append(L, i);

  addArc(G, 1, 2);
  addArc(G, 1, 5);
  addArc(G, 2, 5);
  addArc(G, 2, 6);
  addArc(G, 3, 2);
  addArc(G, 3, 4);
  addArc(G, 3, 6);
  addArc(G, 3, 7);
  addArc(G, 3, 8);
  addArc(G, 6, 5);
  addArc(G, 6, 7);
  addArc(G, 8, 4);
  addArc(G, 8, 7);
  addArc(G, 8, 5);
  printGraph(stdout, G);
 // printf("order: %d\n", getOrder(G));
 // printf("size: %d\n", getSize(G));
//  printf("parent: %d\n", getParent(G, 6));
//  printf("discover: %d\n", getDiscover(G, 6));
//  printf("finish: %d\n", getFinish(G, 6));
  
Graph H = copyGraph(G);
printGraph(stdout, H);
freeGraph(&G);
  freeList(&L);
}
