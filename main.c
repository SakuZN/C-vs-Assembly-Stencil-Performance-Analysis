#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// vectorX -> [RCX], vectorY -> [RDX], size -> R8
extern double calc1D_Stencil_asmfunc(double* vectorX, double* vectorY, int size);
void calc1D_Stencil(double* vectorX, double* vectorY, int size);
void printVectorY(double* vectorY, int size);
double calculateAverage(const double timings[], int numElements);
void writeTimingsToCSV(const double cTimings[], const double asmTimings[], int iterations, int exponent);
int main() {

	int exponentSize = 0;
	const int runTime = 50;

	//Get the size of the exponent
	printf("Enter the size of Vector X (in 2^x min 3): ");
	scanf_s("%d", &exponentSize);
	while (exponentSize < 3) {
		printf("Enter the size of Vector X (in 2^x min 3): ");
		scanf_s("%d", &exponentSize);
	}

	int size = (int)(pow(2, exponentSize) + 0.5);
	printf("Size of Vector X: %d\n", size);
	int vectorYSize = size - 6;

	double* vectorX = (double*)malloc(size * sizeof(double));
	double* vectorY = (double*)malloc((vectorYSize) * sizeof(double));
	double* vectorX_asm = (double*)malloc(size * sizeof(double));
	double* vectorY_asm = (double*)malloc((vectorYSize) * sizeof(double));

	if (vectorX == NULL || vectorY == NULL || vectorX_asm == NULL || vectorY_asm == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		free(vectorX);
		free(vectorY);
		free(vectorX_asm);
		free(vectorY_asm);
		return 1;
	}

	srand((unsigned int)time(NULL));

	// Populate vectorX with random double values
	for (int i = 0; i < size; i++) {

		vectorX[i] = ((double)rand() / (double)RAND_MAX) * 100.0;
	}
	// Copy vectorX to vectorX_asm
	for (int i = 0; i < size; i++) {
		vectorX_asm[i] = vectorX[i];
	}

	//Do a single run for the C function and assembly function for sanity check
	printf("\nRunning the C function once...\n");
	calc1D_Stencil(vectorX, vectorY, size);
	printf("Running the Assembly function once...\n");
	calc1D_Stencil_asmfunc(vectorX_asm, vectorY_asm, size);
	//Check if the values are the same
	int error = 0;
	for (int i = 0; i < vectorYSize; i++) {
		if (vectorY[i] != vectorY_asm[i]) {
			printf("\nError: C function and Assembly function do not match at index %d\n", i);
			error = 1;
		}
	}
	if (error == 0) {
		printf("C function and Assembly function match, proceeding with test\n\n");
	}
	else {
		printf("C function and Assembly function do not match\n");
		free(vectorX);
		free(vectorY);
		free(vectorX_asm);
		free(vectorY_asm);
		return 1;
	}

	//Setup the array to store the time taken for each run
	double c_times[50];
	double asm_times[50];

	printf("Running the C function 50 times...\n\n");
	for (int i = 0; i < runTime; i++) {
		clock_t start = clock();
		calc1D_Stencil(vectorX, vectorY, size);
		clock_t end = clock();
		c_times[i] = (double)(end - start) / CLOCKS_PER_SEC;
	}

	printf("Running the Assembly function 50 times...\n\n");
	for (int i = 0; i < runTime; i++) {
		clock_t start = clock();
		calc1D_Stencil_asmfunc(vectorX_asm, vectorY_asm, size);
		clock_t end = clock();
		asm_times[i] = (double)(end - start) / CLOCKS_PER_SEC;
	}

	printf("Outputting the results to a CSV file...\n");
	writeTimingsToCSV(c_times, asm_times, runTime, exponentSize);
	printf("Results have been outputted to a CSV file\n");

	free(vectorX);
	free(vectorY);
	free(vectorX_asm);
	free(vectorY_asm);

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

double calculateAverage(const double timings[], int numElements) {
	double sum = 0.0;
	for (int i = 0; i < numElements; ++i) {
		sum += timings[i];
	}
	return sum / numElements;
}

// Function to write the timing data to a CSV file
void writeTimingsToCSV(const double cTimings[], const double asmTimings[], int iterations, int exponent) {
	char fileName[100];

	// Determine the file name based on the compilation mode and exponent size
	#ifndef NDEBUG
		sprintf_s(fileName, sizeof(fileName), "Comparison_Analysis_Debug_2^%d.csv", exponent);
	#else
		sprintf_s(fileName, sizeof(fileName), "Comparison_Analysis_Release_2^%d.csv", exponent);
	#endif

	// Open the file for writing
	FILE* file = fopen(fileName, "w");
	if (file == NULL) {
		perror("Error opening file");
		return;
	}

	// Write the header row
	fprintf(file, "Vector Size (2^%d),Iteration,C Timing (s),Assembly Timing (s)\n", exponent);

	// Write the timing data
	for (int i = 0; i < iterations; ++i) {
		// Only print the vector size in the first row
		if (i == 0) {
			fprintf(file, "%d,", 1 << exponent);
		}
		else {
			fprintf(file, ",");
		}
		fprintf(file, "%d,%f,%f\n", i + 1, cTimings[i], asmTimings[i]);
	}

	// Write the averages at the end of the file
	double cAverage = calculateAverage(cTimings, iterations);
	double asmAverage = calculateAverage(asmTimings, iterations);
	fprintf(file, "\n, , Average Time: %f, Average Time: %f\n", cAverage, asmAverage);

	// Close the file
	fclose(file);
}