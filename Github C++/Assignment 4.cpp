#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

struct Node {
  int key;
  Node *LC;
  Node *RC;
  int height;
  // public:
  Node(int data) {
    key = data;
    height = 0;
    LC = RC = NULL;
  }
  // int getHeight(){return height;}
};

class AVL {
private:
  Node *root;
  int spaces;                              //will help for indentation 
  int height(Node *node);
  int getBalance(Node *N);
  Node *rightmostNode(Node *node);
  Node *leftRotate(Node *z);
  Node *rightRotate(Node *z);
  Node *insert(Node *node, int key);
  Node *remove(Node *node, int key);
  void in_order(Node*) const;
  void pre_order(Node*) const;
  void post_order(Node*) const;
  Node* search(Node* root, int key);
  void print(Node* node);
public:
  int max(int a, int b);
  int height();
  int getBalance();
  Node *rightmostNode();
  Node *leftrotate();
  Node *rightRotate();
  void insert(int key);
  void remove(int key);
  void pre_order();
  void post_order();
  void in_order();
  Node* search(int key);
  void print();
  AVL();

};
//--------DEFUALT--constructor---------
AVL::AVL()
{
  root = nullptr;
  spaces = 0;
}
//-------MAX---------------------
int AVL::max(int a, int b) { return (a > b) ? a : b; }
//------HEIGHT------------------
int AVL::height() { return height(root); }
int AVL::height(Node *node) {
  if (node == NULL) {
    return -1;
  }
  return node->height;
}
//--------BALANCE--------------------
int AVL::getBalance() { return getBalance(root); }
int AVL::getBalance(Node *N) {
  if (N == NULL)
    return 0;
  return height(N->LC) - height(N->RC);
}
//----RIGHT MOST-------------------------------------------
Node *AVL::rightmostNode() { return rightmostNode(root); }
Node *AVL::rightmostNode(Node *node) {
  Node *current = node;
  while (current->RC != NULL)
    current = current->RC;
  return current;
}
//-----------LEFTROTATE-----------------------
Node *AVL::leftrotate() { return leftRotate(root); }
Node *AVL::leftRotate(Node *z) {
  Node *y = z->RC;
  Node *T2 = y->LC;
  // Perform rotation
  y->LC = z;
  z->RC = T2;
  // Update heights
  z->height = max(height(z->LC), height(z->RC)) + 1;
  y->height = max(height(y->LC), height(y->RC)) + 1;
  // Return new root
  return y;
}
//-------------RIGHTROTATE------------------------------
Node *AVL::rightRotate() { return rightRotate(root); }
Node *AVL::rightRotate(Node *z) {
  Node *y = z->LC;
  Node *T3 = y->RC;
  // Perform rotation
  y->RC = z;
  z->LC = T3;
  // Update heights
  z->height = max(height(z->LC), height(z->RC)) + 1;
  y->height = max(height(y->LC), height(y->RC)) + 1;
  // Return new root
  return y;
}
//-------------INSERT-----------------------------------
void AVL::insert(int key) {
  root = insert(root, key);
}
Node *AVL::insert(Node *node, int key) {
  if (node == NULL) {
    node = new Node(key);
    return node;
  } else if (key < node->key) {
    node->LC = insert(node->LC, key);
  } else if (key > node->key) {
    node->RC = insert(node->RC, key);
  } else {
    return node;
  }
  node->height = 1 + max(height(node->LC), height(node->RC)); //updates height of the tree
  int balance = getBalance(node); //gets the balance
  if (balance > 1 && key < node->LC->key) { //left case
    return rightRotate(node);
  }
  if (balance < -1 && key > node->RC->key) { //right case
    return leftRotate(node);
  }
  if (balance > 1 && key > node->LC->key) { //left right case
    node->LC = leftRotate(node->LC);
    return rightRotate(node);
  }
  if (balance < -1 && key < node->RC->key) { //right left case
    node->RC = rightRotate(node->RC);
    return leftRotate(node);
  }
  return node;
}
//--------------DELETION-----------------------------
void AVL::remove(int key) {
  remove(root, key);
  return;
}
Node *AVL::remove(Node *node, int key) {
  if (node == NULL) {
    return node;
  }
  if (node->key > key) {
    node->LC = remove(node->LC, key);
  } else if (key > node->key) {
    node->RC = remove(node->RC, key);
  } else {
    if (node->LC == NULL) {
      Node *temp = node->RC;
      delete node;
      return temp;
    } else if (node->RC == NULL) {
      Node *temp = node->LC;
      delete node;
      return temp;
    }
    Node *temp = rightmostNode(node->LC);
    node->key = temp->key;
    node->LC = remove(node->LC, temp->key);
  }
  if (node == NULL) {
    return node;
  }
  node->height = 1 + max(height(node->LC), height(node->RC));
  int balance = getBalance(node);
  if (balance > 1 && getBalance(node->LC) >= 0) {
    return rightRotate(node);
  }
  if (balance > 1 && getBalance(node->LC) < 0) {
    node->LC = leftRotate(node->LC);
    return rightRotate(node);
  }
  if (balance < -1 && getBalance(node->RC) <= 0) {
    return leftRotate(node);
  }
  if (balance < -1 && getBalance(node->RC) > 0) {
    node->RC = rightRotate(node->RC);
    return leftRotate(node);
  }
  return node;
}
//-----ALL-traversals---------------------------
void AVL::in_order()
{
  in_order(root);
}
void AVL::in_order(Node* r) const
{
if(r != nullptr)
{
  in_order(r->LC);
  cout<< r->key << " ";
  in_order(r-> RC);
}
}
//------PRE-ORDER--------------------
void AVL::pre_order()
{
  pre_order(root);
}
void AVL::pre_order(Node* r) const
{
  if(r == NULL){
    return;
  }
  cout << (r->key) << " ";
  pre_order(r->LC);
  pre_order(r->RC);
}
//-------POST-ORDER--------------------
void AVL::post_order()
{
  post_order(root);
}
void AVL::post_order(Node* r) const
{
  if(r == NULL){
    return;
  }
  post_order(r->LC);
  post_order(r->RC);
  cout << r -> key << " ";
}
//-----Search---------------------------
Node* AVL::search(int key)
{
  return search(root, key);
}
Node* AVL::search(Node*root, int key)
{
  if(root == nullptr || root->key == key)
  {
    return root;
  }
  else if(root-> key < key)
  {
    return search(root->RC, key);
  }
  else
  {
    return search(root->LC, key);
  }
}
//------------------------------------------
void AVL::print() {
    if (root == nullptr) {
        cout << "No numbers in tree" << endl;
        return;
    }

    print(root);
}

