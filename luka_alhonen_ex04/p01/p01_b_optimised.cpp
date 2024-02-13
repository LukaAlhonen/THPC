#include <vector>
#include <chrono>
#include <iostream>

int main()
{
    const int n = 3000;

    std::vector<std::vector<float>> a(n, std::vector<float>(n));
    std::vector<std::vector<float>> b(n, std::vector<float>(n));
    std::vector<float> c(n);

    for (int k = 0; k < n; k++) {
        for (int h = 0; h < n; h++) {
            a[k][h] = (float) (h + k) + 1;
            b[k][h] = (float) (h + k) + 1;
            c[k] = k + 1;
        }
    }

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = b[i][j] / c[i];
        }
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    std::cout << elapsed.count() << std::endl;

    return 0;
}