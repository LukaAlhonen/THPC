#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init_array(float* a, int sz)
{
	for (int i = 0; i < sz; i++) {
		a[i] = i * 0.1f;
	}
}

double write_unformatted(float* a, int sz)
{
	clock_t start, end;
	double cpu_time_used;
	FILE* file = fopen("p01_unformatted.datc", "w");
	if (file != NULL) {
		start = clock();
		for (int i = 0; i < sz; i++) {
			fwrite((void*) &a[i], sizeof(a[i]), 1, file);
		}
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		fclose(file);
	}

	return cpu_time_used;

}

int main()
{
	double unformatted_time;
	int a_sz = 10000000;
	float* a = (float*) malloc(a_sz * sizeof(float));

	// Init array with single precision floats
	init_array(a, a_sz);

	// Write array to file unformatted
	unformatted_time = write_unformatted(a, a_sz);

	// Print cpu times
	printf("%f\n", unformatted_time);

	free(a);

	return 0;
}