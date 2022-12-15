///////////////////////////////////
// Yukti Malhan
// ymalhan
// 2022 Winter CSE101 pa5
// List.cpp
// Implementation functions for List ADT
////////////////////////////////////////

#include "List.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

// NOTE used queue example for most of everything

// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x) {
  data = x;
  next = nullptr;
  prev = nullptr;
}

// Class Constructors & Destructors ----------------------------------------
// Creates new List in the empty state.
List::List() {
  frontDummy = new Node(-1);
  backDummy = new Node(-2);
  frontDummy->next = backDummy;
  backDummy->prev = frontDummy;
  beforeCursor = frontDummy;
  afterCursor = backDummy;
  pos_cursor = 0;
  num_elements = 0;
}

// Copy constructor.
List::List(const List &L) {
  // make empty list
  frontDummy = new Node(-1);
  backDummy = new Node(-2);
  frontDummy->next = backDummy;
  backDummy->prev = frontDummy;
  beforeCursor = frontDummy;
  afterCursor = backDummy;
  pos_cursor = 0;
  num_elements = 0;
  // load elements of L into this List
  Node *N = L.frontDummy->next;
  while (N != L.backDummy) {
    this->insertAfter(N->data);
    moveNext();
    N = N->next;
  }
  moveFront();
}

// Destructor
List::~List() {
  while (num_elements > 0) {
    clear();
  }
  delete frontDummy;
  delete backDummy;
}

// Access functions --------------------------------------------------------
// length()
// Returns the length of this List.
int List::length() const { return (num_elements); }

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
  if (num_elements == 0) {
    throw std::length_error("List: front(): empty List");
  }
  return (frontDummy->data);
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
  if (num_elements == 0) {
    throw std::length_error("List: back(): empty List");
    // return;
  }
  return (backDummy->data);
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
  if (pos_cursor < 0 || pos_cursor > num_elements) {
    throw std::range_error("List: position(): 0 <= position() <= length()");
    // return 0;
  }
  return (pos_cursor);
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
  if (position() >= length()) {
    throw std::range_error("List: peekNext(): position() >= length");
    // return;
  }
  return (afterCursor->data);
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
  if (position() <= 0) {
    throw std::range_error("List: peekPrev(): position() <= 0");
    // return;
  }
  return (beforeCursor->data);
}

// Manipulation procedures -------------------------------------------------
// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
  // moveFront();
  /*if (num_elements == 0) {
    //   throw std::length_error("List: clear(): empty List");
    return;
  } */
  moveFront();
  while (length() > 0) {
    // moveNext();
    // eraseBefore();
    eraseAfter();
    // movePrev();
    // eraseAfter();
  }
  frontDummy->next = backDummy; // reset everything
  backDummy->prev = frontDummy;
  beforeCursor = frontDummy;
  afterCursor = backDummy;
  pos_cursor = 0;
  num_elements = 0;
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
  if (num_elements == 0) {
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    return; // before and after at same element
  }
  beforeCursor = frontDummy;
  afterCursor = frontDummy->next;
  pos_cursor = 0;
  return;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
  if (num_elements == 0) {
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    return;
  }
  afterCursor = backDummy;
  beforeCursor = backDummy->prev;
  pos_cursor = num_elements;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over.
