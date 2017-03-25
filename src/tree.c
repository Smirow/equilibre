#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../headers/file.h"
#include "../headers/grille.h"
#include "../headers/tree.h"


NTree newNTree(int val) {
    NNode *n;
    n = (NNode*)malloc(sizeof(NNode));
    n->val = val;
    n->nbSon = 0;
    n->matrixSize = 0;
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
    if (level == 0) {
        forceDeleteNTree(tree);
    }
    else if (level == 1) {
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
    truncateTree(root, 0);
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
    for (int i = indice; i < father->nbSon; i++) {
        father->tabSon[i] = father->tabSon[i+1];
        father->tabSon[i+1] = TREENULL;
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

/* TEST, uncomment and make for testing this module */
/*
int main() {
    NTree A, B;
    A = newNTree(5);
    B = newNTree(10);
    addSon(A, B);
    addSon(A, newNTree(7));
    addSon(A, newNTree(99));

    addSon(B, newNTree(5));
    addSon(B, newNTree(9));
    addSon(B, newNTree(90));

    A->matrixSize = 5;
    A->matrix = initMatrix(A->matrixSize);
    randomMatrix(A->matrix, A->matrixSize, 6);
    printMatrix(A->matrix, A->matrixSize);

    removeSon(A, 0);
    printNTree(A);
    freeTree(A);

}
*/