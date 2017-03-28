/*#include "../headers/grille.h"*/
#include <time.h>
#include <stdlib.h>
#include "../headers/couleur.h"
#include "../headers/solv_rand.h"


FIFO* solv_random(Matrix matrix, int size)
{
	FIFO* file = initFIFOVide();
	coordonnees coord;
    Matrix grille = initMatrix(size);
    copyMatrix(grille, matrix, size);
	int color=0, previouscolor, sizeCC=1, newsizeCC=1;

	while (newsizeCC != size*size){
		previouscolor = color;
		color = rand()%6+ 1;
		if ((newsizeCC = changeCC(grille, color, size)) > sizeCC){
			sizeCC = newsizeCC;	
			coord = modifcoord(color, color);
			constructeur(file, coord);
		}
		else{
			changeCC(grille, previouscolor, size);
		}
	}
	return file;
}

FIFO * best_solv_rand_FIFO(Matrix matrix, int size)
{
	FIFO * bestFIFO = initFIFOVide();
	FIFO * newFIFO = initFIFOVide();
	bestFIFO = solv_random(matrix, size);
	int bestsize = bestFIFO->taille;

	for (int i = 0; i < 1000; ++i)
	{
		newFIFO = solv_random(matrix, size);
		if (newFIFO->taille < bestsize )
		{
			bestsize = newFIFO->taille;
			bestFIFO = newFIFO;
		}
	}
	return bestFIFO;
}

int size_random(Matrix matrix, int size)
{
	int sizesol=0;
    Matrix grille = initMatrix(size);
    copyMatrix(grille, matrix, size);
	int color=0, previouscolor, sizeCC=1, newsizeCC=1;

	while (newsizeCC != size*size){
		previouscolor = color;
		color = rand()%6+ 1;
		if ((newsizeCC = changeCC(grille, color, size)) > sizeCC){
			sizeCC = newsizeCC;	
			sizesol++;
		}
		else{
			changeCC(grille, previouscolor, size);
		}
	}
	return sizesol;
}

int best_solv_rand(Matrix matrix, int size)
{
	int bestsize = size_random(matrix, size);
	int newsize;

	for (int i = 0; i < 1000; ++i)
	{
		newsize = size_random(matrix, size);
		if (newsize < bestsize )
		{
			bestsize = newsize;
		}
	}
	return bestsize;
}