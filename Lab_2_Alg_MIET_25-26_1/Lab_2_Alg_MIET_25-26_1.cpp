#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

long get_time() {
    __asm rdtsc;
}
int main() {
    std::vector<int> vec;

    /*for (int i = 0; i < 20; ++i) {
        long a = get_time();
        vec.push_back(i);
        long b = get_time();
        std::cout << std::setw(3) << i + 1 << std::setw(3) << i << std::setw(7) << b - a << std::setw(7) << vec.capacity() << "\n";
    }
    std::cout << std::count(vec.begin(), vec.end(), 5);
    
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << "\n";
    }*/

    int mas[20];
    for (int i = 0; i < 20; ++i) {
        long a = get_time();
        mas[i] = i;
        long b = get_time();
        std::cout << std::setw(3) << i + 1 << std::setw(3) << i << std::setw(7) << b - a << std::setw(7) << vec.capacity() << "\n";
    }
    vec.clear();
    std::cout << vec.size() << "\n" << vec.capacity() << "\n";
    return 0;
}
