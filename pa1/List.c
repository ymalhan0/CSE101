///////////////////////////////////
// Yukti Malhan
// ymalhan
// 2022 Winter CSE101 pa1
// List.c
// Implementation functions for List ADT
//////////////////////////////////////
#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// structs -------------------------------------------------------
// private Node type
typedef struct NodeObj *Node;

// private NodeObj type
typedef struct NodeObj {
  int data;
  Node prev;
  Node next;
} NodeObj;

// private ListObj type
typedef struct ListObj {
  Node front;
  Node back;
  int length;
  int index;   // cursor position
  Node cursor; // cursor
} ListObj;

// Constructors-Destructors --------------------------------------
// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(int data) {
  Node N = malloc(sizeof(NodeObj));
  N->data = data;
  N->prev = NULL;
  N->next = NULL; // also need a prev cuz double linked list
  return (N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node *pN) {
  if (pN != NULL && *pN != NULL) {
    free(*pN);
    *pN = NULL;
  }
} // from queue

// newList()
// Creates and returns a new empty List.
List newList() {
  List L;
  L = malloc(sizeof(ListObj));
  L->front = L->back = NULL; // front and back
  L->length = 0;
  L->index = -1;
  L->cursor = NULL;
  return (L);
}

// freeList()
// Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List *pL) {
  if (pL != NULL && *pL != NULL) {
    while (length(*pL) != 0) { // while length not 0, delete
      deleteFront(*pL);
    }
    free(*pL); // free and set to null
    *pL = NULL;
  }
}

