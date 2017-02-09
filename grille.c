#include "grille.h"

/**
  Allocation de grille carré de taille variable
**/
Matrix initMatrix(int size) {
  Matrix matrix;
  matrix = (int **) calloc(size,sizeof(int*));
  for (int m = 0; m < size; m++) {
    matrix[m] = (int *) calloc(size,sizeof(int));
  }
  return matrix;
}


/**
  Libération de l'espace mémoire
**/
void freeMatrix(Matrix matrix) {
  free(matrix);
}

void printMatrix(Matrix matrix, int size) {
  for(int m = 0; m < size; m++) {
    for (int n = 0; n < size; n++) {
      printf("|%5d%3s", matrix[m][n], "");
    }
    printf("\n");
  }
}

/**
  Init de la grille a partir de valeurs aléatoires
  N: valeur maximum
**/
void randomMatrix(Matrix matrix, int size, int N) {
  for (int m = 0; m < size; m++) {
    for (int n = 0; n < size; n++) {
      matrix[m][n] = rand() % N+1;
    }
  }
}



int main(void) {
  srand(time(NULL));
  Matrix A = initMatrix(5);
  randomMatrix(A, 5, 6);
  printMatrix(A, 5);
  freeMatrix(A);
}
