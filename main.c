#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


void calc1D_Stencil(double* vectorX, double* vectorY, int size);
void printVectorY(double* vectorY, int size);
int main() {

	int exponentSize = 0;
	int runTime = 0;
	//Get the size of the exponent
	printf("Enter the size of Vector X (in 2^x min 3): ");
	scanf_s("%d", &exponentSize);
	while (exponentSize < 3) {
		printf("Enter the size of Vector X (in 2^x min 3): ");
		scanf_s("%d", &exponentSize);
	}
	/*
	//Get the number of times to run the program
	printf("Enter the number of times to run the program: ");
	scanf("%d", &runTime);
	*/
	int size = (int)(pow(2, exponentSize) + 0.5);
	printf("Size of Vector X: %d\n", size);
	int vectorYSize = size - 6;

	double* vectorX = (double*)malloc(size * sizeof(double));
	// size of vectorY is n - 6
	double* vectorY = (double*)malloc((vectorYSize) * sizeof(double));

	if (vectorX == NULL || vectorY == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		free(vectorX);
		free(vectorY);
		return 1;
	}

	srand((unsigned int)time(NULL));

	// Populate vectorX with random double values
	for (int i = 0; i < size; i++) {

		vectorX[i] = ((double)rand() / (double)RAND_MAX) * 100.0;
	}

	//print the values first
	//calc1D_Stencil(vectorX, vectorY, size);
	//printVectorY(vectorY, vectorYSize);

	
	// Calculate the time taken by calc1D_Stencil() 
	clock_t t;
	t = clock();

	// Repeat the stencil computation multiple times
	for (int i = 0; i < 1000; ++i) {
		calc1D_Stencil(vectorX, vectorY, size);
	}

	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds 

	printf("\ncalc1D_Stencil() took %f seconds in average to execute \n", time_taken / 1000); // average per run

	free(vectorX);
	free(vectorY);
	



	return 0;
}

void calc1D_Stencil(double* vectorX, double* vectorY, int size) {
	int limit = size - 3;
	int yIndex = 0;
	for (int i = 3; i < limit; i++) {
		vectorY[yIndex] = (vectorX[i - 3] + vectorX[i - 2] + vectorX[i - 1] + vectorX[i] + vectorX[i + 1] + vectorX[i + 2] + vectorX[i + 3]);
		yIndex++;
	}
}

void printVectorY(double* vectorY, int size) {
	for (int i = 0; i < size; i++) {
		printf("Y[%d] = %f\n", i, vectorY[i]);
	}
}