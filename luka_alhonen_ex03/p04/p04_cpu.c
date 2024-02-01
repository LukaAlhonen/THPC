#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    clock_t t1,t2;
    double cpu_time;
    int n = 1000000;
    double res = 0.0;

    t1 = clock();
    for (int k = 0; k < n; k++) {
        res += exp(sin(k/1000000));
        printf("res: %f\n", res);
    }
    t2 = clock();
    cpu_time = (double) (t2-t1) / CLOCKS_PER_SEC;
    printf("Elapsed CPU time: %f\n", cpu_time);

    return 0;
}
