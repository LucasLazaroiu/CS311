#include <iostream>
using namespace std;

struct Entry {
  string name;
  int age;
  double GPA;
  string ID;
  Entry *next;
  Entry(string names, int AGE, double gpa, string id) {
    name = names;
    age = AGE;
    GPA = gpa;
    ID = id;
  }
};
//--------------------------------------------------------
class HashMap {
  Entry **table;

  int size;

public:
  HashMap(int size) {
    this->size = size;
    table = new Entry *[size];
    for (int i = 0; i < size; i++) {
      table[i] = NULL;
    }
  }
  unsigned long hash(string str);
  void put(const Entry &entry);
  Entry *get(string id);
  Entry *remove(string id);
};
//----HASH VALUE FUNCTION----------------------------------------------------
unsigned long HashMap::hash(string str) {
  const char *cstr = str.c_str();
  unsigned long hash = 5381;
  int c;
  while ((c = *cstr++)) {
    hash = hash * 33 + c;
  }
  return hash;
}

//-----PUT
//FUNCTION---------------------------------------------------------------
void HashMap::put(const Entry &entry) {
  string key = entry.ID;
  int index = hash(key) % size;
  if (table[index] == nullptr) {
    table[index] = new Entry(entry.name, entry.age, entry.GPA, entry.ID);
  } else {
    Entry *curr = table[index];
    while (curr->next != nullptr) {
      curr = curr->next;
    }
    curr->next = new Entry(entry.name, entry.age, entry.GPA, entry.ID);
  }
}
//--GET FUNCTION--------------------------------------------------
Entry *HashMap::get(string id) {
  string key = id;
  int index = hash(key) % size;
  if (table[index] == nullptr) {
    cout << "Not found in HashMap\n";
    return nullptr;
  }
  Entry *curr = table[index];
  while (curr != nullptr) {
    if (curr->ID == id) {
      cout << "Found " << key << " in HashMap\n";
      return curr;
    }
    curr = curr->next;
  }
  cout << "Not found in HashMap\n";
  return nullptr;
}
//--REMOVE FUNCTION-------------------------------------------
Entry *HashMap::remove(string id) {
  string key = id;
  int index = hash(key) % size;
  if (table[index] == nullptr) {
    cout << "ID was not in HashMap.\n";
    return nullptr;
  }
  Entry *curr = table[index];
  Entry *prev = curr;
  curr = curr->next;
  if (prev->ID == id) {
    table[index] = curr;
    delete prev;
    cout << "Deleted " << key << " ID from HashMap.\n";
    return prev;
  }
  while (curr != nullptr) {
    if (curr->ID == id) {
      prev->next = curr->next;
      Entry *temp = curr;
      delete curr;
      cout << "Deleted " << key << " ID from HashMap.\n";
      return temp;
    }
    curr = curr->next;
    prev = prev->next;
  }
  return nullptr;
}

//-----------------------------------------------------------
int main() {
  Entry student("Lucas", 19, 3.5, "1855213999");
  Entry student2("James", 20, 3.0, "1945213909");
  Entry student3("Jack", 21, 3.9, "1005213299");
  HashMap Hash(50);
  Hash.put(student);
  Hash.put(student2);
  Hash.put(student3);
  //--------------------------------
  Hash.get("1945213909");
  cout << endl;
  Hash.remove("1945213909");
  cout << endl;
  Hash.get("1945213909");
  return 0;
}