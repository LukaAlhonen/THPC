#include <stdio.h>

int ackermann(int m, int n)
{
    int result = 0;
    
    if(m > 0 && n > 0) {
        result = ackermann(m - 1, ackermann(m, n - 1));
    } else if(m > 0 && n == 0) {
        result = ackermann(m - 1, 1);
    } else if(m == 0) {
        result = n + 1;
    }

    return result;
}

int main(int argc, char *argv[])
{
    int result = 0;
    int m = 4;
    int n = 1;
    result = ackermann(m, n);
    printf("Ackermann result: %d\n", result);

    return 0;
}