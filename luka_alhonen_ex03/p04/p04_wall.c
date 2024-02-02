#include <math.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double expensive_operation(int n) {
    double res = 0.0;
    struct timeval tp1, tp2;
    struct timezone tz1, tz2;
    double wall_time;
    gettimeofday(&tp1, &tz1);
    for (int k = 0; k < n; k++) {
        res += exp(sin(k/1000000));
    }
    gettimeofday(&tp2, &tz2);

    return (tp2.tv_sec - tp1.tv_sec) + (tp2.tv_usec - tp1.tv_usec) / 1000000.0;
}

double expensive_operation_print(int n) {
    double res = 0.0;
    struct timeval tp1, tp2;
    struct timezone tz1, tz2;
    gettimeofday(&tp1, &tz1);
    for (int k = 0; k < n; k++) {
        res += exp(sin(k/1000000));
        printf("res: %f\n", res);
    }
    gettimeofday(&tp2, &tz2);

    return (tp2.tv_sec - tp1.tv_sec) + (tp2.tv_usec - tp1.tv_usec) / 1000000.0;
}

int main(int argc, char **argv)
{
    if(argc < 2) {
        printf("Too few arguments, please specify number of iterations\n");
        return 1;
    }

    int n = atoi(argv[1]);
    if (n == 0 && argv[1][0] != '0') {
        printf("Invalid input\n");
        return 1;
    }

    double wall_time;

    if (argc == 3 && strcmp(argv[2], "verbose") == 0) {
        wall_time = expensive_operation_print(n);
    } else {
        wall_time = expensive_operation(n);
    }

    printf("Time elapsed actual time: %f s\n", wall_time);
    return 0;
}
