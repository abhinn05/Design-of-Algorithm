#include <iostream>
#include <vector>
using namespace std;

int findMin(const vector<int>& arr) {
    int minElem = arr[0];
    for (int i = 1; i < static_cast<int>(arr.size()); i++) {
        if (arr[i] < minElem)
            minElem = arr[i];
    }
    return minElem;
}

int findMax(const vector<int>& arr) {
    int maxElem = arr[0];
    for (int i = 1; i <static_cast<int>(arr.size()); i++) {
        if (arr[i] > maxElem)
            maxElem = arr[i];
    }
    return maxElem;
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
    cout << "Minimum element: " << findMin(arr) << endl;
    cout << "Maximum element: " << findMax(arr) << endl;
    return 0;
}
