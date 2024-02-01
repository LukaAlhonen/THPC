#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define N 15000
int a[N][N];
#define NPRINT 500

void main() {
  int i,j;
  clock_t t1,t2;
  double cpu_time;


  /* Begin measurement */
  t1 = clock();
  
  for (i=0;i<N;i++) 
    for (j=0;j<N;j++) 
      a[i][j]=(i+j)/2;
  
  t2 = clock();
  cpu_time = (double) (t2-t1) / CLOCKS_PER_SEC;
  /* End measurement */

  for (i=0;i<N;i+=NPRINT)
    for (j=0;j<N;j+=NPRINT)
      printf("%d ",a[i][j]);
  printf("\n");

  printf("Time elapsed: %f s\n", cpu_time);
}


  
  
    
