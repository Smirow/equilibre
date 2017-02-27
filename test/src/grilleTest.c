#include "../../headers/file.h"
#include "../../headers/grille.h"
#include "../headers/grilleTest.h"
#include <CUnit/Basic.h>


void test_initMatrix(void) {
    Matrix matrix = initMatrix(3);
    CU_ASSERT(sizeof(matrix) == sizeof(Matrix));
    for(int i = 0; i < 3; i++) {
        CU_ASSERT(sizeof(matrix[i]) == sizeof(int*));
        for(int j = 0; j < 3; j++) {
            CU_ASSERT((sizeof(matrix[i][j]) == sizeof(int)) && (matrix[i][j] == 0));
        }
    }
    freeMatrix(matrix, 3);
}


void test_randomMatrix(void) {
    Matrix matrix = initMatrix(10);
    randomMatrix(matrix, 10, 10);
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            CU_ASSERT((matrix[i][j] >= 1) && (matrix[i][j] <= 10));
        }
    }
    freeMatrix(matrix, 10);
}

void test_initFromFile(void) {
    int test_1[3][3] = {{3, 5, 9}, {1, 5, 7}, {3, 8, 5}};

	flux* f = openFile("test/ressources/grille_1.txt");
    int size = checkFileFormat(f);
    Matrix matrix = initFromFile(f);

	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			CU_ASSERT(test_1[i][j] == matrix[i][j]);
		}
	}
}
