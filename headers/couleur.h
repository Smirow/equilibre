#ifndef __COULEUR_H
#define __COULEUR_H
#include "../headers/file.h"
#include "../headers/grille.h"

/* PILE FIFO */

typedef struct struct_coordonnees{
	int x;
	int y;
}coordonnees;

typedef struct struct_cellule{
	coordonnees pos;
	struct struct_cellule *suivant;
}cellule;


typedef struct struct_FIFO {
	cellule *first;
	cellule *last;
	int taille;
}FIFO;

extern void remplace(Matrix grille,int x,int y,int c);
extern FIFO initFIFOVide();
extern int vide(FIFO f);
extern void constructeur(coordonnees coord,FIFO f);
extern coordonnees depile(FIFO f);

#endif