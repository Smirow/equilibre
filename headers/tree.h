#define NBSON 5
#define TREENULL NULL
#define SIZE 7

typedef struct t_tree {
       int val;
       int nbSon;
       int matrixSize;
       int CCsize;
       Matrix matrix;
       struct t_tree *tabSon[NBSON];
} NNode, *NTree;


typedef struct struct_cell{
	NTree tree;
	struct struct_cell *next;
} cell;

typedef struct struct_Tree_FIFO {
	cell *first;
	cell *last;
	int size;
} TREE_FIFO;

typedef struct struct_list_solution {
    unsigned int** list;
    unsigned int rows, cols;
} *list_sol;

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
int playMatrixIntoSon(NTree node, int oldCCsize);
int createStandardPossibleSons(NTree node);

int createStandardPossibleSonsBis(NTree node, Matrix matrix);
void createStandardPossibleTreeRec(NTree tree, NTree node, int Depth, int* maxDepth);
int createStandardPossibleTree(Matrix matrix, int matrixSize, int MAXDepth);
void createStandardPossibleTreeRecOpt(NTree treeSol, NTree node, int Depth, int* maxDepth);
int createStandardPossibleTreeOpt(Matrix matrix, int matrixSize, int MAXDepth);
int createStandardPossibleTreeOptSecond(Matrix matrix, int matrixSize, int MAXDepth);
void createStandardPossibleTreeRecOptSecond(NTree treeSol, NTree node, int Depth, int* maxDepth);