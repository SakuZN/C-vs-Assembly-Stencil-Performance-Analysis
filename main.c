#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int main() {
	int exponentSize = 0;
	int runTime = 0;
	//Get the size of the exponent
	printf("Enter the size of Vector X (in exponent): ");
	scanf("%d", &exponentSize);
	//Get the number of times to run the program
	printf("Enter the number of times to run the program: ");
	scanf("%d", &runTime);

	int size = pow(2, exponentSize);

	double* vectorX = (double*)malloc(size * sizeof(double));

	if (vectorX == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return 1;
	}

	srand((unsigned int)time(NULL));

	// Populate vectorX with random double values
	for (int i = 0; i < size; i++) {

		vectorX[i] = ((double)rand() / (double)RAND_MAX) * 100.0;
	}

	return 0;
}