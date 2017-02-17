#ifndef __COULEUR_H
#define __COULEUR_H
#include "../headers/file.h"
#include "../headers/grille.h"

/* PILE FIFO */

typedef struct struct_coordonnees coordonnees;

typedef struct struct_cellule cellule;

typedef struct struct_FIFO FIFO;

extern void remplace(Matrix grille,int x,int y,int c);
extern FIFO* initFIFOVide();
extern int emptyFIFO(FIFO *f);
extern void constructeur(coordonnees* coord,FIFO *f);
extern coordonnees* defile(FIFO *f);
extern void affiche(FIFO *suite);
extern coordonnees* initcoord();
extern void modifcoord(int x,int y,coordonnees* coord);
extern int changeCC(Matrix grille, int nextcolor, int size);
extern int win(int ccsize, int size);

#endif