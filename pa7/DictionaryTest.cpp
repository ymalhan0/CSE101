///////////////////////////////////
// Yukti Malhan
// ymalhan
// 2022 Winter CSE101 pa7
// DictionaryTest.cpp
// Dictionary ADT test function
////////////////////////////////////////////

#include "Dictionary.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int main() {
  Dictionary A;
  A.setValue("a", 1);
  A.setValue("b", 2);
  A.setValue("c", 3);
  A.setValue("d", 4);
  A.setValue("e", 56);
  cout << " A: " << A << endl;
  cout << endl;
  cout << "size: " << A.size() << endl;
  cout << endl;
  A.begin();
  cout << "begin val: " << A.currentVal() << endl;
  A.end();
  cout << "end val: " << A.currentVal() << endl;
  // A.next();
  // cout << "next val: " << A.currentVal() << endl;
  // A.prev();
  // cout << "prev val: " << A.currentVal() << endl;
  cout << endl;
  A.remove("a");
  A.begin();
  cout << "begin val: " << A.currentVal() << endl;
  cout << endl;
  Dictionary B = A;
  cout << "A==B is " << (A == B ? "true" : "false") << endl;
  // cout << A.getValue("a") << endl;
  cout << A.pre_string() << endl;
  string s;
  int x;
  for (A.begin(); A.hasCurrent(); A.next()) {
    s = A.currentKey();
    x = A.currentVal();
    cout << "(" + s + ", " << x << ") ";
  }
  cout << endl << endl;
  A.clear();
  cout << A << endl;
}
