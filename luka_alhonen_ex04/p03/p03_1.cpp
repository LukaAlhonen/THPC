
#include <iostream>
#include <cstdint>
#include <chrono>

double unrolled_loop_1(int32_t *a, int size)
{
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i += 1) {
        a[i] = i;
    }
    auto finnish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finnish - start;

    return elapsed.count();
}

int main()
{
    int size = 1048576;
    int32_t a[size];

    double duration = unrolled_loop_1(a, size);
    std::cout << duration << std::endl;

    return 0;
}
