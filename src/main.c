#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL/SDL.h>

#include "../headers/couleur.h"
#include "../headers/affichage.h"



int getColor() {
    char s[100];
    fgets(s, sizeof(s), stdin);
    int res = 0;
    switch(s[0]) {
        case 'R':
            res = 1;
            break;
        case 'G':
            res = 2;
            break;
        case 'Y':
            res = 3;
            break;
        case 'B':
            res = 4;
            break;
        case 'M':
            res = 5;
            break;
        case 'C':
            res = 6;
            break;
        default:
            res = 0;
    }
    return res;
}


int main(int argc, char *argv[]) {
    srand(time(NULL));

    /* Petit fixe pour valgrind */
	int *hh = NULL;
	hh = malloc(sizeof(int));
	free(hh);
	/* ----------- */

    int size;
    int boolwin = 0;
    int maxCoups = 0;


    int preSize = 0;
    char *p1, s1[100];
    printf("Entrez la taille de la grille: ");
    fgets(s1, sizeof(s1), stdin);
    preSize = strtol(s1, &p1, 10);
    if(preSize >= 1) {
		size = preSize;
	}
    else {
        printf("Erreur, bye.\n");
        exit(1);
    }
    Matrix M = initMatrix(size);
    randomMatrix(M, size, 6);


    int preMax = 0;
    char *p, s[100];
    printf("Entrez un nombre maximum de coups: ");
    fgets(s, sizeof(s), stdin);
    preMax = strtol(s, &p, 10);
    if(preMax >= 1) {
		maxCoups = preMax;
	}
    else {
        printf("Erreur, bye.\n");
        exit(1);
    }


    SDL_Init(SDL_INIT_VIDEO);
 
    SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
 
    SDL_Quit();
 
    return EXIT_SUCCESS;
}