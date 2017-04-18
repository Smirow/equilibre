#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

TREE_FIFO* initTreeFIFO() {
	TREE_FIFO *file = malloc(sizeof(FIFO));
	file->first = NULL;
	file->last = NULL;
	file->size = 0;
	return file;
}

int emptyTreeFIFO(TREE_FIFO *f) {
	if (f->size == 0){
		return 1;
	}
	else {
		return 0;
	}
}

void constructTreeFIFO(TREE_FIFO *f, NTree node) {
	cell *c;
	c = (cell *)malloc(sizeof(cell));
	c->tree = node;
	if (emptyTreeFIFO(f)){
		f->first = c;
	}
	else {
		f->last->next = c;
	}
	f->last = c;
	f->size++;
}

NTree defileTree(TREE_FIFO *f){
	NTree tree = TREENULL;
 	if (f->size != 0){
		cell *c = f->first;
		tree = f->first->tree;
 		f->first = f->first->next;
 		f->size--;
		free(c);
 	}
 	return tree;
 }

void freeTreeFIFO(TREE_FIFO *f) {
	while(!emptyTreeFIFO(f)) {
		defileTree(f);
	}
	free(f);
}


 void printTreeFIFO(TREE_FIFO *suite) {
	cell *cel;
	cel = suite->first;
	for(int i = 0; i < suite->size; ++i){
		printf("[%d] -> ", cel->tree->val);
		cel = cel->next;
	}
	printf("\n");
}


int playMatrixIntoSon(NTree node, int oldCCsize) {
    if (!node->matrix || !node->matrixSize || !(node->val >= 1 && node->val <= 6)) return 0;
    node->CCsize = changeCC(node->matrix, node->val, node->matrixSize);
    if (node->CCsize <= oldCCsize) return 0;
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

void print_sol_tree(NTree tree) {
    int temp = tree->nbSon - 1;
    switch(tree->val) {
        case 1:
            printf(RED "%1sR", "");
            break;              
        case 2:
            printf(GREEN "%1sG", "");
            break;
        case 3:
            printf(YELLOW "%1sY", "");
            break;
        case 4:
            printf(BLUE "%1sB", "");
            break;
        case 5:
            printf(MAGENTA "%1sM", "");
            break;
        case 6:
            printf(CYAN "%1sC", "");
            break;
        default:
            printf("Erreur couleur");
            exit(1);     
    }
    printf(COLOR_RESET);
    if (temp < 0) printf("\n");
    if (temp >= 0) {
        printf(" -> ");
        print_sol_tree(tree->tabSon[temp]);
    }
}

void createStandardPossibleTreeRec(NTree tree, NTree node, int Depth, int* maxDepth) {
    if (Depth < *maxDepth) {
        createStandardPossibleSons(node);
        int temp = node->nbSon - 1;
        for (int i = temp; i >= 0; i--) {
            copyMatrixIntoNode(node->tabSon[i], node->matrix, node->matrixSize);  
            if (playMatrixIntoSon(node->tabSon[i], node->CCsize) && Depth < *maxDepth) {
                if (node->tabSon[i]->CCsize == node->matrixSize * node->matrixSize) {
                    *maxDepth = Depth;
                    printf("Found solution in %d\n", *maxDepth);
                    print_sol_tree(tree);
                    printf("- - - - - - -  \n");
                }
              createStandardPossibleTreeRec(tree, node->tabSon[i], Depth + 1, maxDepth);
            }
            removeSon(node, i);
        }
        // printNTree(tree);
        // printf("- - - - - - -  \n");
    }
}

void BFSPossibleTreeRec(NTree node, int* maxDepth) {
    int Depth = 0;
    TREE_FIFO *f = initTreeFIFO();
    constructTreeFIFO(f, node);
    while(!emptyTreeFIFO(f) && Depth < *maxDepth) {
        NTree s = defileTree(f);
        //printf("%d\n", s->val);
        if (s->CCsize == s->matrixSize * s->matrixSize && Depth < *maxDepth ) {
            *maxDepth = Depth;
            printf("Better solution in %d\n", *maxDepth);
        }
        createStandardPossibleSons(s);
        int temp = s->nbSon - 1;
        for (int i = temp; i >= 0; i--) {
            copyMatrixIntoNode(s->tabSon[i], s->matrix, s->matrixSize);
            if (playMatrixIntoSon(s->tabSon[i], s->CCsize) && Depth < *maxDepth) {
                if (s->tabSon[i]->CCsize == s->matrixSize * s->matrixSize) {
                    *maxDepth = Depth;
                    printf("Better solution in %d\n", *maxDepth);
                }
                constructTreeFIFO(f, s->tabSon[i]);
            }
        }
        Depth++;
    }
}

int createStandardPossibleTree(Matrix matrix, int matrixSize, int MAXDepth) {
    NTree tree = newNTree(matrix[0][0]);
    copyMatrixIntoNode(tree, matrix, matrixSize);
    int* maxDepth = &MAXDepth;
    createStandardPossibleTreeRec(tree, tree, 1, maxDepth);
    printf("Best solution in %d\n", *maxDepth);
    freeTree(tree);
    return *maxDepth;
}



void basicSolver(Matrix matrix, int size, FIFO* f, int OldCC, int depth, int *maxDepth) {
    if (depth < *maxDepth) {
        int CCSize = 0;
        Matrix g2 = initMatrix(size);
        for (int i = 1; i <= 6; i++) {
            if (i != matrix[0][0]) {
                copyMatrix(g2, matrix, size);
                if ((CCSize = changeCC(g2, i, size)) > OldCC) {
                    coordonnees coord = modifcoord(i, i);
                    constructeur(f, coord);
                    if (CCSize == size * size) {
                        *maxDepth = f->taille;
                        printf("Found Solution in %d: ", depth);
                        affiche(f);
                    }
                    else {
                        basicSolver(g2, size, f, CCSize, depth + 1, maxDepth);
                    }
                    defile(f);
                }
            }
        }
    }
}





/* TEST, uncomment and make to test this module */
/*
int main() {
    srand(time(NULL));

    int size = SIZE;
    Matrix matrix = initMatrix(size);
    randomMatrix(matrix, size, 6);

    printMatrix(matrix, size);

    createStandardPossibleTree(matrix, size, 150);
    freeMatrix(matrix, size);
}
*/
