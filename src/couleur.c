#include "../headers/couleur.h"
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>


struct struct_coordonnees{
	int x;
	int y;
};

struct struct_cellule{
	coordonnees pos;
	struct struct_cellule *suivant;
};


struct struct_FIFO {
	cellule *first;
	cellule *last;
	int taille;
};


void remplace(Matrix grille,int x,int y,int c){
	grille[x][y]= c;
}

coordonnees* initcoord(){
	coordonnees *coord = malloc(sizeof(coordonnees));
	coord->x = 0;
	coord->y = 0;
	return coord;
}

void modifcoord(int x,int y,coordonnees* coord){
	coord->x = x;
	coord->y = y;
}

FIFO* initFIFOVide(){
	FIFO *file = malloc(sizeof(FIFO));
	file->first = NULL;
	file->last = NULL;
	file->taille = 0;
	return file;
}

int vide(FIFO *f){
	if (f->taille == 0){
		return 1;
	}
	else {
		return 0;
	}
}

void constructeur(coordonnees* coord,FIFO *f){
	cellule *c;
	c = (cellule *)malloc(sizeof(cellule));
	c->pos.x = coord->x;
	c->pos.y = coord->y;
	if (vide(f)){
		f->first = c;		
	}
	else{
		f->last->suivant = c;
	}
	f->last = c;
	f->taille++;
}

coordonnees* defile(FIFO *f){
	coordonnees *coord = malloc(sizeof(coordonnees));
	if (f->taille != 0){
		coord->x = f->first->pos.x;
		coord->y = f->first->pos.y;
		f->first = f->first->suivant;
		f->taille--;
	}
	return coord;
}

void affiche(FIFO *suite){
	cellule *cel;
	int i,x,y;
	cel = suite->first;
	for(i=0;i<suite->taille;++i){
		x = cel->pos.x;
		y = cel->pos.y;
		printf("[%d,%d] -> ", x , y);
		cel = cel->suivant;
	}
	printf("\n");
}