// Access functions--------------------------------------------------------
// length()
// Returns the number of elements in L.
int length(List L) {
  if (L == NULL) {
    fprintf(stderr, "List Error: calling length() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  return (L->length);
}

// front()
// Returns front element of L. Pre: length()>0
int front(List L) {
  if (L == NULL) {
    fprintf(stderr, "List Error: calling front() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->length == 0) {
    fprintf(stderr, "List Error: calling front() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  return (L->front->data);
}

// back()
// Returns back element of L. Pre: length()>0
int back(List L) {
  if (L == NULL) {
    fprintf(stderr, "List Error: calling back() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->length == 0) {
    fprintf(stderr, "List Error: calling back() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  return (L->back->data);
}

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L) {
  if (L == NULL) {
    fprintf(stderr, "List Error: calling index() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->cursor == NULL) {
    return -1;
  }
  return L->index;
}

// get()
// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L) {
  if (L == NULL) { // check if list is null
    fprintf(stderr, "List Error: calling get() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->cursor == NULL) { // check if cursor is null
    fprintf(stderr, "List Error: calling get() on NULL cursor\n");
    exit(EXIT_FAILURE);
  }
  if (L->length == 0) { // check length is > 0
    fprintf(stderr, "List Error: calling get() on List length < 0\n");
    exit(EXIT_FAILURE);
  }
  if (L->index < 0) { // check index is >= 0
    fprintf(stderr, "List Error: calling get() on List index < 0\n");
    exit(EXIT_FAILURE);
  }
  return L->cursor->data;
}

// equals()
// Returns true iff Lists A and B are in same state, and returns false
// otherwise.
bool equals(List A, List B) {
  int eq = 0;
  Node N = NULL;
  Node M = NULL;
  if (A == NULL || B == NULL) {
    fprintf(stderr,
            "List Error: calling equals() when one or more list are NULL\n");
    exit(EXIT_FAILURE);
  }
  eq = (A->length == B->length); // gets true or false based on list lengths
  N = A->front;                  // go to head of each list
  M = B->front;
  while (eq && N != NULL) {
    eq = (N->data == M->data); // check if each value same
    N = N->next;
    M = M->next; // if eq is false, loop wont run and false would be returned
  }
  return eq;
}

// Manipulation procedures -----------------------------------------------------
// clear()
// Resets L to its original empty state
void clear(List L) {
  if (L == NULL) {
    fprintf(stderr, "List Error: calling clear() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  while (L->length > 0) { // delete to free nodes
    deleteFront(L);
  }
  L->index = -1; // reset to original state
  L->front = L->back = L->cursor = NULL;
  L->length = 0;
}

// set()
// Overwrites the cursor element’s data with x. Pre:
// length()>0, index()>=0
void set(List L, int x) {
  if (L == NULL) {
    fprintf(stderr, "List Error: calling set() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->length <= 0) {
    fprintf(stderr, "List Error: calling set() on list length <= 0\n");
    exit(EXIT_FAILURE);
  }
  if (L->index < 0) {
    fprintf(stderr, "List Error, calling set() on index < 0\n");
    exit(EXIT_FAILURE);
  }
  L->cursor->data = x;
}

// moveFront()
// If L is non-empty, sets cursor under the front
// element, otherwise does nothing.
void moveFront(List L) {
  if (L == NULL) {
    fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->length == 0) {
    return;
  }
  L->cursor = L->front;
  L->index = 0;
}

// moveBack()
// If L is non-empty, sets cursor under the back element, or do nothing
void moveBack(List L) {
  if (L == NULL) {
    fprintf(stderr, "List Error: calling moveBack() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->length == 0) {
    return;
  }
  L->index = L->length - 1; // pos of last element in list
  L->cursor = L->back;
}

// movePrev()
// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined
// and at front, cursor becomes undefined;
// is undefined do nothing
void movePrev(List L) {
  if (L == NULL) {
    fprintf(stderr, "List Error: calling movePrev() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->cursor != NULL && L->cursor == L->front) { // if defined and at front
    L->cursor = NULL;                               // cursor becomes undefined
    L->index = -1;
  }
  if (L->cursor != NULL && L->cursor != L->front) { // if defined and not front
    L->cursor = L->cursor->prev;
    L->index--;
  }
}

// moveNext()
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and
// at // back, cursor becomes undefined; if cursor is
// undefined // do nothing
void moveNext(List L) {
  if (L == NULL) {
    fprintf(stderr, "List Error: calling movePrev() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->cursor != NULL && L->cursor == L->back) { // if def and back
    L->cursor = NULL;
    L->index = -1;
  }
  if (L->cursor != NULL && L->cursor != L->back) { // if def and not back
    L->cursor = L->cursor->next;
    L->index++;
  }
}

// prepend()
// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, int x) {
  if (L == NULL) {
    fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  Node save = newNode(x); // temporary save
  if (L->length == 0) {   // if empty add in new node for element
    L->front = L->back = save;
    // L->index++;
    L->length++;

  } else if (L->length >= 1) {
    save->next = L->front; // x is front of list
    L->front->prev = save; // old fronts prev is x
    L->front = save;       // front is now x
    if (L->cursor != NULL) {
      L->index++; // increment index
    }
    L->length++;
  }
}

// append()
// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, int x) {
  if (L == NULL) {
    fprintf(stderr, "List Error: calling append() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  // kinda like enqueue from queue.c
  Node save = newNode(x);
  if (L->length == 0) { // if empty add in new node for element
    L->front = L->back = save;
    // L->index = 0;
    L->length++;
  } else if (L->length >= 1) {
    save->prev = L->back; // link x in
    L->back->next = save;
    L->back = save;
    L->length++;
  }
}

// insertBefore()
// Insert new element before cursor. // Pre: length()>0, index()>=0
void insertBefore(List L, int x) {
  if (L == NULL) {
    fprintf(stderr,
            "List Error: calling insertBefore() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->length == 0) {
    fprintf(stderr, "List Error: calling insertBefore() on empty list\n");
    exit(EXIT_FAILURE);
  }
  if (L->index < 0) {
    fprintf(stderr, "List Error: calling insertBefore() on index -1\n");
    exit(EXIT_FAILURE);
  }
  if (L->cursor != NULL) {
    Node N = newNode(x);
    // Node save = L->cursor->prev;
    N->prev = L->cursor->prev; // insert new node
    L->cursor->prev = N;
    N->next = L->cursor;
    if (L->cursor == L->front) { // if cursor was front, new is now front
      L->front = N;
    } else if (N->prev != NULL && L->cursor != L->front) {
      N->prev->next = N; // else N is after cursor's prev
    }
    L->index++;
    L->length++;
  }
}

// insertAfter()
// Insert new element after cursor. // Pre: length()>0, index()>=0
void insertAfter(List L, int x) {
  if (L == NULL) {
    fprintf(stderr, "List Error: calling insertAfter on NULL List\n");
    exit(EXIT_FAILURE);
  }
  if (L->cursor == NULL) {
    // fprintf(stderr, "List Error: calling insertAfter() on NULL cursor\n");
    // exit(EXIT_FAILURE);
    return;
  }
  if (L->length <= 0) {
    fprintf(stderr, "List Error: calling insertAfter() on empty list\n");
    exit(EXIT_FAILURE);
  }
  if (L->index < 0) {
    fprintf(stderr, "List Error: calling insertAfter() on index -1\n");
    exit(EXIT_FAILURE);
  }
  Node save = newNode(x);
  if (L->cursor == L->back) {
    save->prev = L->back; // if inserting after back, x will become new back
    L->back->next = save;
    L->back = save;
    L->length++; // index will stay the same
  } else {
    save->next =
        L->cursor->next; // else x will become cursor next & cursor next prev x
    save->prev = L->cursor;
    L->cursor->next->prev = save;
    L->cursor->next = save;
    L->length++;
  }
}

// deleteFront()
// Delete the front element. Pre: length()>0
void deleteFront(List L) {
  if (L == NULL) {
    fprintf(stderr, "List Error: calling deleteFront on NULL List\n");
    exit(EXIT_FAILURE);
  }
  if (L->length == 0) {
    return;
  }
  // using dequque() from Queue.c
  Node N = NULL;
  if (L->length > 1) {
    N = L->front;              // save front
    L->front = L->front->next; // front is front->next
    freeNode(&N);              // free N
    L->front->prev = NULL;     // front prev is null
    if (L->cursor != NULL) {
      L->index--; // decrement index if cursor defined
    } else if (L->index == 0) {
      L->cursor = NULL; // otherwise cursor undefined
      L->index = -1;
    }
  } else if (L->length == 1) {
    freeNode(&L->front);                   // free front
    L->front = L->back = L->cursor = NULL; // set everything to empty state
    L->index = -1;
  }
  L->length--;
}

// deleteBack()
// Delete the back element. Pre: length()>0
void deleteBack(List L) {
  if (L == NULL) {
    fprintf(stderr, "List Error: calling deleteBack on NULL List\n");
    exit(EXIT_FAILURE);
  }
  if (L->length == 0) {
    return;
  }
  // using dequque() from Queue.c
  Node N = NULL;
  if (L->length > 1) {
    N = L->back;
    if (L->cursor == L->back) {
      L->cursor = NULL; // if cursor is back then undef it
      L->index = -1;
    }
    L->back = L->back->prev; // back is old back's prev
    freeNode(&N);            // free temp node
    L->back->next = NULL;    // back next is null
    L->length--;
  } else if (L->length == 1) {
    freeNode(&L->front); // free front
    L->back = L->front = L->cursor = NULL;
    L->index = -1;
    L->length = 0;
  }
  // L->length--;
}

// delete()
// Delete cursor element, making cursor undefined. Pre:
// length()>0, index()>=0
void delete (List L) {
  if (L == NULL) {
    fprintf(stderr, "List Error: calling delete on NULL List\n");
    exit(EXIT_FAILURE);
  }
  if (L->cursor == NULL) {
    return;
  }
  if (L->length == 0) {
    return;
  }
  if (L->index == -1) {
    return;
  }
  if (L->length == 1) {
    freeNode(&L->front); // if length 1, free front and set back/front to null
    L->front = L->back = NULL;
  } else if (L->front ==
             L->cursor) { // if cursor is on front, set to next and free
    L->front = L->front->next;
    freeNode(&L->cursor);
    L->front->prev = NULL;
  } else if (L->back == L->cursor) { // if back, delete and free
    L->back = L->back->prev;
    freeNode(&L->cursor);
    L->back->next = NULL;
  } else { // otherwise link the prev and next together and free cursor
    L->cursor->prev->next = L->cursor->next;
    L->cursor->next->prev = L->cursor->prev;
    freeNode(&L->cursor);
  }
  L->index = -1;
  L->length--;
}

// other operations -----------------------------------------------------
// printList()
// Prints to the file pointed to by out, a string rep
// of L consisting of a space separated seq of ints,with front on left.
// from queue.c
void printList(FILE *out, List L) {
  if (L == NULL) {
    fprintf(stderr, "List Error: calling printList() on NULL List\n");
    exit(EXIT_FAILURE);
  }
  Node N = NULL;
  for (N = L->front; N != NULL; N = N->next) {
    fprintf(out, "%d ", N->data); // loop through nodes and print data
  }
}

// copyList()
// returns a new List representing same integer sequence as L.
// The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state of L is unchanged.
List copyList(List L) {
  if (L == NULL) {
    fprintf(stderr, "List Error: calling copyList() on NULL List\n");
    exit(EXIT_FAILURE);
  }
  Node N = NULL;
  List copy_List = newList();
  N = L->front; // save front
  while (N != NULL) {
    append(copy_List, N->data);
    N = N->next; // while list not null, add data to copy and move next
  }
  return (copy_List);
}
