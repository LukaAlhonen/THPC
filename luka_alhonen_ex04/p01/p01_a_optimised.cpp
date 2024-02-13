#include <vector>
#include <chrono>
#include <iostream>

int main(int argc, char* argv[])
{
    const int n = 10000000;
    std::vector <float> a(n);
    std::vector <float> b(n);

    for (int j = 0; j < n - 1; j++) {
        a[j] = (float) j;
        b[j] = (float) j;
    }

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 500; i++) {
        a[i] = 4.0 * b[i] + b[i+1];
    }
    for (int i = 500; i < n-2; i++) {
        a[i] = 4.0 * b[i+1] + b[i];
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    std::cout << elapsed.count() << std::endl;

    return 0;
}