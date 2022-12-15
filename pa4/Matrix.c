///////////////////////////////////
// Yukti Malhan
// ymalhan
// 2022 Winter CSE101 pa4
// Matrix.c
// Implement Matrix ADT
///////////////////////////////////////

#include "Matrix.h"
#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// private entry type
typedef struct EntryObj *Entry;

// private EntryObj type
typedef struct EntryObj {
  int col;
  double value;
} EntryObj;

// private MatrixObj type
typedef struct MatrixObj {
  int size;
  int NNZ;
  List *entry;
} MatrixObj;

// Constructors-Destructors ------------------------------
// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n) {
  Matrix M = malloc(sizeof(MatrixObj)); // alocate matrix object
  M->size = n;                          // size n
  M->NNZ = 0;
  M->entry = malloc((n + 1) * sizeof(List));
  for (int i = 1; i <= n; i++) {
    M->entry[i] = newList(); // 2d array
  }
  return M;
}

// freeMatrix()
//  Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix *pM) {
  if (*pM != NULL && pM != NULL) {
    makeZero(*pM);
    for (int i = 1; i <= (*pM)->size; i++) {
      freeList(&(*pM)->entry[i]); // free all lists like how did in graph
      (*pM)->entry[i] = NULL;
    }
    free((*pM)->entry);
  }
  free(*pM);
  *pM = NULL;
}

// newEntry()
// returns ref to entry object
Entry newEntry(int col, double value) {
  Entry E = malloc(sizeof(EntryObj));
  E->col = col;
  E->value = value;
  return E;
}

// freeEntry()
// free entry object
void freeEntry(Entry *pE) {
  if (*pE != NULL && pE != NULL) {
    free(*pE);
    *pE = NULL;
  }
}

// Access functions -------------------------------------
// size()
// Return the size of square Matrix M.
int size(Matrix M) {
  if (M == NULL) {
    fprintf(stderr, "NULL Error: calling size() on null matrix\n"); // why
    exit(EXIT_FAILURE);
  }
  return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
  if (M == NULL) {
    fprintf(stderr, "NULL Error: calling NNZ() on null matrix\n");
    exit(EXIT_FAILURE);
  }
  return M->NNZ;
}

// equals() - use ta pseudo
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
  if (A == NULL || B == NULL) {
    fprintf(stderr, "NULL Error: calling equals() on null matrix\n");
    exit(EXIT_FAILURE);
  }
  if (A->size != B->size) {
    return 0; // if not same size then false
  }
  for (int i = 1; i <= size(A); i++) { // loop thru size of first matrix
    if (length(A->entry[i]) != length(B->entry[i])) {
      return 0; // if lengths of list not same then false
    }
    moveFront(A->entry[i]);
    moveFront(B->entry[i]);
    while (index(A->entry[i]) >= 0) {
      if (((Entry)get(A->entry[i]))->col != ((Entry)get(B->entry[i]))->col) {
        return 0; // if cols not same false
      }
      if (((Entry)get(A->entry[i]))->value !=
          ((Entry)get(B->entry[i]))->value) {
        return 0; // if vals not same false
      }
      moveNext(A->entry[i]);
      moveNext(B->entry[i]);
    }
  }
  return 1; // true if all is well :)
}

// Manipulation procedures --------------------------------
// using pseudo from ta eric's section with smol changes :)
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {
  if (M == NULL) {
    fprintf(stderr, "NULL Error: calling makeZero() on null matrix\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i <= size(M); i++) {
    // clear(M->entry[i]); - no work
    while (length(M->entry[i]) != 0) {
      free((front(M->entry[i]))); // free insetad of freeEntry?
      deleteFront(M->entry[i]);
    }
  }
  M->NNZ = 0;
}

// changeEntry() -- from eric ta section with edits
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
  if (M == NULL) {
    fprintf(stderr, "NULL Error: calling changeEntry() on null matrix\n");
    exit(EXIT_FAILURE);
  }
  List L = M->entry[i]; // keep getting null get from i
  Entry E;
  if (x != 0) {           // use erics pseudo
    if (length(L) == 0) { // if empty can just prepend for order
      prepend(L, newEntry(j, x));
      M->NNZ++; // increment
    } else {
      moveFront(L);
      while (index(L) > -1 && ((Entry)get(L))->col < j) {
        moveNext(L); // move next till col >= j to keep sorted
      }
      if (index(L) == -1) {
        append(L, newEntry(j, x));
        M->NNZ++; // add to end
      } else if (((Entry)get(L))->col == j) {
        ((Entry)get(L))->value = x; // just change that value
      } else {
        insertBefore(L, newEntry(j, x)); // if j < get then insert before
        M->NNZ++;
      }
    }
  } else { // what if x is 0?
    moveFront(L);
    while (index(L) > -1 && ((Entry)get(L))->col < j) {
      moveNext(L);
    } // keep order
    if (index(L) > -1) {
      E = (Entry)get(L);
      freeEntry(&E);
      delete (L); // delete free
      M->NNZ--;
    }
  }
  // freeEntry(&E);
}

