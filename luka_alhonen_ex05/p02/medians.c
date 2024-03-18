#include <stdio.h>

int main(int argc, char** argv)
{
	FILE* file;
	double value, sum;
	int count;

	for (int i = 1; i < argc; i++) {
		char* filename = argv[i];
		file = fopen(filename, "r");
		if (file != NULL) {
			value = 0.0;
			sum = 0.0;
			count = 0;

			while(fscanf(file, "%lf", &value) == 1) {
				sum += value;
				count++;
			}

			if (count > 0) {
				double average = sum / count;
				printf("Average of %s: %f\n", filename, average);
			}
		}
		fclose(file);
	}

	return 0;
}