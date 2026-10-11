#include <iostream>
#include <vector>
#include <algorithm> 
using namespace::std;

int arr_sum(const int* arr, std::size_t n) { 
    int s = 0; 
    for (std::size_t i = 0; i < n; ++i) { 
        s += arr[i]; 
    } 
    return s; 
}

int arr_max(const int* a, std::size_t n) { 
int m = a[0]; 
for (std::size_t i = 1; i < n; ++i) if (a[i] > m) m = a[i]; 
return m; 
} 

int arr_min(const int* a, std::size_t n) { 
int m = a[0]; 
for (std::size_t i = 1; i < n; ++i) if (a[i] < m) m = a[i]; 
return m; 
} 

int arr_average(const int* arr, std::size_t n) { 
    double s = 0; 
    for (std::size_t i = 0; i < n; ++i) { 
        s += arr[i]; 
    } 
    s = s/double(n);
    return s; 
}

int arr_count_positive(const int* arr, std::size_t n) {
    int count = 0;
    for (std::size_t i = 0; i < n; ++i) {
        if (arr[i] > 0) count++;
    }
    return count;
}

int arr_count_negative(const int* arr, std::size_t n) {
    int count = 0;
    for (std::size_t i = 0; i < n; ++i) {
        if (arr[i] < 0) count++;
    }
    return count;
}
int arr_count_zero(const int* arr, std::size_t n) {
    int count = 0;
    for (std::size_t i = 0; i < n; ++i) {
        if (arr[i] == 0) count++;
    }
    return count;
}


int arr_product(const int* arr, std::size_t n) {
    if (n == 0) return 0;
    int p = 1;
    for (std::size_t i = 0; i < n; ++i) {
        p *= arr[i];
    }
    return p;
}

double arr_median(const int* arr, std::size_t n){
    std::vector<int> copy(arr, arr + n);
    std::sort(copy.begin(), copy.end());
    if (n%2 == 1) {
        return copy[n/2];
    }
    else {
        return ((copy[n/2 - 1] + copy[n/2])/2.0);
    }
}

