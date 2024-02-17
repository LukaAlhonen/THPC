
#include <iostream>
#include <cstdint>
#include <chrono>

double unrolled_loop_16(int32_t *a, int size)
{
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i += 16) {
        a[i] = i;
		a[i + 1] = i + 1;
		a[i + 2] = i + 2;
		a[i + 3] = i + 3;
		a[i + 4] = i + 4;
		a[i + 5] = i + 5;
		a[i + 6] = i + 6;
		a[i + 7] = i + 7;
		a[i + 8] = i + 8;
		a[i + 9] = i + 9;
		a[i + 10] = i + 10;
		a[i + 11] = i + 11;
		a[i + 12] = i + 12;
		a[i + 13] = i + 13;
		a[i + 14] = i + 14;
		a[i + 15] = i + 15;
    }
    auto finnish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finnish - start;

    return elapsed.count();
}

int main()
{
    int size = 1048576;
    int32_t a[size];

    double duration = unrolled_loop_16(a, size);
    std::cout << duration << std::endl;

    return 0;
}
