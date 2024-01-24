#include <stdio.h>
#include <math.h>
#include <time.h>

int
main()
{
    // Variables for measuring cpu time
    clock_t start, end;
    double cpu_time1, cpu_time2, cpu_time3;

    int n = 200000000;
    float res1 = 0.0; // 32 bit
    double res2 = 0.0; // 64 bit
    __float128 res3 = 0.0; // 128 bit

    // Sum with 32 bit float
    start = clock();
    for (int k = 0; k < n; k++) {
        res1 += expf(sinf(k/1000000));
    }
    end = clock();
    cpu_time1 = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    // Sum with 64 bit float
    start = clock();
    for (int k = 0; k < n; k++) {
        res2 += exp(sin(k/1000000));
    }
    end = clock();
    cpu_time2 = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Sum with 128 bit float
    start = clock();
    for (int k = 0; k < n; k++) {
        res3 += expl(sinl(k/1000000));
    }
    end = clock();
    cpu_time3 = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    // Print results
    printf("res1: %f\n", res1);
    printf("cpu_time for 32 bit float: %f\n", cpu_time1);
    
    printf("res2: %f\n", res2);
    printf("cpu_time for 64 bit float: %f\n", cpu_time2);
    
    printf("res3: %Lf\n", res3);
    printf("cpu_time for 128 bit float: %f\n", cpu_time3);

    return 0;
}