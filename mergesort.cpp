// Online C++ compiler to run C++ program online
#include <iostream>
#include<vector>
#include<omp.h>
using namespace std;

void merge(vector<int>& arr, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    vector<int> L(n1), R(n2);

    // Copy data to temporary arrays
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    i = 0;  // Initial index of first subarray
    j = 0;  // Initial index of second subarray
    k = left;  // Initial index of merged subarray

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void parallelMerge(vector<int>& arr,int left,int right){
    if (left < right) {
        int mid = left + (right - left) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMerge(arr, left, mid);
            }

            #pragma omp section
            {
                parallelMerge(arr, mid + 1, right);
            }
        }

        merge(arr, left, mid, right);
    }
}
int main() {
    // Write C++ code here
    vector<int> arr = {7, 2, 5, 1, 8, 3};
    parallelMerge(arr,0,arr.size()-1);
    for(int num:arr){
        cout<<num<<" ";
    }
    

    return 0;
}