#define NBSON 5

typedef struct t_tree {
       int val;
       int nbSon;
       int matrixSize;
       int CCsize;
       Matrix matrix;
       struct t_tree *tabSon[NBSON];
} NNode, *NTree;

#define TREENULL NULL

NTree newNTree(int val);
int nTreeNull(NTree a);
NTree addSon(NTree a, NTree son);
void freeNode(NTree node);
void forceDeleteNTree(NTree tree);
void truncateTree(NTree tree, int level);
void freeTree(NTree tree);
void printNTreeRec(NTree a, int p);
void printNTree(NTree a);
void removeSon(NTree father, int indice);
void copyMatrixIntoNode(NTree node, Matrix matrixToCopy, int size);