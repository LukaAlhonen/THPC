#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double expensive_operation(int n) {
    double res = 0.0;
    clock_t t1,t2;
    
    t1 = clock();
    for (int k = 0; k < n; k++) {
        res += exp(sin(k/1000000));
    }
    t2 = clock();

    return (double)(t2 - t1) / CLOCKS_PER_SEC;
}

double expensive_operation_print(int n) {
    double res = 0.0;
    clock_t t1,t2;
    
    t1 = clock();    
    for (int k = 0; k < n; k++) {
        res += exp(sin(k/1000000));
        printf("res: %f\n", res);
    }
    t2 = clock();

    return (double)(t2 - t1) / CLOCKS_PER_SEC;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Too few arguments, please specify number of iterations\n");
        return 1;
    }

    clock_t t1,t2;
    double cpu_time;
    double res = 0.0;

    int n = atoi(argv[1]);
    if (n == 0 && argv[1][0] != '0') {
        printf("Invalid input\n");
        return 1;
    }
    
    if (argc == 3 && strcmp(argv[2], "verbose") == 0) {
        cpu_time = expensive_operation_print(n);
    } else {
        cpu_time = expensive_operation(n);
    }

    printf("Elapsed CPU time: %f\n", cpu_time);

    return 0;
}
