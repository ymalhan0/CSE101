///////////////////////////////////
// Yukti Malhan
// ymalhan
// 2022 Winter CSE101 pa4
// MatrixTest.c
// Test file for Matrix ADT
///////////////////////////////////////

#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  /*Matrix A = newMatrix(3);
  changeEntry(A, 1, 1, 1);
  changeEntry(A, 1, 2, 2);
  changeEntry(A, 1, 3, 3);
  changeEntry(A, 2, 1, 4);
  changeEntry(A, 2, 2, 5);
  changeEntry(A, 2, 3, 6);
  changeEntry(A, 3, 1, 7);
  changeEntry(A, 3, 2, 8);
  changeEntry(A, 3, 3, 9);
  printMatrix(stdout, A);
  fprintf(stdout, "\n");
  Matrix C = scalarMult(2, A);
  printMatrix(stdout, C);
  printf("%d\n", NNZ(C));
  freeMatrix(&A);
  freeMatrix(&C);*/
  // Matrix C = scalarMult(2,A);
  // printMatrix(stdout, C);
  // 	printf("\n");
  //	freeMatrix(&C);
  int n = 3;
  Matrix A = newMatrix(n);
  Matrix B = newMatrix(n);

  changeEntry(A, 1, 1, 1);
  changeEntry(B, 1, 1, 1);
  changeEntry(A, 1, 2, 2);
  changeEntry(B, 1, 2, 0);
  changeEntry(A, 1, 3, 3);
  changeEntry(B, 1, 3, 1);
  changeEntry(A, 2, 1, 4);
  changeEntry(B, 2, 1, 0);
  changeEntry(A, 2, 2, 5);
  changeEntry(B, 2, 2, 1);
  changeEntry(A, 2, 3, 6);
  changeEntry(B, 2, 3, 0);
  changeEntry(A, 3, 1, 7);
  changeEntry(B, 3, 1, 1);
  changeEntry(A, 3, 2, 8);
  changeEntry(B, 3, 2, 1);
  changeEntry(A, 3, 3, 9);
  changeEntry(B, 3, 3, 1);

  printf("%d\n", NNZ(A));
  printMatrix(stdout, A);
  printf("\n");
  Matrix G = product(B, B);
  // Matrix G = copy(A);
  printf("%d\n", NNZ(G));
  printMatrix(stdout, G);
  printf("\n");

  /* Matrix F = transpose(A);
   printf("%d\n", NNZ(F));
   printMatrix(stdout, F);
   printf("\n");
   return 0;
 */
  /* Matrix D;

   D = sum(A, A);
   printf("%d\n", NNZ(D));
   printMatrix(stdout, D);
   printf("\n");
   freeMatrix(&D);

   Matrix E, N;

   N = diff(A, A);
   printf("%d\n", NNZ(N));
   printMatrix(stdout, N);
   printf("\n");
   freeMatrix(&N);

   E = product(A, A);
   printf("%d\n", NNZ(E));
   printMatrix(stdout, E);
   printf("\n");
   freeMatrix(&E);
 */
}
