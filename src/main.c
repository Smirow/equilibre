#include "../headers/couleur.h"
#include "../headers/affichage.h"
#include <SDL/SDL.h>


int main(void) {
	srand(time(NULL));

	/* Petit fixe pour valgrind */
	int *hh = NULL;
	hh = malloc(sizeof(int));
	free(hh);
	/* ----------- */

	
	return 0;
}
