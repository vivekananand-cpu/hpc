#include <iostream>
#include <vector>
#include <omp.h>

void parallelBubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    bool swapped = false;

    #pragma omp parallel
    {
        do {
            swapped = false;
            #pragma omp for
            for (int i = 0; i < n - 1; i++) {
                if (arr[i] > arr[i + 1]) {
                    std::swap(arr[i], arr[i + 1]);
                    swapped = true;
                }
            }
        } while (swapped);
    }
}

int main() {
    std::vector<int> arr = {7, 2, 5, 1, 8, 3};

    parallelBubbleSort(arr);

    std::cout << "Sorted array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
