#include <iostream>
using namespace std;

struct edge {
  int adj_vtx;
  edge *next;
};

class Queue {
private:
  edge *front = nullptr;
  
public:
  Queue() {
    front = nullptr;
  }
  int getTop();
  void dequeue();
  void pushBack(int val);
  bool isEmpty();
};
int Queue::getTop() { return front->adj_vtx; }
void Queue::dequeue() {
  edge *temp = front;
  front = front->next;
  temp->next = nullptr;
  delete temp;
}
void Queue::pushBack(int val) {
  edge *ptr = new edge; // creates new node in the push front
  ptr->adj_vtx = val;
  ptr->next = nullptr;
  if (isEmpty()) {
    front = ptr;

  } else {
    edge *curr = front;
    while (curr->next != nullptr) {
      curr = curr->next;
    }
    curr->next = ptr;
  }
}
bool Queue::isEmpty() { return front == nullptr; }

// NEW CLASS------------------------------------------------
class Graph {
  int V;      // No. of vertices
  edge **adj; // Pointer to an array containing adjacency lists
  void DFSUtil(int v, bool visited[]); // A function used by DFS

public:
  Graph(int v) {
    V = v;
    adj = new edge *[V];
    for (int i = 0; i < V; i++) {                  //for loop sets all indexs to null
      adj[i] = nullptr;
    }
  }                           // Constructor
  void addEdge(int v, int w); // function to add an edge (from v to w) to graph
  void BFS(int s);            // BFS traversal of the vertices reachable from s
  void DFS(int v);            // DFS traversal of the vertices reachable from v
  bool pathExist(int s, int t); // Check if there is a path from s to t.
  void printGraph(int V);
};
//ADDEDGE----------------------------------------------------
void Graph::addEdge(int v, int w) {
 
  edge* ptr = new edge;
  ptr->adj_vtx = w;
  ptr->next = nullptr;

  if(adj[v] == nullptr) {
      adj[v] = ptr;                       //if index is null it sets ptr to the first number
  }
  else {
      edge* curr = adj[v];
      while(curr->next != nullptr) {         //if not it goes into the while loop and adds another connection to that number
          curr = curr->next;
      }
      curr->next = ptr;
  }
  
  
}
//BFS-------------------------------------------------------------
void Graph::BFS(int s) {
  //cout << "begin" << endl;
  bool *visited = new bool[V];
  for (int i = 0; i < V; i++) {
    visited[i] = false;                    //
  }
  Queue Queue;
  visited[s] = true;
  Queue.pushBack(s);
  while (!Queue.isEmpty()) {
    s = Queue.getTop();
    cout << s << " ";
    Queue.dequeue();
    edge *curr = adj[s];
    while (curr != nullptr) {
      if (!visited[curr->adj_vtx]) {
        visited[curr->adj_vtx] = true;
        Queue.pushBack(curr->adj_vtx);
      }
      curr = curr->next;
    }
  }
  
}
//DFS---------------------------------------------------
void Graph::DFS(int v) {
  bool *visited = new bool[V];
  for (int i = 0; i < V; i++){
     visited[i] = false;
  }
  DFSUtil(v, visited);
}
void Graph::DFSUtil(int v, bool visited[]) {
  visited[v] = true;
  cout << v << " ";
  edge *curr = adj[v];
  while (curr != nullptr) {
    if (!visited[curr->adj_vtx]) {
      visited[curr->adj_vtx] = true;
      DFSUtil(curr->adj_vtx, visited);
    }
    curr = curr->next;
  }
}
//-------------------------------------------------------
bool Graph::pathExist(int s, int t) 
{
  //cout << "begin" << endl;
  bool *visited = new bool[V];
  for (int i = 0; i < V; i++) {
    visited[i] = false;
  }
  Queue Queue;
  visited[s] = true;
  Queue.pushBack(s);
  while (!Queue.isEmpty()) {
    s = Queue.getTop();
    if(s == t)
    {
      return true;
    }
    Queue.dequeue();
    edge *curr = adj[s];
    while (curr != nullptr) {
      if (!visited[curr->adj_vtx]) {
        visited[curr->adj_vtx] = true;
        Queue.pushBack(curr->adj_vtx);
      }
      curr = curr->next;
    }
  }
  return false;
}
// MAIN-----------------------------------------------------
int main() {
  Graph graph(20);
  cout << boolalpha;

  graph.addEdge(0, 1);
  graph.addEdge(1, 2);
  graph.addEdge(2, 3);
  graph.addEdge(3, 4);
  graph.addEdge(4, 5);
  graph.addEdge(5, 2);
  graph.addEdge(7, 9);
  graph.addEdge(1, 15);
  cout << "BFS traversal from 1" << endl;;
  graph.BFS(1);
  cout << "\nDFS traversal from 0" << endl;
  graph.DFS(0);
  cout << "\nDoes path exist from 1 to 5? (should return true) \n" <<   
  graph.pathExist(1, 5) << endl;
  cout << "Does path exsist from 1 to 6? (should return false) \n" << 
  graph.pathExist(1,6) << endl;

  
  return 0;
}