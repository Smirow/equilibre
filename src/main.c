#include <SDL/SDL.h>
#include "../headers/couleur.h"
#include "../headers/affichage.h"


int main(int argc, char *argv[]) {
	srand(time(NULL));

	/* Petit fixe pour valgrind */
	int *hh = NULL;
	hh = malloc(sizeof(int));
	free(hh);
	/* ----------- */

	
	return 0;
}