// Matrix Arithmetic operations ------------------------------------
// copy() - used graph for inspo
// Returns a reference to a new Matrix object having the same entries as
// A.
Matrix copy(Matrix A) {
  if (A == NULL) {
    fprintf(stderr, "NULL Error: calling copy() on null matrix\n");
    exit(EXIT_FAILURE);
  }
  Entry E;
  Matrix C = newMatrix(A->size);
  for (int i = 1; i <= size(A); i++) {
    List c = C->entry[i]; // am lazy
    List a = A->entry[i];
    // if (length(a) != 0) {
    for (moveFront(a); index(a) >= 0;
         moveNext(a)) { // loop and change each entry in C to A
      // changeEntry(C, i, ((Entry)get(a))->col,
      //  ((Entry)get(a))->value);
      E = (Entry)get(a);
      append(c, newEntry(E->col, E->value)); // append to entry list
      // changeEntry(C, i, E->col, E->value);
      //}
    }
  }

  C->NNZ = A->NNZ;
  C->size = A->size;
  return C;
}

// transpose()
// Returns a reference of A.
Matrix transpose(Matrix A) {
  if (A == NULL) {
    fprintf(stderr, "NULL Error: calling transpose() on null matrix\n");
    exit(EXIT_FAILURE);
  }
  Entry E;
  Matrix T = newMatrix(A->size);
  for (int i = 1; i <= size(A); i++) {
    // List t = T->entry[i];
    List a = A->entry[i];
    for (moveFront(a); index(a) >= 0; moveNext(a)) {
      // changeEntry(T, ((Entry)get(A->entry[i]))->col, i,
      //  ((Entry)get(A->entry[i]))->value);
      E = (Entry)get(a);
      List t = T->entry[E->col]; // like copy but diff order
      append(t, newEntry(i, E->value));
    }
  }
  T->NNZ = A->NNZ;
  return T;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
  if (A == NULL) {
    fprintf(stderr, "NULL Error: calling scalarMult() on null matrix\n");
    exit(EXIT_FAILURE);
  }
  Matrix S = copy(A);
  if (x != 0) {
    for (int i = 1; i <= size(A); i++) {
      for (moveFront(S->entry[i]); index(S->entry[i]) >= 0;
           moveNext(S->entry[i])) {
        ((Entry)get(S->entry[i]))->value *= x; // loop thru and multiply

        // double mult = x * ((Entry)get(A->entry[i]))->value;
        // changeEntry(S, i, ((Entry)get(A->entry[i]))->col, mult);
      }
    }
  } else {
    makeZero(S); // if 0 makezero does same ting
  }
  return S;
}

// used pseudo from ta eric's section with changes
// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
  if (A == NULL || B == NULL) {
    fprintf(stderr, "NULL Error: calling sum() on null matrix\n");
    exit(EXIT_FAILURE);
  }
  if (size(A) != size(B)) {
    return 0;
  }
  if (A == B) { // if same matrix can just mult by 2
    return scalarMult(2, A);
  }
  Matrix S = newMatrix(A->size);
  List s;
  for (int i = 1; i <= size(S); i++) {
    s = S->entry[i];
    moveFront(A->entry[i]);
    moveFront(B->entry[i]);
    while (index(A->entry[i]) >= 0 && index(B->entry[i]) >= 0) {
      //    for (moveFront(A->entry[i]); index(A->entry[i]) >= 0;
      //         moveNext(A->entry[i])) {
      Entry a = (Entry)get(A->entry[i]);
      Entry b = (Entry)get(B->entry[i]);
      // for (moveFront(B->entry[i]); index(B->entry[i]) >= 0;
      //     moveNext(B->entry[i])) {
      if (b->col > a->col) {
        append(s, newEntry(a->col, a->value)); // from pseudo
        S->NNZ++;
        moveNext(A->entry[i]);
      } else if (b->col < a->col) {
        append(s, newEntry(b->col, b->value)); // use append insted of change
        S->NNZ++;
        moveNext(A->entry[i]);
      } else {
        if (a->value + b->value != 0) {
          append(s, newEntry(a->col, a->value + b->value));
          S->NNZ++;
        }
        moveNext(A->entry[i]);
        moveNext(B->entry[i]);
      }
    }
    while (index(A->entry[i]) >= 0) { // if ones index is -1, same as ifs
      Entry a = (Entry)get(A->entry[i]);
      append(s, newEntry(a->col, a->value));
      S->NNZ++;
      moveNext(A->entry[i]);
    }
    while (index(B->entry[i]) >= 0) {
      Entry b = (Entry)get(B->entry[i]);
      append(s, newEntry(b->col, b->value));
      S->NNZ++;
      moveNext(B->entry[i]);
    }
  }
  return S;
}

