#include <iostream>
#include <sstream>
using namespace std;

void selectionSort(int A[], int len);
void bubbleSort(int A[], int len);
void insertionSort(int A[], int len);

void mergeSort(int A[], int len);
void MERGE(int A[], int p, int q, int r);
void MERGEsort(int A[], int p, int r);

void quickSort(int A[], int len);
void QUICKSORT(int A[], int p, int r);
int Partition(int A[], int p, int r);

int main() {

  int num = 0;
  string numbers;

  cout << "Enter your numbers you want to be sorted: " << endl;

  getline(cin, numbers);

  int size = 0;

  stringstream s1(numbers);
  stringstream s2(numbers);
  while (s1 >> num) {
    size++;                                            //finds the size of the array
  }
  
  int array[size];

  for (int i = 0; i < size; i++) {
    s2 >> array[i];                                   //finds the numbers to put in the array
  }

  
int array2[size];
int array3[size];
int array4[size];
int array5[size];
for(int i = 0; i< size; i++)
{
  array2[i] = array[i];
  array3[i] = array[i];
  array4[i] = array[i];
  array5[i] = array[i];
}


cout << "Using Bubble Sort: " << endl;
bubbleSort(array, size);
  for (int i = 0; i < size; i++) {
    cout << array[i] << "  ";
  }
cout << "\nUsing Selection Sort: " << endl;
selectionSort(array2, size);
  for (int i = 0; i < size; i++) {
    cout << array2[i] << "  ";
  }
cout << "\nUsing Insertion Sort: " << endl;
  insertionSort(array3, size);
  for (int i = 0; i < size; i++) {
    cout << array3[i] << "  ";
  }
cout << "\nUsing Quick Sort: " << endl;
  quickSort(array4, size);
  for (int i = 0; i < size; i++) {
    cout << array4[i] << "  ";
  }
cout << "\nUsing Merge Sort: " << endl;
  mergeSort(array5, size);

  for (int i = 0; i < size; i++) {
    cout << array5[i] << "  ";
  }

}

//---------------------------------------------------------------
void selectionSort(int A[], int len) {
  for (int i = len - 1; i > 0; i--) {                        //starts from the back
    int largest_index = 0;
    for (int j = 0; j <= i; j++) {                           //starts from the front
      if (A[largest_index] < A[j]) {                         //finds the largest number
        largest_index = j;                                    
      }
    }
    swap(A[i], A[largest_index]);                            //swaps
  }
}
//--------------------------------------------------------------
void bubbleSort(int A[], int len) {
  for (int i = 0; i < len; i++) {
    for (int j = i + 1; j < len; j++) {
      if (A[j] < A[i]) {
        swap(A[i], A[j]);
      }
    }
  }
}
//----------------------------------------------------------------
void insertionSort(int A[], int len) {
  for (int i = 1; i < len; i++) {                    
    int num = A[i];                                //uses num as a placeholder to save a[i] index
    for (int j = i - 1; j >= 0; j--) {              
      if (A[j] > num) {                             //if a[j] is greater than num then it will swap
        A[j + 1] = A[j];                            //shifts the number to the right
        A[j] = num;
      } else {
        break;                                      //if its not greater than nume it will break and start in next loop
      }
    }
  }
}
//--------------------------------------------- ----------------
void quickSort(int A[], int len)          //helper function that calls QUICKSORt
{
  QUICKSORT(A, 0, len-1);                   
}

void QUICKSORT(int A[], int p, int r) {
  if (p >= r) {
    return;
  }
  int q = Partition(A, p, r);                
  QUICKSORT(A, p, q - 1);                    //sorts left side
  QUICKSORT(A, q + 1, r);                    //sorts right side
}

int Partition(int A[], int p, int r) {
  int pivot = A[p];                          //sets pivot to the first index
  int q = p + 1;
  int i = p + 1;

  while (i <= r) {                          //continues while i is less than r
    if (A[i] <= pivot) {                      
      swap(A[q++], A[i]);                   //swaps the values
    }
    i++;
  }
  swap(A[p], A[q - 1]);
  return q - 1;
}
//---------------------------------------------------------
void mergeSort(int A[], int len) 
{
  MERGEsort(A, 0, len-1);                    //another helper function to call MERGEsort
}

void MERGEsort(int A[], int p, int r) {
  if (p == r) {
    return;
  }
  int q = (p + r) / 2;
  MERGEsort(A, p, q);
  MERGEsort(A, q + 1, r);
  MERGE(A, p, q, r);
}

void MERGE(int A[], int p, int q, int r) {
  int arrayB[r + 1];
  int i = p;
  int k = p;
  int j = q + 1;
  while (i <= q && j <= r) {                  //splitting the array into two
    if (A[i] <= A[j]) {
      arrayB[k++] = A[i++];
    } else {
      arrayB[k++] = A[j++];                  //sorts the array
    }
  }
  while (i <= q) {
    arrayB[k++] = A[i++];
  }
  while (j <= r) {
    arrayB[k++] = A[j++];
  }
  for(int i = p; i <= r; i++){
    A[i] = arrayB[i];
  }
}