/**
 * \file couleur.h
 * \brief Fonctionnalité S1.2 : Couleur
 * \author Team Équilibre
 * \version 0.0.1
 * \date 18 fevrier 2017
 *
 */

#ifndef __COULEUR_H
#define __COULEUR_H
#include "../headers/file.h"
#include "../headers/grille.h"


/**
 * \struct struct_coordonnees
 * \brief Objet coordonnees.
 */
 typedef struct struct_coordonnees{
 	int x;
 	int y;
} coordonnees;


/**
 * \struct struct_cellule
 * \brief Objet cellule.
 */
typedef struct struct_cellule{
	coordonnees pos;
	struct struct_cellule *suivant;
} cellule;

/**
 * \struct struct_FIFO
 * \brief Objet FIFO.
 */
typedef struct struct_FIFO {
	cellule *first;
	cellule *last;
	int taille;
} FIFO;


void replace(Matrix matrix, int size, coordonnees coord, int val);
FIFO* initFIFOVide();
int emptyFIFO(FIFO *f);
void constructeur(FIFO *f, coordonnees coord);
coordonnees defile(FIFO *f);
void freeFIFO(FIFO *f);
void affiche(FIFO *suite);
coordonnees modifcoord(int x, int y);
int changeCC(Matrix grille, int nextcolor, int size);
int win(Matrix grille, int size);

#endif
