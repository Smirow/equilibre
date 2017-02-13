/**
 * \file grille.c
 * \brief Fonctionnalité S1.1 : Grille
 * \author Team Équilibre
 * \version 0.0.1
 * \date 10 fevrier 2017
 */
#include "../headers/file.h"
#include "../headers/grille.h"


/**
 * \fn Matrix initMatrix(int size)
 * \brief Creation d'une matrice carrée de taille variable.
 *
 * \param size int correspondant a la taille de la matrice carrée.
 * \return Un object de type Matrix.
 */
Matrix initMatrix(int size) {
    Matrix matrix;
    matrix = (int **) calloc(size, sizeof(int*));
    for (int m = 0; m < size; m++) {
        matrix[m] = (int *) calloc(size, sizeof(int));
    }
    return matrix;
}


/**
 * \fn void freeMatrix(Matrix matrix, int size)
 * \brief Libération de l'espace mémoire d'une matrice.
 *
 * \param matrix Matrix la matrice et size int à la taille de la matrice carrée.
 */
void freeMatrix(Matrix matrix, int size) {
    for(int m = 0; m < size; m++) {
        free(matrix[m]);
    }
    free(matrix);
}


/**
 * \fn void printMatrix(Matrix matrix, int size)
 * \brief Affiche la matrice de taille carré. Fonction de test.
 *
 * \param matrix Matrix la matrice et size int à la taille de la matrice carrée.
 */
void printMatrix(Matrix matrix, int size) {
    for(int m = 0; m < size; m++) {
        for (int n = 0; n < size; n++) {
            printf("|%5d%3s", matrix[m][n], "");
        }
        printf("\n");
    }
}


/**
 * \fn void randomMatrix(Matrix matrix, int size, int N)
 * \brief initialisation d'une matrice carrée à partir de valeurs aléatoires comprises entre 0 et N.
 *
 * \param matrix Matrix la matrice, size int à la taille de la matrice carrée, N le maximum..
 */
void randomMatrix(Matrix matrix, int size, int N) {
    for (int m = 0; m < size; m++) {
        for (int n = 0; n < size; n++) {
            matrix[m][n] = rand() % N+1;
        }
    }
}


/**
 * \fn Matrix initFromFile(flux* f)
 * \brief Creation d'une matrice carrée à partir d'un fichier.
 *
 * \param flux* f correspondant au flux du fichier.
 * \return Un object de type Matrix.
 */
Matrix initFromFile(flux* f) {
    int size = checkFileFormat(f);
    Matrix matrix = initMatrix(size);
    for(int m = 0; m < size; m++) {
        char* str = readALine(f);
        if(str) {
            for(int n = 0; n < size; n++) {
                char strOne = str[n];
                matrix[m][n] = atoi(&strOne);
            }
        }
    }
    rewind(f->f);
    return matrix;
}
