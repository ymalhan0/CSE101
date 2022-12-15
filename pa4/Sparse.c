///////////////////////////////////
// Yukti Malhan
// ymalhan
// 2022 Winter CSE101 pa4
// Sparse.c
// Main file for Matrix ADT
/////////////////////////////////////

#include "List.h"
#include "Matrix.h"
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
  Matrix A = newMatrix(size);
  Matrix B = newMatrix(size);
  int v1, v2;
  fscanf(in, " %d", &v1);
  fscanf(in, " %d", &v2); // scan in first so that 0 0 isnt added
  int row, col;
  double value;
  for (int i = 1; i <= v1; i++) {
    fscanf(in, " %d", &row);
    fscanf(in, " %d", &col);
    fscanf(in, " %lf", &value);
    changeEntry(A, row, col, value);
  }
  for (int i = 1; i <= v2; i++) {
    fscanf(in, " %d", &row);
    fscanf(in, " %d", &col);
    fscanf(in, " %lf", &value);
    changeEntry(B, row, col, value);
  }

  // printing time
  // non zero entries for A
  fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
  printMatrix(out, A);
  fprintf(out, "\n");

  // non zero for B
  fprintf(out, "B has %d non-zero entries:\n", NNZ(B));
  printMatrix(out, B);
  fprintf(out, "\n");

  // scalar mult by 1.5 on A
  Matrix Scale = scalarMult(1.5, A);
  fprintf(out, "(1.5)*A =\n");
  printMatrix(out, Scale);
  fprintf(out, "\n");
  freeMatrix(&Scale);

  // A + B
  Matrix S1 = sum(A, B);
  fprintf(out, "A+B =\n");
  printMatrix(out, S1);
  fprintf(out, "\n");
  freeMatrix(&S1);

  // A + A
  Matrix S2 = sum(A, A);
  fprintf(out, "A+A =\n");
  printMatrix(out, S2);
  fprintf(out, "\n");
  freeMatrix(&S2);

  // B - A
  Matrix D1 = diff(B, A);
  fprintf(out, "B-A =\n");
  printMatrix(out, D1);
  fprintf(out, "\n");
  freeMatrix(&D1);

  // A - A
  Matrix D2 = diff(A, A);
  fprintf(out, "A-A =\n");
  printMatrix(out, D2);
  fprintf(out, "\n");
  freeMatrix(&D2);

  // Transpose A
  Matrix T = transpose(A);
  fprintf(out, "Transpose(A) =\n");
  printMatrix(out, T);
  fprintf(out, "\n");
  freeMatrix(&T);

  // A * B
  Matrix P1 = product(A, B);
  fprintf(out, "A*B =\n");
  printMatrix(out, P1);
  fprintf(out, "\n");
  freeMatrix(&P1);

  // B * B
  Matrix P2 = product(B, B);
  fprintf(out, "B*B =\n");
  printMatrix(out, P2);
  fprintf(out, "\n");
  freeMatrix(&P2);

  freeMatrix(&A);
  freeMatrix(&B);
  fclose(in);
  fclose(out);
}
