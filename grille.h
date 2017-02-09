#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


/* Définir le type matrix. */
typedef int **Matrix;

Matrix initMatrix(int);
void freeMatrix(Matrix);
void printMatrix(Matrix, int);
void randomMatrix(Matrix, int, int);
