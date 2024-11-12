#include <iostream>
#include <vector>
#include <cstdlib> 
using namespace std;


int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];  
    int i = low;  

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[high]);
    return i;
}

int quickselect(vector<int>& arr, int low, int high, int k) {
    if (low <= high) {
        int pivotIndex = partition(arr, low, high);

        if (pivotIndex == k)
            return arr[pivotIndex]; 
        else if (pivotIndex > k)
            return quickselect(arr, low, pivotIndex - 1, k);  
        else
            return quickselect(arr, pivotIndex + 1, high, k);  
    }
    return -1; 
}

int main() {
    vector<int> arr;
    int n;
    cout<<"Enter size of Array : ";
    cin>>n;
    arr.resize(n);
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    int k;
    cout<<"Enter the smallest number you want : ";
    cin>>k;  
    int result = quickselect(arr, 0, n - 1, k - 1);  

    cout << "The " << k << "rd smallest element is " << result << endl;
    return 0;
}
