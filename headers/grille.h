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
Matrix initMatrix(int);
void freeMatrix(Matrix, int);
void printMatrix(Matrix, int);
void randomMatrix(Matrix, int, int);
Matrix initFromFile(flux*);
