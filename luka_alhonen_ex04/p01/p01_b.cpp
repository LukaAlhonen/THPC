#include <vector>

int main()
{
    const int n = 3000;
    std::vector<std::vector<float>> a(n, std::vector<float>(n));
    std::vector<std::vector<float>> b(n, std::vector<float>(n));
    std::vector<float> c(n);

    for (int k = 0; k < n - 1; k++) {
        a[k][k] = (float) k;
        b[k][k] = (float) k;
        c[k] = k;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            a[i][j] = b[i][j] / c[i];
        }
    }

    return 0;
}