// diff()
// Returns a reference to a new Matrix rep A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
  if (A == NULL || B == NULL) {
    fprintf(stderr, "NULL Error: calling diff() on null matrix\n");
    exit(EXIT_FAILURE);
  }
  if (size(A) != size(B)) {
    return 0;
  }
  Matrix m1 = copy(B);              // copy
  Matrix m2 = scalarMult(-1.0, m1); // mult by -1
  Matrix m3 = sum(A, m2);           // add em
  freeMatrix(&m1);
  freeMatrix(&m2);
  return m3;
}

// dot()
// helper for product
double dot(List A, List BT) {
  if (A == NULL || BT == NULL) {
    return 0.0;
  }
  double prod = 0.0;
  moveFront(A);
  moveFront(BT);
  // while (get(A->entry[v1]) != NULL && get(BT->entry[v2]) != NULL) {
  // for (int i = 0; i < length(A); i++) {
  // if (index(A) != -1 && index(BT) != -1) {

  while (index(A) >= 0 && index(BT) >= 0) {
    Entry EA = (Entry)get(A);
    Entry EBT = (Entry)get(BT);
    if (EA->col == EBT->col) { // if cols equal then mult em
      prod += EA->value * EBT->value;
      moveNext(A);
      moveNext(BT);
    } else if (EA->col > EBT->col) {
      moveNext(BT); // move next transpose
    } else if (EA->col < EBT->col) {
      moveNext(A); // move next a
    }
  }
  return prod;
}

// product() -- from eric ta section with edits
// Returns a reference to a new Matrix rep AB.
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
  if (A == NULL || B == NULL) {
    fprintf(stderr, "NULL Error: calling product() on null matrix\n");
    exit(EXIT_FAILURE);
  }
  if (size(A) != size(B)) {
    return 0;
  }
  Matrix P = newMatrix(A->size);
  if (A->NNZ == 0 || B->NNZ == 0) {
    return P;
  }
  List p; // all from pseudo
  Matrix BT = transpose(B);
  for (int i = 1; i <= A->size; i++) {
    p = P->entry[i];
    if (length(A->entry[i]) > 0) {
      for (int k = 1; k <= BT->size; k++) {
        if (length(BT->entry[k]) > 0) {
          if (dot(A->entry[i], BT->entry[k]) != 0) {
            // printf("%f\n", dot(A->entry[i], BT->entry[k]));
            // changeEntry(P, i, k, dot(A->entry[i], BT->entry[k]));
            append(p, newEntry(k, dot(A->entry[i], BT->entry[k])));
            P->NNZ++;
          }
        }
      }
    }
  }
  freeMatrix(&BT);
  return P;
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero
// rows
// are not printed. Each non-zero row is represented as one line
// consisting of the row number, followed by a colon, a space, then a
// space separated list of pairs "(col, val)" giving the column numbers
// and non-zero values in that row. The double val will be rounded to 1
// decimal point.
void printMatrix(FILE *out, Matrix M) {
  if (M == NULL) {
    fprintf(stderr, "NULL Error: calling scalarMult() on null matrix\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i <= size(M); i++) {
    if (length(M->entry[i]) > 0) { // make sure zero rows not printed
      fprintf(out, "%d:", i);
      for (moveFront(M->entry[i]); index(M->entry[i]) >= 0;
           moveNext(M->entry[i])) {
        fprintf(out, " (%d, %0.1f)", ((Entry)get(M->entry[i]))->col,
                ((Entry)get(M->entry[i]))->value);
      }
      fprintf(out, "\n");
    }
  }
}
