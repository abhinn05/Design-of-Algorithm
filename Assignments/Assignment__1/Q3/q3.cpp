#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>

using namespace std;

int partitionArray(vector<int>& arr, int low, int high) {
    int pivotElement = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivotElement) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

    void quickSortArray(vector<int>& arr, int low, int high) {
    if (low < high) {
        int partitionIndex = partitionArray(arr, low, high);
        quickSortArray(arr, low, partitionIndex - 1);
        quickSortArray(arr, partitionIndex + 1, high);
    }
}

void evaluateSortPerformance(const vector<int>& data, const string& scenario, int dataSize) {
    vector<int> testArray = data; 

    auto startTime = chrono::high_resolution_clock::now();
    quickSortArray(testArray, 0, dataSize - 1);
    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<long double> elapsedTime = endTime - startTime;

    ofstream resultsFile("sorting_performance_3.csv", ios::app);
    resultsFile << scenario << "," << dataSize << "," << elapsedTime.count() << "\n";
    resultsFile.close();
}

int main() {
    ofstream resultsFile("sorting_performance_3.csv");
    resultsFile << "Test Case,Array Size,Time (seconds)\n"; // Write CSV header
    resultsFile.close();

    vector<int> randomArray, sortedArray, reverseSortedArray, duplicateArray;

    vector<int> testSizes = {100, 1000, 10000};

    for (int dataSize : testSizes) {
        randomArray.clear();
        sortedArray.clear();
        reverseSortedArray.clear();
        duplicateArray.clear();

        for (int i = 0; i < dataSize; ++i) {
            int value = rand() % dataSize;
            randomArray.push_back(value);
            sortedArray.push_back(i);
            reverseSortedArray.push_back(dataSize - i);
            duplicateArray.push_back(42);  
        }

        evaluateSortPerformance(randomArray, "Random", dataSize);
        evaluateSortPerformance(sortedArray, "Sorted", dataSize);
        evaluateSortPerformance(reverseSortedArray, "Reverse-Sorted", dataSize);
        evaluateSortPerformance(duplicateArray, "Duplicate", dataSize);
    }

    cout << "Performance testing complete. Results written to sorting_performance_3.csv" << endl;

    return 0;
}
