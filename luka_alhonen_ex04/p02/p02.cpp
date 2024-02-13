#include <iostream>
#include <vector>
#include <chrono>
#include <cstring>

#define N 1000

void init_matrices(std::vector<std::vector<int>> &a, std::vector<std::vector<int>> &b)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i][j] = i + j + 1;
            b[i][j] = i + j + 1;
        }
    }
}

std::vector<std::vector<int>> transpose(std::vector<std::vector<int>> &my_vec)
{
    std::vector<std::vector<int>> transposed(N, std::vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            transposed[j][i] = my_vec[i][j];
        }
    }

    return transposed;
}

double matrix_mult(std::vector<std::vector<int>> &a, std::vector<std::vector<int>> &b)
{
    std::vector<std::vector<int>> c(N, std::vector<int>(N));

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    auto finnish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finnish - start;

    std::vector<std::vector<int>>().swap(c);

    return elapsed.count();
}

int main(int argc, char** argv)
{
    std::vector<std::vector<int>> a(N, std::vector<int>(N));
    std::vector<std::vector<int>> b(N, std::vector<int>(N));

    double duration;

    if (strcmp(argv[1], "b") == 0) {
        std::vector<std::vector<int>> a_T(N, std::vector<int>(N));
        a_T = transpose(a);
        duration = matrix_mult(a_T, b);
    } else if (strcmp(argv[1], "c") == 0) {
        std::vector<std::vector<int>> b_T(N, std::vector<int>(N));
        b_T = transpose(b);
        duration = matrix_mult(a, b_T);
    } else {
        duration = matrix_mult(a, b);
    }

    std::cout << duration << std::endl;

    return 0;
}