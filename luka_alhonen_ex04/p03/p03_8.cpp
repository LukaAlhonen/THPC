
#include <iostream>
#include <cstdint>
#include <chrono>

double unrolled_loop_8(int32_t *a, int size)
{
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i += 8) {
        a[i] = i;
		a[i + 1] = i + 1;
		a[i + 2] = i + 2;
		a[i + 3] = i + 3;
		a[i + 4] = i + 4;
		a[i + 5] = i + 5;
		a[i + 6] = i + 6;
		a[i + 7] = i + 7;
    }
    auto finnish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finnish - start;

    return elapsed.count();
}

int main()
{
    int size = 1048576;
    int32_t a[size];

    double duration = unrolled_loop_8(a, size);
    std::cout << duration << std::endl;

    return 0;
}
