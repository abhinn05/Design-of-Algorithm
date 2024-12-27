#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <climits>
#include <algorithm>

using namespace std;

void mergeArrays(vector<int>& array, int start, int middle, int end) {
    int leftSize = middle - start + 1;
    int rightSize = end - middle;

    vector<int> leftPart(leftSize + 1);
    vector<int> rightPart(rightSize + 1);

    copy(array.begin() + start, array.begin() + middle + 1, leftPart.begin());
    copy(array.begin() + middle + 1, array.begin() + end + 1, rightPart.begin());

    leftPart[leftSize] = INT_MAX;
    rightPart[rightSize] = INT_MAX;

    int leftIndex = 0, rightIndex = 0;
    for (int i = start; i <= end; i++) {
        if (leftPart[leftIndex] <= rightPart[rightIndex]) {
            array[i] = leftPart[leftIndex++];
        } else {
            array[i] = rightPart[rightIndex++];
        }
    }
}

void mergeSort(vector<int>& array, int start, int end) {
    if (start < end) {
        int middle = start + (end - start) / 2;
        mergeSort(array, start, middle);
        mergeSort(array, middle + 1, end);
        mergeArrays(array, start, middle, end);
    }
}

void evaluateSortingPerformance(const vector<int>& data, const string& testCase, int arrayLength) {
    vector<int> testArray = data;  

    auto startTime = chrono::high_resolution_clock::now();
    mergeSort(testArray, 0, arrayLength - 1);
    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedTime = endTime - startTime;

    ofstream outputFile("sorting_performance_2.csv", ios::app);
    outputFile << testCase << "," << arrayLength << "," << elapsedTime.count() << "\n";
}

int main() {
    ofstream outputFile("sorting_performance_2.csv");
    outputFile << "Test Case,Array Size,Time (seconds)\n"; // Write CSV header
    outputFile.close();

    vector<int> randomArray, sortedArray, reverseSortedArray, duplicateArray;

    vector<int> testSizes = {100, 1000, 10000};

    for (int length : testSizes) {
        randomArray.clear();
        sortedArray.clear();
        reverseSortedArray.clear();
        duplicateArray.clear();

        for (int i = 0; i < length; ++i) {
            randomArray.push_back(rand() % length);
            sortedArray.push_back(i);
            reverseSortedArray.push_back(length - i);
            duplicateArray.push_back(42);  
        }

        evaluateSortingPerformance(randomArray, "Random", length);
        evaluateSortingPerformance(sortedArray, "Sorted", length);
        evaluateSortingPerformance(reverseSortedArray, "Reverse-Sorted", length);
        evaluateSortingPerformance(duplicateArray, "Duplicate", length);
    }

    cout << "Performance testing complete. Results written to sorting_performance_2.csv" << endl;

    return 0;
}