void AVL::print(Node* node) {
    if (node == nullptr) {
        return;
    }
    spaces++;                  //increments spaces by 1
    print(node->RC);           //recursivly calls the function one more to the right
    cout << setw(spaces * 8) << node->key << endl; //indents the numbers from eachother to give eachother spaces
 
    print(node->LC);           //recursivly calls the function one to the left
    spaces--;                  //decrements the spaces so when we are doen with right side we can decrease the spaces to go back
}
//------------------------------------
int main() 
{ 
AVL A;
string numbers;
int num;
int nums;
int nums1;

cout << "Enter your numbers you want to be in the AVL tree: " << endl;

  getline(cin, numbers);
cout << endl << endl;
  int size = 0;

  stringstream s1(numbers);
  stringstream s2(numbers);
  while (s1 >> num) {
    size++;                                  
  }



  
  int array[size];
  for (int i = 0; i < size; i++) {
    s2 >> array[i];                            
  }
  for(int i = 0; i < size; i++)
    {
      A.insert(array[i]);
    }
  A.print();


cout << "\n\nIn order traversal: \n";
A.in_order();
cout << endl;
cout << "pre order traversal: \n";
A.pre_order();
cout << endl;
cout << "post order traversal: \n";
A.post_order();
cout << endl;


cout <<"What number would you like to remove? ";
cin >> nums;
cout << endl;
A.remove(nums);
A.print();

cout <<"What number would you like to search? ";
cin >> nums1;
cout << endl;
if(A.search(nums1) == nullptr)
{
  cout << "Number is not in tree";
}
else{
  cout << "Number is in tree.";
}

  
}