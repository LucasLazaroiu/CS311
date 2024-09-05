#include <iostream>
using namespace std;

const int CAP = 100000;
struct Node {
  Node *next; // points to the next Node object
  int time;
};

class Queue {
private:
  Node *front = nullptr;

public:
  int getTop();
  void dequeue();
  void endQueue(int val);
  bool isEmpty();
};

int Queue::getTop() { return front->time; }

void Queue::dequeue() {
  Node *temp = front;
  front = front->next;
  temp->next = nullptr;
  delete temp;
}

void Queue::endQueue(int val) {
  Node *ptr = new Node; // creates new node in the push front
  ptr->time = val;
  ptr->next = nullptr;
  if (isEmpty()) {
    front = ptr;

  } else {
    Node *curr = front;
    while (curr->next != nullptr) {
      curr = curr->next;
    }
    curr->next = ptr;
  }
}

bool Queue::isEmpty() { return front == nullptr; }

//---------------------------------------------------------
int main() {
  Queue q;
  int N = 0;
  int minutesPerCow = 0;
  int K = 0;
  int stage[CAP] = {0};
  bool flag = false;
  int smallest_index = 0;
  int total_time = 0;
  int largest_index = 0;
  cin >> N >> K;

  cout << endl;


  if (K == 1) {

    for (int i = 0; i < N; i++) {
      cin >> minutesPerCow;
      // this loop enters the numbers into the queue
      q.endQueue(minutesPerCow);
    }
    
    //cout << "time: " << total_time << endl;
    while (!q.isEmpty())
      {
      total_time += q.getTop();
      cout << "time: " << total_time << endl;
      q.dequeue();
      }
    cout << total_time << endl;
  }


  
  else if (K > 0) {

    for (int i = 0; i < N; i++) {
      cin >> minutesPerCow;
                                                       // this loop enters the numbers into the queue
      q.endQueue(minutesPerCow);
    }

    for (int i = 0; i < K;
         i++)                                   // for loop that will take the first wave of cows on the stage
    {
      if (!q.isEmpty()) {
        stage[i] = q.getTop();
        q.dequeue();
      }
    }

    while (flag == false) {
      smallest_index = 0;
      if (q.isEmpty()) {                                      //checks if queue is emptry and if it is it finds the largest index and adds it to the time
        for (int j = 0; j < K; j++) {
          if (stage[largest_index] < stage[j]) {    
            largest_index = j;
          }
        }
        total_time += stage[largest_index];
        flag = true;
      } else {
        for (int s = 0; s < K; s++) {                            //finds the smallest index and starts it in smallest index
          if (stage[smallest_index] >= stage[s]) {
            smallest_index = s;
          }
        }
        int test = stage[smallest_index];
        for (int i = 0; i < K; i++) {                            //subtracts every number in teh stage by that number
          stage[i] -= test;
        }
        for (int i = 0; i < K; i++) {                  
          if (stage[i] == 0) {                                  //checks if any of the numbers in the stage are 0 if so put the next number in the stage
            stage[i] = q.getTop();
            q.dequeue();
          }
        }
        total_time += stage[smallest_index];                    //adds the smallest number to the total time
      }
    }

    cout << endl;
    cout << total_time << endl;

  } else {
    cout << total_time;
  }
}