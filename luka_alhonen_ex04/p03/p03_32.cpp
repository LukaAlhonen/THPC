
#include <iostream>
#include <cstdint>
#include <chrono>

double unrolled_loop_32(int32_t *a, int size)
{
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i += 32) {
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
		a[i + 16] = i + 16;
		a[i + 17] = i + 17;
		a[i + 18] = i + 18;
		a[i + 19] = i + 19;
		a[i + 20] = i + 20;
		a[i + 21] = i + 21;
		a[i + 22] = i + 22;
		a[i + 23] = i + 23;
		a[i + 24] = i + 24;
		a[i + 25] = i + 25;
		a[i + 26] = i + 26;
		a[i + 27] = i + 27;
		a[i + 28] = i + 28;
		a[i + 29] = i + 29;
		a[i + 30] = i + 30;
		a[i + 31] = i + 31;
    }
    auto finnish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finnish - start;

    return elapsed.count();
}

int main()
{
    int size = 1048576;
    int32_t a[size];

    double duration = unrolled_loop_32(a, size);
    std::cout << duration << std::endl;

    return 0;
}
