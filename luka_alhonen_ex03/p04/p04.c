#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    struct timeval *tp1, *tp2;
    struct timezone *tz1, *tz2;
    int n = 100000000;
    double res = 0.0;

    gettimeofday(tp1, tz1);
    for (int k = 0; k < n; k++) {
        res += exp(sin(k/1000000));
        printf("res: %f\n", res);
    }
    gettimeofday(tp2, tz2);

    printf("Time elapsed: %f s\n", (tp2->tv_sec - tp1->tv_sec) + (tp2->tv_usec - tp1->tv_usec) / 1000000.0);
    return 0;
}