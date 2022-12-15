///////////////////////////////////
// Yukti Malhan
// ymalhan
// 2022 Winter CSE101 pa4
// ListTest.c
// Test file for List ADT
///////////////////////////////////////

#include "List.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

  List A = newList();
  for (int i = 1; i <= 10; i++) {
    append(A, &i);
  }
  fprintf(stderr, "length: %d\n", length(A));

  moveFront(A);
  printf("%d\n", index(A));

  moveBack(A);
  printf("%d\n", index(A));
  moveFront(A);
  get(A);
  moveBack(A);
  get(A);
  printf("%d\n", *(int *)front(A));
  printf("%d\n", *(int *)back(A));
  int i;
  moveFront(A);
  for (i = 0; i < 3; i++) {
    insertBefore(A, &i);
    insertAfter(A, &i);
  }
  printf("%d\n", *(int *)get(A));
  for (i = 0; i < 3; i++) {
    moveNext(A);
    movePrev(A);
  }
  printf("%d\n", *(int *)get(A));

  for (i = 0; i < 3; i++) {
    deleteFront(A);
    deleteBack(A);
  }
  delete (A);
  printf("%d\n", length(A));
  clear(A);
  printf("%d\n", length(A));
  freeList(&A);

  return (0);
}
