#include <iostream>
#include <vector>
#include <ctime>
#include <cassert>
using namespace std;
/*
 * Benjamin Raiford
 * BubbleSort
 * October 3, 2019
 */

// MergeSort function declarations
void mergeSort(vector<int>& a, vector<int>& tmp, int left, int right);
void mergeSortedLists(vector<int>& a, vector<int>& tmp, int leftPos, int rightPos, int rightEnd);

// BubbleSort function declarations
void swap (int *a, int *b);
void bubbleSort(int *a, int size);

int main(int argc, char* argv[]) {
    //TEST: swap
    cout << "Testing Swap...";
    int* testArray = new int[2];
        *(testArray) = 7;
        *(testArray + 1) = 9;

    swap(testArray[0],testArray[1]);
    assert((testArray[0]==9) &&
        (testArray[1]==7));
    cout << " Test complete." << endl;

    //TEST: bubbleSort
    cout << "Testing bubbleSort...";
    int* bubbleArray = new int[5];
        *(bubbleArray) = 14;
        *(bubbleArray + 1) = 33;
        *(bubbleArray + 2) = 27;
        *(bubbleArray + 3) = 35;
        *(bubbleArray + 4) = 10;

    bubbleSort(bubbleArray, 5);
    for(int i = 1; i < 5; i++){
        assert(bubbleArray[i-1] <= bubbleArray[i]);
    }
    cout << " Test complete.\n" << endl;

    // get input: first is random seed, second is vector length
    int seed, length;
    seed = atoi(argv[1]);
    length = atoi(argv[2]);
    srand(seed);

    vector<int> v(length); // vector to be sorted
    vector<int> t(length); // temporary workspace

    // define an integer pointer dynamically allocate an array of integers
    int *array = new int[length];

    // initialize and print input
    cout << "Unsorted:" << endl;
    for (int & i : v) {
        i = rand() % 100;
        cout << i << "\t";
    }
    cout << endl << endl;

    // copy the random list of integers from vector to array
    for (unsigned long i = 0; i < v.size(); ++i) {
        array[i] = v.at(i);
    }

//bubbleSort
    // sort array using bubbleSort
    clock_t start_bubbleSort = clock();
    bubbleSort(array, length);
    clock_t end_bubbleSort = clock();

    // check output, make sure array is sorted after bubbleSort
    for (int i = 1; i < length; i++) {
        assert(array[i - 1] <= array[i]);
    }

    // print sorted array after bubbleSort
    cout << "BubbleSorted:" << endl;
    for (int i = 0; i < length; i++) {
        cout << array[i] << '\t';
    }
    cout << endl << endl;

//mergeSort
    // sort vector using mergeSort
    clock_t start_mergeSort = clock();
    mergeSort(v, t, 0, v.size() - 1);
    clock_t end_mergeSort = clock();

    // check output, make sure vector is sorted after mergeSort
    for (unsigned long i = 1; i < v.size(); i++) {
        assert(v.at(i - 1) <= v.at(i));
    }

    // print sorted vector after mergeSort
    cout << "MergeSorted:" << endl;
    for (int i : v) {
        cout << i << '\t';
    }
    cout << endl << endl;

//Print Times
    // print elapsed time for mergeSort and bubbleSort
    double elapsed_mergeSort = double(end_mergeSort - start_mergeSort) / CLOCKS_PER_SEC;
    double elapsed_bubbleSort = double(end_bubbleSort - start_bubbleSort) / CLOCKS_PER_SEC;

    cout << "BubbleSort time: " << elapsed_bubbleSort << endl;
    cout << "MergeSort time: " << elapsed_mergeSort << endl;

    delete[] array;//deallocate memory to prevent dangling pointers
    return 0;
}




void mergeSortedLists(vector<int>& a, vector<int>& tmp, int leftPos, int rightPos, int rightEnd) {
    int leftEnd = rightPos - 1;
    int tempPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    while (leftPos <= leftEnd && rightPos <= rightEnd) {
        if (a[leftPos] <= a[rightPos]) {
            tmp[tempPos++] = a[leftPos++];
        } else {
            tmp[tempPos++] = a[rightPos++];
        }

    }

    while (leftPos <= leftEnd) {
        tmp[tempPos++] = a[leftPos++];
    }
    while (rightPos <= rightEnd) {
        tmp[tempPos++] = a[rightPos++];
    }

    for (int i = 0; i < numElements; i++, --rightEnd) {
        a[rightEnd] = tmp[rightEnd];
    }
}
void mergeSort(vector<int>& a, vector<int>& tmp, int left, int right) {
    if (left < right) {
        int center = ( left + right ) / 2;
        mergeSort(a, tmp, left, center);
        mergeSort(a, tmp, center + 1, right);
        mergeSortedLists(a, tmp, left, center + 1, right);
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void bubbleSort(int *a, int size) {
    int n = size;
    while(n > 0) {
        for(int i = 0; i < size - 1; i++){
            if(*(a+i)> *(a+i+1)){
                swap(a+i, (a + i + 1));
            }
        }
        n--;
    }
}