/*#include "couleur.h"*/
#include "grille.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>

void remplace(Matrix grille,int x,int y,int c){
	grille[x][y]= c;
}

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


FIFO initFIFOVide(){
	FIFO file;
	file.first = NULL;
	file.last = NULL;
	file.taille = 0;
	return file;
}

int vide(FIFO f){
	if (f.taille == 0){
		return 1;
	}
	else {
		return 0;
	}
}

void constructeur(coordonnees coord,FIFO f){
	cellule *c;
	c = (cellule *)malloc(sizeof(cellule));
	c->pos = coord;
	if (vide(f)){
		f.first = c;		
	}
	f.last = c;
	f.taille = f.taille +1;
}

coordonnees depile(FIFO f){
	coordonnees coord;
	if (f.taille != 0){
		coord.x = f.first->pos.x;
		coord.y = f.first->pos.y;
		f.first = f.first->suivant;
		f.taille--;
	}

	return coord;
}