// pre: position()>0
ListElement List::movePrev() {
  if (pos_cursor == 0) {
    //   throw std::length_error("List: movePrev(): empty List");
    return 0;
  }
  //  ListElement x = beforeCursor->data;
  beforeCursor = beforeCursor->prev;
  afterCursor = afterCursor->prev;
  pos_cursor--;
  return afterCursor->data;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over.
// pre: position()<length()
ListElement List::moveNext() {
  if (position() >= length()) {
    //   throw std::range_error("List: moveNext(): position() >= length()");
    return 0;
  }
  // ListElement x = afterCursor->data;
  beforeCursor = beforeCursor->next;
  afterCursor = afterCursor->next;
  pos_cursor++;
  return beforeCursor->data;
}

// insertAfter()
// Inserts x after cursor.
// Pre: length()>0, index()>=0
void List::insertAfter(ListElement x) {
  // if (length() <= 0 || pos_cursor < 0) {
  //  return;
  Node *temp = new Node(x);
  temp->prev = beforeCursor; // link temp between before and after cursors
  temp->next = afterCursor;
  // temp->next = afterCursor->next;
  // afterCursor->next = temp;
  afterCursor->prev = temp; // link prev and next
  beforeCursor->next = temp;
  // beforeCursor->next = temp;
  afterCursor = temp; // aftercursor is the temp
  num_elements++;
}

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void List::insertBefore(ListElement x) {
  Node *temp = new Node(x);
  temp->prev = beforeCursor; // link temp
  temp->next = afterCursor;
  afterCursor->prev = temp; // link prev and next
  beforeCursor->next = temp;
  beforeCursor = temp; // before cursor is the temp
  pos_cursor++;        // increent cursor
  num_elements++;
}

// setAfter()
// Overwrites the List element after the cursor with x
// pre: position()<length()
void List::setAfter(ListElement x) {
  if (position() >= length()) {
    // throw std::range_error("List: setAfter(): position() >= length()");
    return;
  }
  afterCursor->next->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x
// pre: position()>0
void List::setBefore(ListElement x) {
  if (position() <= 0) {
    //   throw std::range_error("List: setBefore(): position() <= 0");
    return;
  }
  beforeCursor->prev->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
  if (position() >= length()) {
    //  throw std::range_error("List: eraseAfter(): position() >= length()");
    return;
  }
  afterCursor->prev->next = afterCursor->next; // next and prev
  afterCursor->next->prev = afterCursor->prev;
  afterCursor = afterCursor->next;
  num_elements--;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
  if (position() <= 0) {
    //   throw std::range_error("List: eraseBefore(): position() <= 0");
    return;
  }
  beforeCursor->prev->next = beforeCursor->next; // next and prev
  beforeCursor->next->prev = beforeCursor->prev;
  beforeCursor = beforeCursor->prev;
  pos_cursor--;
  num_elements--;
}

// Other Functions ---------------------------------------------------------
// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then
// returns the final cursor position. If x is not found, places the cursor at
// position length(), and returns -1.
int List::findNext(ListElement x) {
  bool f = false;
  Node *N = afterCursor;
  while (!f && N != backDummy) {
    f = (N->data == x); // x is data?
    if (!f) {           // no then move next
      N = N->next;
    }
    pos_cursor++;
  }
  afterCursor = N->next;
  beforeCursor = N; // fix before and after  
if (f) {
    return pos_cursor; // pos of x
  } else {
    return -1;
  }
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position 0, and returns -1.
int List::findPrev(ListElement x) {
  bool f = false;
  do {
    if (x == movePrev()) {
      f = true;
      break;
    }
  } while (pos_cursor > 0);
  return (f ? pos_cursor : -1);
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost
// occurrance of each element, and removing all other occurances. The cursor
// is not moved with respect to the retained elements, i.e. it lies between
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
  int position = 0;
  Node *cursor = frontDummy->next;
  Node *current = nullptr;
  Node *n = nullptr;
  while (cursor != backDummy) {
    current = cursor;
    n = cursor->next;
    position += 1;
    while (n != backDummy) {
      if (cursor->data == n->data) {
        current->next = n->next;
        n->next->prev = current;
        delete n;
        n = current->next;
        num_elements -= 1;
        if (position < pos_cursor) {
          pos_cursor -= 1;
        }
      } else {
        current = n;
        n = current->next;
      }
    }
    cursor = cursor->next;
  }
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List &L) const {
  List J;
  Node *N = this->frontDummy->next;
  Node *M = L.frontDummy->next;
  while (N != this->backDummy) { // back dummy instead of nullptr
    J.insertAfter(N->data);
    N = N->next;
  }
  while (M != L.backDummy) {
    J.insertAfter(M->data);
    M = M->next;
  }
  return J;
}

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
  Node *N = nullptr;
  std::string s = "";
  for (N = frontDummy; N != nullptr; N = N->next) {
    s += std::to_string(N->data) + " ";
  }
  return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List &R) const {
  bool eq = false;
  Node *N = nullptr;
  Node *M = nullptr;
  eq = (this->num_elements == R.num_elements);
  N = this->frontDummy;
  M = R.frontDummy;
  while (eq && N != nullptr) {
    eq = (N->data == M->data);
    N = N->next;
    M = M->next;
  }
  return eq;
}

std::ostream &operator<<(std::ostream &stream, const List &L) {
  return stream << L.List::to_string();
}

bool operator==(const List &A, const List &B) { return A.List::equals(B); }

List &List::operator=(const List &L) {
  if (this != &L) {
    List temp = L;
    /*std::swap(beforeCursor, temp.beforeCursor);
    std::swap(afterCursor, temp.afterCursor);
    std::swap(num_elements, temp.num_elements);
*/
    std::swap(frontDummy, temp.frontDummy);
    std::swap(backDummy, temp.backDummy);
    std::swap(num_elements, temp.num_elements);
    std::swap(beforeCursor, temp.beforeCursor);
    std::swap(afterCursor, temp.afterCursor);
    std::swap(pos_cursor, temp.pos_cursor);
  }
  return *this;
}
