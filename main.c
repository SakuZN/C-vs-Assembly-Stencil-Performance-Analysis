#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


void calc1D_Stencil(double* vectorX, double* vectorY, int size);
void printVectorY(double* vectorY, int size);
int main() {

	/*
	int exponentSize = 0;
	int runTime = 0;
	//Get the size of the exponent
	printf("Enter the size of Vector X (in 2^x min 3): ");
	scanf("%d", &exponentSize);
	while (exponentSize < 3) {
		printf("Enter the size of Vector X (in 2^x min 3): ");
		scanf("%d", &exponentSize);
	}
	//Get the number of times to run the program
	printf("Enter the number of times to run the program: ");
	scanf("%d", &runTime);
	int size = pow(2, exponentSize);

	double* vectorX = (double*)malloc(size * sizeof(double));
	// size of vectorY is n - 6
	double* vectorY = (double*)malloc((size - 6) * sizeof(double));

	if (vectorX == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return 1;
	}

	srand((unsigned int)time(NULL));

	// Populate vectorX with random double values
	for (int i = 0; i < size; i++) {

		vectorX[i] = ((double)rand() / (double)RAND_MAX) * 100.0;
	}

	free(vectorX);
	*/

	double vectorX[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	double vectorY[3] = { 0, 0, 0 };

	calc1D_Stencil(&vectorX, &vectorY, 9);
	printVectorY(&vectorY, 9);



	return 0;
}

void calc1D_Stencil(double* vectorX, double* vectorY, int size) {
	int limit = (size - 6) + 4;
	int yIndex = 0;
	for (int i = 3; i < limit; i++) {
		vectorY[yIndex] = (vectorX[i - 3] + vectorX[i - 2] + vectorX[i - 1] + vectorX[i] + vectorX[i + 1] + vectorX[i + 2] + vectorX[i + 3]);
		yIndex++;
	}
}

void printVectorY(double* vectorY, int size) {
	for (int i = 0; i < (size - 6); i++) {
		printf("%f\n", vectorY[i]);
	}
}