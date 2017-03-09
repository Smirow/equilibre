/**
 * \file grille.h
 * \brief Fonctionnalité S1.1 : Grille
 * \author Team Équilibre
 * \version 0.0.1
 * \date 10 fevrier 2017
 *
 */


#ifndef __GRILLE_H
#define __GRILLE_H


#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

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

#endif
