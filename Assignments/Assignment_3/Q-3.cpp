#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib> 

using namespace std;

int findMedian(vector<int>& arr, int low, int size) {
    vector<int> temp(arr.begin() + low, arr.begin() + low + size);
    sort(temp.begin(), temp.end());
    return temp[size / 2];
}

int partition(vector<int>& arr, int low, int high, int pivot) {
    for (int i = low; i <= high; ++i) {
        if (arr[i] == pivot) {
            swap(arr[i], arr[high]);
            break;
        }
    }
    int i = low;
    for (int j = low; j < high; ++j) {
        if (arr[j] < arr[high]) {
            swap(arr[i], arr[j]);
            ++i;
        }
    }
    swap(arr[i], arr[high]);
    return i;
}

int medianOfMedians(vector<int>& arr, int low, int high, int medianIdx) {
    if (high - low + 1 <= 5) {
        sort(arr.begin() + low, arr.begin() + high + 1);
        return arr[low + (high - low) / 2];
    }

    int n = high - low + 1;
    vector<int> medians((n + 4) / 5);  
    int i;
    for (i = 0; i < n / 5; ++i) {
        medians[i] = findMedian(arr, low + i * 5, 5);
    }
    if (n % 5 != 0) {  
        medians[i] = findMedian(arr, low + i * 5, n % 5);
        ++i;
    }

    int medianOfMediansValue = medianOfMedians(medians, 0, i - 1, i / 2);

    int partitionIdx = partition(arr, low, high, medianOfMediansValue);

    if (partitionIdx == medianIdx) {
        return arr[partitionIdx];
    } else if (partitionIdx > medianIdx) {
        return medianOfMedians(arr, low, partitionIdx - 1, medianIdx);
    } else {
        return medianOfMedians(arr, partitionIdx + 1, high, medianIdx);
    }
}

int findMedian(vector<int>& arr) {
    int n = arr.size();
    return medianOfMedians(arr, 0, n - 1, n / 2);
}

void generate_random_numbers(vector<int>& arr, int n) {
    arr.resize(n); 
    for (int i = 0; i < n; ++i) {
        arr[i] = rand();  
    }
}

int main() {
    vector<int> arr;
    int n;
    cout << "Enter Size of array: ";
    cin >> n;
    generate_random_numbers(arr, n);
    int median = findMedian(arr);
    cout << "Median is: " << median << endl;
    return 0;
}
