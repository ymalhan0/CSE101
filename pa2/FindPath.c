///////////////////////////////////
// Yukti Malhan
// ymalhan
// 2022 Winter CSE101 pa2
// FindPath.c
// Main file for Graph ADT
//////////////////////////////////////////

#include "Graph.h"
#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  // v1 = v2 = 1;
  fscanf(in, " %d", &v1);
  fscanf(in, " %d", &v2); // scan in first so that 0 0 isnt added

  // add edges till end of file
  while (v1 != 0 && v2 != 0) {
    addEdge(G, v1, v2);
    fscanf(in, " %d", &v1);
    fscanf(in, " %d", &v2);
  }
  printGraph(out, G); // print graph

  List L = newList(); // list for paths
  int s, d;

  // scan into sorce and destination, print accordingly
  while (fscanf(in, "%d %d", &s, &d) != EOF) {
    if (s == 0 && d == 0) {
      break;
    }
    BFS(G, s);
    getPath(L, G, d);
    // do bfs and get path, if length of L is 0 or distance is inf
    if (length(L) == 0 || getDist(G, d) == -2) {
      fprintf(
          out,
          "\nThe distance from %d to %d is infinity\nNo %d-%d path exists\n", s,
          d, s, d);
    } else {
      fprintf(out,
              "\nThe distance from %d to %d is %d\nA shortest %d-%d path is: ",
              s, d, getDist(G, d), s, d);
      printList(out, L);
      fprintf(out, "\n"); // print new line cuz apparently printlist doesnt
    }
    clear(L);
  }
  // clear and free everything, close files
  freeList(&L);
  freeGraph(&G);
  fclose(in);
  fclose(out);
}
