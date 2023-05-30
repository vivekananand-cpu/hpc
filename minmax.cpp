#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;
int main() {
    std::vector<int> numbers = {7, 2, 5, 1, 8, 3};
    int n = numbers.size();
    int minVal = numbers[0];
    int maxVal = numbers[0];
    int sum = 0;

    #pragma omp parallel for reduction(min:minVal) reduction(max:maxVal) reduction(+:sum)
    for (int i = 0; i < n; i++) {
        int num = numbers[i];
        minVal = std::min(minVal, num);
        maxVal = std::max(maxVal, num);
        sum += num;
    }

    double average = static_cast<double>(sum) / n;

    std::cout << "Minimum value: " << minVal << std::endl;
    std::cout << "Maximum value: " << maxVal << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Average: " << average << std::endl;

    return 0;
}
