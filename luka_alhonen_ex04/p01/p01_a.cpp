#include <vector>

int main(int argc, char* argv[])
{
    const int n = 10000000;
    std::vector <float> a(n);
    std::vector <float> b(n);

    for (int j = 0; j < n - 1; j++) {
        a[j] = (float) j;
        b[j] = (float) j;
    }

    // Loop a

    for (int i = 0; i < n - 2; i++) {
        if (i < 500) a[i] = 4.0 * b[i] + b[i+1];
        else a[i] = 4.0 * b[i+1] + b[i];
    }

    return 0;
}