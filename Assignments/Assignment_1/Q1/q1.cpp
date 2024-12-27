#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>

using namespace std;

void insertionSort(vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void testSortingPerformance(const vector<int>& arr, const string& caseName, int arraySize) {
    vector<int> arrCopy = arr;  
    auto start = chrono::high_resolution_clock::now();
    insertionSort(arrCopy);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    ofstream file("sorting_performance_1.csv", ios::app);
    file << caseName << "," << arraySize << "," << duration.count() << "\n";
}

int main() {
    ofstream file("sorting_performance_1.csv");
    file << "Test Case,Array Size,Time (seconds)\n"; 
    file.close();

    vector<int> randomData, sortedData, reverseData, duplicateData;

    vector<int> testSizes = {100, 1000, 10000};

    for (int size : testSizes) {
        randomData.clear();
        sortedData.clear();
        reverseData.clear();
        duplicateData.clear();

        for (int i = 0; i < size; ++i) {
            randomData.push_back(rand() % size);
            sortedData.push_back(i);
            reverseData.push_back(size - i);
            duplicateData.push_back(42);  
        }

        testSortingPerformance(randomData, "Random", size);
        testSortingPerformance(sortedData, "Sorted", size);
        testSortingPerformance(reverseData, "Reverse-Sorted", size);
        testSortingPerformance(duplicateData, "Duplicate", size);
    }

    cout << "Performance testing complete. Results written to sorting_performance_1.csv" << endl;

    return 0;
}
