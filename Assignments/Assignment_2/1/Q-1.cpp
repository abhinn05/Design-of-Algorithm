#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>


using namespace std;

void InsertionSort(vector<float>& arr) {
    size_t n = arr.size();
    for (size_t i = 1; i < n; i++) {
        float key = arr[i];
        int j = static_cast<int>(i) - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void BucketSort(vector<float>& arr) {
    size_t n = arr.size();
    vector<vector<float>> buckets(10);
    for (size_t i = 0; i < n; i++) {
        float value = arr[i];
        if (value < 0) value = 0;
        if (value > 1) value = 1;
        int index = static_cast<int>(value * 10);
        if (index >= 10) index = 9;
        buckets[index].push_back(arr[i]);
    }
    size_t index = 0;
    for (size_t i = 0; i < 10; i++) {
        InsertionSort(buckets[i]);
        for (float num : buckets[i]) {
            arr[index++] = num;
        }
    }
}

void testSortingPerformance(vector<float>& arr, const string& caseName, int arraySize) {
    vector<float> arrCopy = arr;
    auto start = chrono::high_resolution_clock::now();
    BucketSort(arrCopy);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    ofstream file("sorting_performance_1.csv", ios::app);
    file << caseName << "," << arraySize << "," << duration.count() << "\n";
}

int main() {
    ofstream file("sorting_performance_1.csv");
    file << "Test Case,Array Size,Time (seconds)\n";
    file.close();

    vector<float> randomData, sortedData, reverseData, duplicateData;
    vector<int> testSizes = {100, 1000, 10000};

    for (int size : testSizes) {
        randomData.clear();
        sortedData.clear();
        reverseData.clear();
        duplicateData.clear();

        for (int i = 0; i < size; ++i) {
            randomData.push_back(static_cast<float>(rand()) / RAND_MAX);
            sortedData.push_back(static_cast<float>(i) / size);
            reverseData.push_back(static_cast<float>(size - i) / size);
            duplicateData.push_back(0.42f);
        }

        testSortingPerformance(randomData, "Random", size);
        testSortingPerformance(sortedData, "Sorted", size);
        testSortingPerformance(reverseData, "Reverse-Sorted", size);
        testSortingPerformance(duplicateData, "Duplicate", size);
    }

    cout << "Performance testing complete. Results written to sorting_performance_1.csv" << endl;

    return 0;
}
