#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


// vectorX -> [RCX], vectorY -> [RDX], size -> R8
extern double calc1D_Stencil(double* vectorX, double* vectorY, int size);
int main()
{
    double vectorX[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9};
    double vectorY[4] = { 0, 0, 0, 0 };
    int size = 9;
    int length = sizeof(vectorY) / sizeof(vectorY[0]);


    calc1D_Stencil(&vectorX, &vectorY, size);

    for (int i = 0; i < length; i++) {
        printf("\nVectorY[%d]: %lf", i, vectorY[i]);
    }

    return 0;
}