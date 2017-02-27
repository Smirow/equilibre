#include "../headers/couleur.h"
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>



/**
 * \fn void replace(Matrix matrix, int size, coordonnees coord, int val)
 * \brief Remplace la couleur d'une cell
 *
 * \param Matrix matrix la grille
 * \param int size la taille de la grille
 * \param coordonnees coord les coordonnees de la cellule
 * \param int val la valeur souhaité de la cellule
 */
void replace(Matrix matrix, int size, coordonnees coord, int val) {
	if ((coord.x >= 0) && (coord.x < size) && (coord.y >= 0) && (coord.y < size)) {
		matrix[coord.x][coord.y] = val;
	}
}

/**
 * \fn coordonnees modifcoord(int x, int y)
 * \brief Initialisation ou modification d'une structure coordonnees
 *
 * \return coordonnees coord

 */
coordonnees modifcoord(int x, int y){
	coordonnees coord;
	coord.x = x;
	coord.y = y;
	return coord;
}


/**
 * \fn FIFO* initFIFOVide()
 * \brief Initialisation d'une structure FIFO
 *
 * \return FIFO* file NULL

 */
FIFO* initFIFOVide() {
	FIFO *file = malloc(sizeof(FIFO));
	file->first = NULL;
	file->last = NULL;
	file->taille = 0;
	return file;
}


/**
 * \fn int emptyFIFO(FIFO *f)
 * \brief Verifie si la FIFO est vide
 *
 * \param FIFO *f la FIFO à traiter
 * \return int 0 ou 1

 */
int emptyFIFO(FIFO *f) {
	if (f->taille == 0){
		return 1;
	}
	else {
		return 0;
	}
}


/**
 * \fn void constructeur(FIFO *f, coordonnees coord)
 * \brief Constructeur de FIFO
 *
 * \param FIFO* f la FIFO à traiter
 * \param coordonnees* coord les coordonnees à rajouter
 */
void constructeur(FIFO *f, coordonnees coord) {
	cellule *c;
	c = (cellule *)malloc(sizeof(cellule));
	c->pos.x = coord.x;
	c->pos.y = coord.y;
	if (emptyFIFO(f)){
		f->first = c;
	}
	else {
		f->last->suivant = c;
	}
	f->last = c;
	f->taille++;
}


/**
 * \fn freeFIFO(FIFO *f)
 * \brief vide la FIFO
 *
 * \param FIFO* f la FIFO à traiter
 */
void freeFIFO(FIFO *f) {
	while(!emptyFIFO(f)) {
		defile(f);
	}
	free(f);
}


/**
 * \fn coordonnees* defile(FIFO *f)
 * \brief defile la FIFO
 *
 * \param FIFO* f la FIFO à traiter
 * \return coordonnees* coord les coordonnees de la cellule depilée
 */
coordonnees defile(FIFO *f){
	coordonnees coord = modifcoord(0, 0);
 	if (f->taille != 0){
		cellule *c = f->first;
		coord = modifcoord(f->first->pos.x, f->first->pos.y);
 		f->first = f->first->suivant;
 		f->taille--;
		free(c);
 	}
 	return coord;
 }


/**
 * \fn void affiche(FIFO *suite)
 * \brief affiche la FIFO sur la sortie standard
 *
 * \param FIFO* f la FIFO à afficher
 */
void affiche(FIFO *suite) {
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


/**
 * \fn void changeCC(Matrix grille, int nextcolor, int size)
 * \brief Fonction du jeu, permet de modifier les couleur de la composante connexe
 *
 * \param Matrix grille la grille du jeu
 * \param int nextcolor la couleur du tour actue
 * \param int size la taille de la grille de jeu
 */
void changeCC(Matrix grille, int nextcolor, int size) {
	int color = grille[0][0];
	int x, y;
	coordonnees coord = modifcoord(0, 0);
	coordonnees coord2 = modifcoord(0, 0);
	FIFO *f = initFIFOVide();
	constructeur(f, coord);
	grille[0][0] = nextcolor;
	while((!emptyFIFO(f)) && (color != nextcolor)) {
		coord2 = defile(f);
		x = coord2.x, y = coord2.y;
		if(x > 0 && grille[x-1][y] == color) {
			coord = modifcoord(x-1, y);
			constructeur(f, coord);
			grille[x-1][y] = nextcolor;
		}
		if(y > 0 && grille[x][y-1] == color) {
			coord = modifcoord(x, y-1);
			constructeur(f, coord);
			grille[x][y-1] = nextcolor;
		}
		if(x < size-1 && grille[x+1][y] == color) {
			coord = modifcoord(x+1, y);
			constructeur(f, coord);
			grille[x+1][y] = nextcolor;
		}
		if(y < size-1 && grille[x][y+1] == color) {
			coord = modifcoord(x, y+1);
			constructeur(f, coord);
			grille[x][y+1] = nextcolor;
		}
	}
	freeFIFO(f);
}

/**
 * \fn int win(Matrix grille, int size)
 * \brief Fonction du jeu, permet de verifier si le joueur à gagné
 *
 * \param Matrix grille la grille du jeu
 * \param int size la taille de la grille de jeu
 * \return int 0 or 1
 */
int win(Matrix grille, int size) {
	int color = grille[0][0];
	for(int i = 0 ; i < size ; i++) {
		for(int j = 0 ; j < size ; j++) {
			if(grille[i][j] != color) {
				return 0;
			}
		}
	}
	return 1;
}
