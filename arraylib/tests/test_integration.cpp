#include "arraylib.h" 
#include <cassert> 
#include <cmath> 
#include <iostream> 
static bool close(double a, double b, double eps = 1e-9) { 
return std::fabs(a - b) < eps; 
} 
int main() { 
    int data[] = {7, 3, 9, 1, 5, 8, 2, 6, 4}; 
    const std::size_t n = sizeof(data) / sizeof(data[0]); 
    // Случай 1: сумма и максимум согласованы 
    assert(arr_sum(data, n) == 45); 
    assert(arr_max(data, n) == 9); 
    // Случай 2: среднее между min и max 
    double avg = arr_average(data, n); 
    assert(avg >= static_cast<double>(arr_min(data, n))); 
    assert(avg <= static_cast<double>(arr_max(data, n))); 
    // Случай  4: медиана отсортированного массива 
    int sorted[] = {1, 2, 3, 4, 5, 6, 7}; 
    assert(close(arr_median(sorted, 7), 4.0)); 
    std::cout << "[integration] All tests passed\n"; 
    return 0; 
}