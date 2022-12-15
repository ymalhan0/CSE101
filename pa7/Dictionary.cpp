///////////////////////////////////
// Yukti Malhan
// ymalhan
// 2022 Winter CSE101 pa7
// Dictionary.cpp
// Implementation functions for Dictionary ADT
////////////////////////////////////////////

#include "Dictionary.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

// Private Constructor --------------------------------------------------------
// Node constructor
Dictionary::Node::Node(keyType k, valType v) {
  key = k;
  val = v;
  parent = nullptr;
  left = nullptr;
  right = nullptr;
}

// Class Constructors & Destructors ----------------------------------------
// Creates new Dictionary in the empty state.
Dictionary::Dictionary() {
  nil = new Node("\000", -1);
  // nil->parent = nil;
  //  nil->left = nil;
  //  nil->right = nil;
  root = nil;
  current = nil;
  num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary &D) {
  nil = new Node("\000", -1);
  //  nil->parent = nil;
  //  nil->left = nil;
  //  nil->right = nil;
  root = nil;
  current = nil;
  num_pairs = 0;
  preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary() {
  while (num_pairs > 0) {
    clear();
  }
  delete nil;
}

// Helper Functions (Optional) ---------------------------------------------
// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node *Dictionary::search(Node *R, keyType k) const {
  if (R == nil) { // used pseudo
    return nil;
  } else if (R->key == k) {
    return R;
  } else if (k < R->key) {
    return search(R->left, k);
  } else {
    return search(R->right, k);
  }
}
// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node *R, Node *N) {
  if (R != N) {                // term at N
    setValue(R->key, R->val);  // set values
    preOrderCopy(R->left, N);  // left
    preOrderCopy(R->right, N); // right
  }
}
// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node *R) {
  if (R == nil) {
    return; // no do anything
  }
  postOrderDelete(R->left);  // delete left node
  postOrderDelete(R->right); // delete right node
  R->parent = nullptr;       // set to null
  R->left = nullptr;
  R->right = nullptr;
  delete R;
  num_pairs--;
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node *Dictionary::findMin(Node *R) {
  if (R == nil) {
    return nil;
  } // used pseudo
  while (R->left != nil) {
    R = R->left;
  }
  return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node *Dictionary::findMax(Node *R) {
  if (R == nil) {
    return nil;
  } // used pseudo
  while (R->right != nil) {
    R = R->right;
  }
  return R;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost
// Node, or is nil, returns nil.
Dictionary::Node *Dictionary::findNext(Node *R) {
  if (!(R->right == nil)) {
    return findMin(R->right);
  } // used psuedo
  Node *y = R->parent;
  while (y != nil && R == y->right) {
    R = y;
    y = y->parent;
  }
  return y;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost
// Node, or is nil, returns nil.
Dictionary::Node *Dictionary::findPrev(Node *R) {
  if (!(R->left == nil)) {
    return findMax(R->left);
  } // used pseudo
  Node *y = R->parent;
  while (y != nil && R == y->left) {
    R = y;
    y = y->parent;
  }
  return y;
}

// Transplant()
// helper for remove()
void Dictionary::Transplant(Node *u, Node *v) {
  if (u->parent == nil) {
    root = v; // used pseudo
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  if (v != nil) {
    v->parent = u->parent;
  }
}

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string &s, Node *R) const {
  if (R != nil) {
    inOrderString(s, R->left); // used pseudo
    s.append(R->key);          // append key : val \n
    s.append(" : ");
    s.append(std::to_string(R->val));
    s.append("\n");
    inOrderString(s, R->right);
  }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string &s, Node *R) const {
  if (R != nil) {
    s.append(R->key); // used pseudo, same as in order but no val
    // s.append(" : ");
    // s.append(std::to_string(R->val));
    s.append("\n");
    preOrderString(s, R->left);
    preOrderString(s, R->right);
  }
}

// Access functions --------------------------------------------------------
// size()
// Returns the size of this Dictionary.
int Dictionary::size() const { return num_pairs; }

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
  // new Node N =  search(current, k);
  if (search(root, k) == nil) {
    return false;
  }
  return true;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType &Dictionary::getValue(keyType k) const {
  Node *N = search(root, k);
  if (contains(k) == false) {
    throw std::logic_error("Dictionary: getValue(): false contains");
  }
  return N->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false
// otherwise.
bool Dictionary::hasCurrent() const {
  if (current == nil || current == nullptr) {
    return false;
  }
  return true;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent()
keyType Dictionary::currentKey() const {
  if (!(hasCurrent())) {
    throw std::logic_error("Dictionary: hasCurrent(): false contains");
  }
  return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType &Dictionary::currentVal() const {
  if (hasCurrent() == false) {
    throw std::logic_error("Dictionary: hasCurrent(): false contains");
  }
  return current->val;
}

// Manipulation procedures -------------------------------------------------
// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
  // while (num_pairs > 0) {
  postOrderDelete(root);
  //  }
  nil = new Node("\000", -1);
  nil->parent = nil;
  nil->left = nil;
  nil->right = nil;
  root = nil;
  current = nil;
  num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v,
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
  // used pseudo
  Node *x = this->root;     // root
  Node *y = nil;            // y = NIL
  Node *z = new Node(k, v); // z = node of k, v
  while (x != nil) {
    y = x;
    if (k < x->key) { // z.key same as k
      x = x->left;
    } else {
      x = x->right;
    }
  }
  z->parent = y;
  if (y == nil) {
    this->root = z; // empty
    z->left = nil;  // link
    z->right = nil;
    num_pairs++; // increase size
  } else if (k < y->key) {
    y->left = z;
    z->left = nil;
    z->right = nil;
    num_pairs++;
  } else if (k > y->key) {
    y->right = z;
    z->left = nil;
    z->right = nil;
    num_pairs++;
  } else {
    y->val = v; // set to v
    delete z;   // dont need z
  }
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {
  // used pseudo
  if (contains(k) == false) {
    return;
  }
  Node *z = search(root, k);
  if (z == current) {
    current = nil;
  }
  if (z->left == nil) {
    Transplant(z, z->right);
    delete z;                   // transplant then delete z
  } else if (z->right == nil) { // case 2.2
    Transplant(z, z->left);
    delete z;
  } else {
    Node *y = findMin(z->right); // min
    if (!(y->parent == z)) {     // parent not z
      Transplant(y, y->right);
      y->right = z->right;
      y->right->parent = y;
      //  delete y;
    }
    Transplant(z, y);
    y->left = z->left;
    y->left->parent = y;
    delete z;
  }
  num_pairs--; // decrement size
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::begin() {
  if (num_pairs > 0) {
    Node *min = findMin(root);
    current = min;
  }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::end() {
  if (num_pairs > 0) {
    Node *max = findMax(root);
    current = max;
  }
}

// next()
// If the current iterator is not at the last pair, advances current
// to the next pair (as defined by the order operator < on keys). If
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {
  if (!(hasCurrent())) {
    return;
  }
  if (findNext(current) != nil) {
    Node *next = findNext(current); // current is find next
    current = next;
  } else {
    current = nil;
  }
}

// prev()
// If the current iterator is not at the first pair, moves current to
// the previous pair (as defined by the order operator < on keys). If
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() {
  if (!(hasCurrent())) {
    return;
  }
  if (findPrev(current) != nil) {
    Node *prev = findPrev(current);
    current = prev; // current is find prev
  } else {
    current = nil;
  }
}

// Other Functions ---------------------------------------------------------
// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value
// are separated by the sequence space-colon-space " : ". The pairs are arranged
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
  // Node N = nil;
  std::string s = "";
  this->inOrderString(s, this->root); // just use helper
  return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
  // Node N = nil;
  std::string s = "";
  this->preOrderString(s, this->root); // just use helper
  return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary &D) const {
  // used pseudo from ta eric section
  string a = "";
  string b = "";
  this->preOrderString(a, this->root);
  D.preOrderString(b, D.root);
  return a == b;
}

// Overloaded Operators ----------------------------------------------------
// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream &operator<<(std::ostream &stream, Dictionary &D) {
  return stream << D.Dictionary::to_string();
} // same as list

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals().
bool operator==(const Dictionary &A, const Dictionary &B) {
  return A.Dictionary::equals(B);
} // same as list

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary &Dictionary::operator=(const Dictionary &D) {
  if (this != &D) {
    Dictionary temp = D;
    std::swap(nil, temp.nil);
    std::swap(root, temp.root);
    std::swap(current, temp.current);
    std::swap(num_pairs, temp.num_pairs);
  }
  return *this;
} // same as list
