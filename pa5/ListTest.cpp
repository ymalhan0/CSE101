///////////////////////////////////
// Yukti Malhan
// ymalhan
// 2022 Winter CSE101 pa5
// ListTest.cpp
// Test file for List ADT
/////////////////////////////////////////

#include "List.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int main() {
  List A;

  for (int i = 1; i <= 10; i++) {
    A.insertAfter(i);
  }

  cout << endl;
  cout << "A = " << A << endl;
  cout << "A.position() = " << A.position() << endl;

  A.moveFront();
  cout << "Front A.position() = " << A.position() << endl;

  A.moveBack();
  cout << "Back A.position() = " << A.position() << endl;

  A.movePrev();
  A.movePrev();
  cout << "Prev A.position() = " << A.position() << endl;

  A.moveNext();
  cout << "Next A.position() = " << A.position() << endl;
  cout << endl;

  List B;
  for (int i = 1; i <= 10; i++) {
    B.insertAfter(i);
  }
  cout << "A==B is " << (A == B ? "true" : "false") << endl;
  cout << endl;

  cout << A.findNext(5) << endl;
  cout << "A before erase" << A << endl;
  // A.eraseBefore();
  // A.eraseAfter();
  // cout << "A after erase" << A << endl;
  cout << A.position() << endl;
  //  cout << A.findPrev(2) << endl;
  cout << endl;

  //  for (int i = 1; i <= 10; i++) {
  //    A.insertBefore(i);
  //  }
  //  cout << A << endl;
  //  cout << endl;

  List J = A.concat(B);
  cout << "J = " << J << endl;
  cout << "length: " << J.length() << endl;
  cout << "front " << J.front() << endl;
  cout << "back " << J.back() << endl;
  cout << "position " << J.position() << endl;

  cout << "peeknext " << J.peekNext() << endl;
  //  cout << "peekprev " << J.peekPrev() << endl;
  cout << endl;
  return (EXIT_SUCCESS);
}
