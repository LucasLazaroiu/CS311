// Name: Lucas Lazaroiu
// Student ID: 201049984
// Email: lazar048@csusm.edu


#include <iostream>
using namespace std;

struct Node
{
int num;
Node * next;
};


Node * createLinkedList (int a[], int len);
Node * mergeLinkedLists (Node ** LL, int len);
Node * removeDuplicate (Node * L);
Node * reverseLinkedList (Node * L);
void display(Node *head);

//____________________________________________________
int main()
{
int a[] = {0, 2, 4, 2, 6, 7};
int b[] = {1, 8, 9, 10};
int c[] = {12};
int d[] = {1, 2, 1, 2, 4, 1, 4};
  
Node * linkOne;
Node * linkTwo;
Node * linkThree;
Node * linkFour;
  
  linkOne = createLinkedList(a, 6);      // creates link using array a          
  linkTwo = createLinkedList(b, 4);      // creates link using array b 
  linkThree = createLinkedList(c, 1);    // creates link using array c 
  linkFour = createLinkedList(d, 7);     // creates link using array d 

  
  cout << "Link List A: \n";
  display(linkOne);
  cout << endl;
  cout << "Link List B: \n";
  display(linkTwo);
  cout << endl;
  cout << "Link List C: \n";
  display(linkThree);
  cout << endl;
  cout << "Link List D:: \n";
  display(linkFour);
  cout << endl;

  cout << "Merging list A , B , C: \n";
  Node* array[3] = {linkOne, linkTwo, linkThree};      //creates an array of link lists
  Node* merged = mergeLinkedLists(array, 3);           // will merge them
  display(merged);
  cout << endl << endl;

  
  cout << "Removing duplicates from list D: " << endl;
  linkFour = removeDuplicate(linkFour);                //removes all duplicates from the list
  display(linkFour);
  cout << endl;


  
  cout << "Reversed Linked list for list A: \n";        
  linkOne = reverseLinkedList(linkOne);                //reverses the whole list
  display(linkOne);
  cout << endl;
  
}
//______________________________________________________
Node * createLinkedList (int a[], int len)
{
Node *head = nullptr;
Node *curr = nullptr;
if(len <= 0)
{
  cout << " list is empty! ";
}
else
{
for(int i = 0; i < len; i++)
{
 Node* ptr = new Node; 
 ptr -> num = a[i];
 ptr -> next = nullptr;
 if(head == nullptr)
 {
   head = ptr;
   curr = ptr;
 }
 else
   {
   curr ->next = ptr;
   curr = ptr;
   } 
}
}
  return head;
}



Node * mergeLinkedLists (Node ** LL, int len)
{

Node *head = nullptr;
Node * tail = nullptr;
Node* curr;

for(int i = 0; i < len; i++)
{
Node * ptr = LL[i];                  //sets ptr to the first link list
 
while(ptr != nullptr)
{
  curr = new Node;                  //creates a new node and setting it equal to the ptr pointer
  curr -> num = ptr -> num;
  curr->next = nullptr;              //increments curr
  if(head == nullptr)              //checks if its the first in the new list
  {
    head = curr;                  //sets head pointint to that new node
  }
  
  else{
    tail->next = curr;             //points tails next to curr;
  }
  tail = curr;                    //tail is equal to curr
  ptr = ptr -> next;              //increments ptr to the next spot
    
}
    
 }  
  
  return head;
}



Node * removeDuplicate (Node * L)
{
  Node *curr = L;  
  Node *head = curr;
  Node *duplicate = curr;
  Node *prev = curr;
  duplicate = duplicate -> next;
  bool removed = false;

while(curr != nullptr)                          //loop ends once curr reaches nullptr
{
while(duplicate != nullptr)                //inner loop cancels once duplicate reaches nullptr
  {
    removed = false;
    if(duplicate -> num == curr -> num)
    {
      Node *ptr = new Node;                      //creates new Node
      ptr = duplicate;                            //sets it equal to duplicate
      duplicate = duplicate->next;                //traverses duplicate through the list
      ptr-> next = nullptr;                        
      prev -> next = duplicate;                  
      delete ptr;                                  //deletes the node
      removed = true;
    }
    if(removed == false)
    {
    duplicate = duplicate -> next;
    prev = prev -> next;
    }
  }
  curr = curr -> next;                          //increments curr to the next in the list
  if(curr != nullptr)
  duplicate = curr -> next;
  prev = curr;
  
}
  
   
  
  return head;
}



Node * reverseLinkedList (Node * L)
{
  Node *front = nullptr;            
  Node *curr = L;                //set curr to point to the head of the list
  Node *prev = nullptr;          
while(curr != nullptr)
{
front = curr -> next;            //points front to curr's next
curr -> next = prev;              // curr's next points to prev
prev = curr;                      // prev is now curr
curr = front;                     //curr is now equal to front
}
return prev;                    //prev is now the head of the list
}



void display(Node* head)
{
  if (head== nullptr) {
    cout << "Empty List\n";
  }
  else
  {
    Node *ptr = head;
    while(ptr != nullptr)
      {
        cout << ptr -> num << "  ";
        ptr = ptr-> next;
        
      }
    cout << endl;
  }
}