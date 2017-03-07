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

	int boolwin = 0;

    flux* fichier = openFile("test.txt");

    int size = checkFileFormat(fichier);
    Matrix M = initFromFile(fichier);
    printMatrix(M, size);

	char *p, s[100];
    int n;
    SDL_Surface* ecran=initSDLwindow();



	printf("Entrez une couleur : ");
    while (!boolwin && fgets(s, sizeof(s), stdin)) {
        n = strtol(s, &p, 10);
        if (p == s || *p != '\n') {
            printf("Entrez un nombre.\n");
        }
		else if(n >= 1 && n <= 7) {
			changeCC(M, n, size);
			boolwin = win(M, size);
			printMatrix(M, size);
			printMatrixSDL(M, size);
		}
		else {
			printf("Entrez un nombre entre 1 et 6.\n");
		}
		printf("RENTRE UNE COULEUR STP : ");
    }

	freeMatrix(M, size);
	close(fichier);



	// SDL_Surface ecran=initSDLwindow();


	// const SDL_VideoInfo* info = NULL;
    
 //    if(SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
 //        /* Failed, exit. */
 //        fprintf( stderr, "Video initialization failed: %s\n", SDL_GetError( ) );
 //        SDL_Quit( );
 //    }
 //    info = SDL_GetVideoInfo( );
 //    if( !info ) {
 //        /* This should probably never happen. */
 //        fprintf( stderr, "Video query failed: %s\n", SDL_GetError( ) );
 //        SDL_Quit( );
 //    }

	// while (!win) 
	// {
	// 	printMatrixSDL(M, size);
 //        win=win(mat, size);
 //    }


	SDL_Quit();








	return 0;
}
