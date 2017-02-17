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

int emptyFIFO(FIFO *f){
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
	if (emptyFIFO(f)){
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
	for(i = 0; i < suite->taille; ++i){
		x = cel->pos.x;
		y = cel->pos.y;
		printf("[%d,%d] -> ", x , y);
		cel = cel->suivant;
	}
	printf("\n");
}

void changeCC(Matrix grille, int nextcolor, int size) {
	int color = grille[0][0];
	int x, y;
	coordonnees* coord = initcoord();
	coordonnees* coord2 = initcoord();
	FIFO *f = initFIFOVide();
	constructeur(coord, f);
	grille[0][0] = nextcolor;
	while(!emptyFIFO(f))
	{
		coord2 = defile(f);
		x = coord2->x, y = coord2->y;
		if(x > 0 && grille[x-1][y] == color)
		{
			modifcoord(x-1, y, coord);
			constructeur(coord, f);
			grille[x-1][y] = nextcolor;
		}
		if(y > 0 && grille[x][y-1] == color)
		{
			modifcoord(x, y-1, coord);
			constructeur(coord, f);
			grille[x][y-1] = nextcolor;
		}
		if(x < size-1 && grille[x+1][y] == color)
		{
			modifcoord(x+1, y, coord);
			constructeur(coord, f);
			grille[x+1][y] = nextcolor;
		}
		if(y < size-1 && grille[x][y+1] == color)
		{
			modifcoord(x, y+1, coord);
			constructeur(coord,f );
			grille[x][y+1] = nextcolor;
		}
	}
}

int win(Matrix grille, int size){
	int color=grille[0][0];
	for(int i=0 ; i<size ; i++)
	{
		for(int j=0 ; j<size ; j++)
		{
			if(grille[i][j]!=color)
			{
				return 0;
			}
		}
	}
	return 1;
}