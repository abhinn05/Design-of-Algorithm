#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>

using namespace std;

int getMax(const vector<int>& arr) {
    int max = arr[0];
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

void countSort(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(vector<int>& arr) {
    int max = getMax(arr);
    for (int i = 1; max / i > 0; i *= 10)
        countSort(arr, i);
}

void testSortingPerformance(const vector<int>& arr, const string& caseName, int arraySize) {
    vector<int> arrCopy = arr;

    auto start = chrono::high_resolution_clock::now();
    radixSort(arrCopy);  
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    ofstream file("sorting_performance_2.csv", ios::app);
    file << caseName << "," << arraySize << "," << duration.count() << "\n";
}

int main() {
    ofstream file("sorting_performance_2.csv");
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

    cout << "Performance testing complete. Results written to sorting_performance_2.csv" << endl;

    return 0;
}
