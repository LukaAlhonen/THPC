#include <stdio.h>

int
main()
{
  int a[10];

  int i = 0;

  while(1) {
    printf("value: %d\tindex: %d\n", a[i], i);
    i++;
  }

  return 0;
}
