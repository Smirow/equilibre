#include <stdio.h>
#include <CUnit/Basic.h>
#include "../../headers/couleur.h"
#include "../headers/couleurTest.h"


void test_replace(void) {
    Matrix matrix = initMatrix(3);
    coordonnees coord = modifcoord(1, 1);
    Matrix matrix2 = initMatrix(3);
    coordonnees coord2 = modifcoord(4, 1);
    replace(matrix, 3, coord, 42);
    replace(matrix2, 3, coord2, 42);
    CU_ASSERT(matrix[1][1] == 42);
    CU_ASSERT(matrix[0][0] == 0);
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            CU_ASSERT(matrix2[i][j] == 0);
        }
    }
}

void test_modifcoord(void) {
    coordonnees coord = modifcoord(1, 42);
    CU_ASSERT((coord.x == 1) && (coord.y == 42));
    coord = modifcoord(42, 1);
    CU_ASSERT((coord.x == 42) && (coord.y == 1));
}

void test_emptyFIFO(void) {
    FIFO *f = initFIFOVide();
    CU_ASSERT(emptyFIFO(f));
    coordonnees coord = modifcoord(0, 0);
    constructeur(f, coord);
    CU_ASSERT_FALSE(emptyFIFO(f));
}

void test_defile(void) {
    FIFO *f = initFIFOVide();
    coordonnees coord = modifcoord(24, 42);
    constructeur(f, coord);
    coord = defile(f);
    CU_ASSERT((coord.x == 24) && (coord.y == 42));
    CU_ASSERT(emptyFIFO(f));
}

void test_win(void) {
    Matrix matrix = initMatrix(3);
    CU_ASSERT(win(matrix, 3));
    matrix[1][2] = 3;
    CU_ASSERT_FALSE(win(matrix, 3));
}
