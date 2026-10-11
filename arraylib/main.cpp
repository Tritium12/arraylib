#include "arraylib.h" 
#include <iostream> 
int main() { 
    int data[] = {5, 3, 8, 1, 9, 2}; 
    std::size_t n = sizeof(data) / sizeof(data[0]);

    std::cout << "Sum: " << arr_sum(data, n) << "\n";
    std::cout << "Max: " << arr_max(data, n) << "\n";
    std::cout << "Min: " << arr_min(data, n) << "\n";
    std::cout << "Average: " << arr_average(data, n) << "\n";
    std::cout << "Positive: " << arr_count_positive(data, n) << "\n";
    std::cout << "Negative: " << arr_count_negative(data, n) << "\n";
    std::cout << "Zero: " << arr_count_zero(data, n) << "\n";
    std::cout << "Product: " << arr_product(data, n) << "\n";
    std::cout << "Median: " << arr_median(data, n) << "\n";
    return 0;
}