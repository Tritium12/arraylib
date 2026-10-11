#include "arraylib.h" 
#include <cstddef> 
#include <iomanip> 
#include <iostream> 
int main() { 
    int manager_sales[] = {184000, 213000, 176000, 245000, 198000, 221000 }; 
    const std::size_t n = sizeof(manager_sales) / sizeof(manager_sales[0]); 
    std::cout << "Количество элементов: " << n << '\n'; 
    std::cout << "Сумма продаж: " << arr_sum(manager_sales, n) << '\n'; 
    std::cout << "Худший результат: " << arr_min(manager_sales, n) << '\n'; 
    std::cout << "Лучший результат: " << arr_max(manager_sales, n) << '\n'; 
    std::cout << "Средний результат: " << arr_average(manager_sales, n) << '\n'; 
    std::cout << "Медиана результатов: " << arr_median(manager_sales, n) << '\n'; 

    return 0; 
} 