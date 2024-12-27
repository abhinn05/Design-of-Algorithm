#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>

using namespace std;

int partitionArray(int arr[], int startIdx, int endIdx) {
    int pivotElement = arr[endIdx];
    int smallerElementIdx = startIdx - 1;

    for (int currentIdx = startIdx; currentIdx < endIdx; ++currentIdx) {
        if (arr[currentIdx] < pivotElement) {
            smallerElementIdx++;
            swap(arr[smallerElementIdx], arr[currentIdx]);
        }
    }
    swap(arr[smallerElementIdx + 1], arr[endIdx]);
    return smallerElementIdx + 1;
}

int randomPartitionArray(int arr[], int startIdx, int endIdx) {
    int randomPivotIdx = startIdx + rand() % (endIdx - startIdx + 1);
    swap(arr[randomPivotIdx], arr[endIdx]);
    return partitionArray(arr, startIdx, endIdx);
}

void randomizedQuickSort(int arr[], int startIdx, int endIdx) {
    if (startIdx < endIdx) {
        int partitionIdx = randomPartitionArray(arr, startIdx, endIdx);
        randomizedQuickSort(arr, startIdx, partitionIdx - 1);
        randomizedQuickSort(arr, partitionIdx + 1, endIdx);
    }
}

void evaluateSortPerformance(const vector<int>& inputData, const string& testCase, int dataSize) {
    int* arrCopy = new int[dataSize];
    copy(inputData.begin(), inputData.end(), arrCopy);

    auto startTime = chrono::high_resolution_clock::now();
    randomizedQuickSort(arrCopy, 0, dataSize - 1);
    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<long double> elapsedTime = endTime - startTime;

    ofstream outputFile("sorting_performance_4.csv", ios::app);
    outputFile << testCase << "," << dataSize << "," << elapsedTime.count() << "\n";
    outputFile.close();

    delete[] arrCopy;
}

int main() {
    srand(time(0));

    ofstream outputFile("sorting_performance_4.csv");
    outputFile << "Test Case,Array Size,Time (seconds)\n"; // Write CSV header
    outputFile.close();

    vector<int> randomValues, sortedValues, reverseSortedValues, identicalValues;

    vector<int> testSizes = {100, 1000, 10000};

    for (int size : testSizes) {
        randomValues.clear();
        sortedValues.clear();
        reverseSortedValues.clear();
        identicalValues.clear();

        for (int i = 0; i < size; ++i) {
            int randomValue = rand() % size;
            randomValues.push_back(randomValue);
            sortedValues.push_back(i);
            reverseSortedValues.push_back(size - i - 1);
            identicalValues.push_back(42); 
        }

        evaluateSortPerformance(randomValues, "Random", size);
        evaluateSortPerformance(sortedValues, "Sorted", size);
        evaluateSortPerformance(reverseSortedValues, "Reverse-Sorted", size);
        evaluateSortPerformance(identicalValues, "Duplicate", size);
    }

    cout << "Performance testing complete. Results written to sorting_performance_4.csv" << endl;

    return 0;
}
