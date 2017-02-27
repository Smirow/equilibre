/**
 * \file grille.h
 * \brief Fonctionnalité S1.1 : Grille
 * \author Team Équilibre
 * \version 0.0.1
 * \date 10 fevrier 2017
 *
 */
#include <time.h>
#include <math.h>


/**
 * \struct Matrix
 * \brief Objet matrix.
 */
typedef int **Matrix;


/**
 * Prototypes
 */
Matrix initMatrix(int size);
void freeMatrix(Matrix matrix, int size);
void printMatrix(Matrix matrix, int size);
void randomMatrix(Matrix matrix, int size, int N);
Matrix initFromFile(flux* f);
