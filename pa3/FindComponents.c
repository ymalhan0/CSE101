///////////////////////////////////
// Yukti Malhan
// ymalhan
// 2022 Winter CSE101 pa3
// FindComponents.c
// Main file for Graph ADT
//////////////////////////////////

#include "Graph.h"
#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// cite ta arka for scc part

int main(int argc, char *argv[]) {

  FILE *in, *out;
  // check command line for correct number of arguments
  if (argc != 3) {
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }

  // open files for reading and writing
  in = fopen(argv[1], "r");
  if (in == NULL) {
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }

  out = fopen(argv[2], "w");
  if (out == NULL) {
    printf("Unable to open file %s for writing\n", argv[2]);
    exit(1);
  }

  int size = 0;
  fscanf(in, " %d", &size); // scan size of graph
  Graph G = newGraph(size); // make a new graph of size

  int v1, v2; // vertices
  fscanf(in, " %d", &v1);
  fscanf(in, " %d", &v2); // scan in first so that 0 0 isnt added
                          // add edges till end of file
  while (v1 != 0 && v2 != 0) {
    addArc(G, v1, v2);
    fscanf(in, " %d", &v1);
    fscanf(in, " %d", &v2);
  }

  fprintf(out, "Adjacency list representation of G:\n");
  printGraph(out, G); // print graph
  // fprintf(out, "\n");
  List S = newList();
  Graph T = transpose(G); // transpose of G
  for (int i = 1; i <= getOrder(G); i++) {
    append(S, i); // append to list
    DFS(G, S);    // dfs on G and G^T
    DFS(T, S);
  }
  int count = 0;
  int count2 = 0;
  List L = newList(); // another list for connected comps
  for (moveFront(S); index(S) >= 0; moveNext(S)) {
    if (getParent(T, get(S)) == NIL) { // increment counter, for how many comps
      count++;
    }
  }
  fprintf(out, "G contains %d strongly connected components:\n", count);
  for (moveBack(S); index(S) != -1; movePrev(S)) {
    if (getParent(T, get(S)) == NIL) {
      prepend(L, get(S)); // if end then add and print, then clear
      count2++;
      fprintf(out, "Component %d: ", count2);
      printList(out, L);
      fprintf(out, "\n");
      clear(L);
    } else if (getParent(T, get(S)) != NIL) {
      prepend(L, get(S)); // else keep adding in order
    }
  }
  // free and close
  freeGraph(&T);
  freeGraph(&G);
  freeList(&L);
  freeList(&S);
  fclose(in);
  fclose(out);
}
