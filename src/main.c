#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL/SDL.h>

#include "../headers/couleur.h"
#include "../headers/affichage.h"

int main() {
    srand(time(NULL));

    /* Petit fixe pour valgrind */
	int *hh = NULL;
	hh = malloc(sizeof(int));
	free(hh);
	/* ----------- */

    int PLAY = 0;
    int size = 0;
    int boolwin = 0;
    int maxCoups = 0;
    int nbCoups = 0;
    int restart = 0;


    size = getsValue("Entrez la taille de la grille: ", 1);
    maxCoups = getsValue("Entrez un nombre maximum de coups: ", 1);

    Matrix matrixNoGame = initMatrix(size);
    Matrix matrix = initMatrix(size);
    randomMatrix(matrixNoGame, size, 6);
    copyMatrix(matrix, matrixNoGame, size);

    SDL_Surface *screen = initSDLwindow(504, 504);
    printMatrixSDL(matrix, size, screen, 0);
    

    SDL_Event event;
    char buf[100];
    while (!(boolwin = win(matrix, size)) && nbCoups < maxCoups && !PLAY) {
        /* RESTART */
        if (restart) {
            copyMatrix(matrix, matrixNoGame, size);
            printMatrixSDL(matrix, size, screen, 0); 
            nbCoups = 0;
            restart = 0;       
        }

        int playing = 0;
        sprintf(buf, "Color Flood Equilibre (%d coups restant)", maxCoups - nbCoups);
        SDL_WM_SetCaption(buf, NULL);

        /* Fixe for Mac */
        if (nbCoups == 0) 
            SDL_Flip(screen);
        
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT: PLAY = 1; break;
            case SDL_VIDEORESIZE:
                screen = SDL_SetVideoMode(event.resize.w, event.resize.h, 32, SDL_HWSURFACE | SDL_RESIZABLE);
                printMatrixSDL(matrix, size, screen, 0); 
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if ((playing = getValueMatrix(event.button.x, event.button.y, matrix, size, screen))) {
                        if (playing != matrix[0][0])
                            nbCoups++;
			            changeCC(matrix, playing, size);
                        printMatrixSDL(matrix, size, screen, 0);
                    }
                }
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_q:
                        printf("Exit requested.\n");
                        PLAY = 1;
                        break;
                    case SDLK_r:
                        printf("Restarting game.\n");
                        restart = 1;
                        break;
                    default:
                        break;
                }   
                break;         
        }
    }

    if (boolwin) {
        printMatrixSDL(matrix, size, screen, 0);
        SDL_WM_SetCaption("Color Flood Equilibre (partie gagnée)", NULL);
        printf("Partie Gagnée !\n");
        printWin();
    }
    else if (nbCoups >= maxCoups) {
        printMatrixSDL(matrix, size, screen, 128);
        SDL_WM_SetCaption("Color Flood Equilibre (max coups atteint)", NULL);
        printf("Partie terminée, max coups atteint.\n");
        printWin();
    }
    
    free(matrix);
    SDL_FreeSurface(screen);
    SDL_Quit();
    return EXIT_SUCCESS;
}