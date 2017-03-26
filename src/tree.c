#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../headers/file.h"
#include "../headers/grille.h"
#include "../headers/couleur.h"
#include "../headers/tree.h"


NTree newNTree(int val) {
    NNode *n;
    n = (NNode*)malloc(sizeof(NNode));
    n->val = val;
    n->nbSon = 0;
    n->matrixSize = 0;
    n->CCsize = 0;
    n->matrix = NULL;
    return n;
}


int nTreeNull(NTree a) {
    return a == TREENULL;
}


NTree addSon(NTree a, NTree son) {
    if (a->nbSon == NBSON) return a;
    a->nbSon++;
    a->tabSon[a->nbSon-1] = son;
    return a;
}


void freeNode(NTree node) {
    if (node->matrix) {
        freeMatrix(node->matrix, node->matrixSize);
        node->matrixSize = 0;
        node->matrix = NULL;
    }
    free(node);
}


void forceDeleteNTree(NTree tree) {
    if (tree->nbSon == 0) {
        freeNode(tree);
    }
    else {
        int temp = tree->nbSon - 1;
        for(int i = temp; i >= 0; i--) {
            forceDeleteNTree(tree->tabSon[i]);
            tree->nbSon--;
        }
        freeNode(tree);
    }
}


void truncateTree(NTree tree, int level) {
    if (level == -1) {
        forceDeleteNTree(tree);
    }
    else if (level == 0) {
        int temp = tree->nbSon - 1;
        for (int i = temp; i >= 0; i--) {
            truncateTree(tree->tabSon[i], level - 1);
            tree->nbSon--;
        }
    }
    else {
        for (int i = 0; i < tree->nbSon; i++) {
            truncateTree(tree->tabSon[i], level - 1);
        }
    }
}


void freeTree(NTree root) {
    truncateTree(root, -1);
}


void printNTreeRec(NTree root, int p) {
    printf("n%d [label=%d];\n", p, root->val);
    for (int i = 0; i < root->nbSon; i++) {
        printNTreeRec(root->tabSon[i], p*root->nbSon+i+1);
        printf("n%d -> n%d;\n", p, p*root->nbSon+i+1);
    }
}


void printNTree(NTree root) {
    printNTreeRec(root, 0);
}


void removeSon(NTree father, int indice) {
    freeTree(father->tabSon[indice]);
    if (indice < father->nbSon - 1) {
        for (int i = indice; i < father->nbSon; i++) {
            father->tabSon[i] = father->tabSon[i+1];
            father->tabSon[i+1] = TREENULL;
        }
    }
    father->nbSon--;
}


void copyMatrixIntoNode(NTree node, Matrix matrixToCopy, int size) {
    if (node->matrix && node->matrixSize == size) {      
        copyMatrix(node->matrix, matrixToCopy, size);
    }
    else if (!node->matrix) {
        node->matrixSize = size;
        node->matrix = initMatrix(node->matrixSize);
        copyMatrix(node->matrix, matrixToCopy, size);
    }
    else {
        freeMatrix(node->matrix, node->matrixSize);
        node->matrixSize = 0;
        node->matrix = NULL;
        copyMatrixIntoNode(node, matrixToCopy, size);
    }
}

int playMatrixIntoSon(NTree node, int oldCCsize) {
    if (!node->matrix || !node->matrixSize || !(node->val >= 1 && node->val <= 6)) return 0;
    node->CCsize = changeCC(node->matrix, node->val, node->matrixSize);
    if (node->CCsize == oldCCsize) return 0;
    return 1;
}

int createStandardPossibleSons(NTree node) {
    if (node->val >= 1 && node->val <= 6 && node->nbSon == 0) {
        for (int i = 1; i <= 6; i++)
            if (i != node->val) addSon(node, newNTree(i));      
        return 1;
    }
    return 0;
}


void createStandardPossibleTreeRec(NTree node, int Depth, int* maxDepth) {
    if (Depth < *maxDepth) {
        createStandardPossibleSons(node);
        int temp = node->nbSon - 1;
        for (int i = temp; i >= 0; i--) {
            copyMatrixIntoNode(node->tabSon[i], node->matrix, node->matrixSize);  
            if (playMatrixIntoSon(node->tabSon[i], node->CCsize) && Depth < *maxDepth) {
                if (node->tabSon[i]->CCsize == node->matrixSize * node->matrixSize) {
                    *maxDepth = Depth;
                    printf("Better solution in %d\n", *maxDepth);
                }
              createStandardPossibleTreeRec(node->tabSon[i], Depth + 1, maxDepth);
            }
            removeSon(node, i);
        }
    }
}

Matrix chooseColor(Matrix matrix, int size) {
    Matrix colors = initMatrixNonRegular(6, 2);
    colors[0][0] = 1;
    colors[1][0] = 2;
    colors[2][0] = 3;
    colors[3][0] = 4;
    colors[4][0] = 5;
    colors[5][0] = 6;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            switch(matrix[i][j]) {
                case 1: colors[0][1]++; break;
                case 2: colors[1][1]++; break;
                case 3: colors[2][1]++; break;
                case 4: colors[3][1]++;  break;
                case 5: colors[4][1]++;  break;
                case 6: colors[5][1]++;  break;
            }
        }
    }
    return colors;
}


void triBullesColors(Matrix matrix, int row){
  int tmp = 0;
  for (int i = row; i >= 0; i--){
    for (int j = 0; j < i-1; j++) {
      if (matrix[j+1][1] < matrix[j][1]){
        tmp = matrix[j][1];
        matrix[j][1] = matrix[j+1][1];
        matrix[j+1][1] = tmp;
      }
    }
  }
}

void printColors(Matrix matrix, int col, int row) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col - 1; j++) {
            printf("[%d %d]", matrix[i][j], matrix[i][j+1]);
        }
    }
    printf("\n");
}


void createStandardPossibleTree(Matrix matrix, int matrixSize, int MAXDepth) {
    NTree tree = newNTree(matrix[0][0]);
    copyMatrixIntoNode(tree, matrix, matrixSize);
    int* maxDepth = &MAXDepth;
    createStandardPossibleTreeRec(tree, 1, maxDepth);
    printf("Best solution in %d\n", *maxDepth);
    freeTree(tree);
}




/* TEST, uncomment and make to test this module */

int main() {
    srand(time(NULL));
    NTree A, B;
    flux* f = openFile("./test.txt");

    int size = checkFileFormat(f);
    Matrix matrix = initFromFile(f);
    printMatrix(matrix, size);
    Matrix colors = chooseColor(matrix, size);
    triBullesColors(colors, 6);
    printColors(colors, 2, 6);
    createStandardPossibleTree(matrix, size, 20);
    freeMatrix(matrix, size);
}
