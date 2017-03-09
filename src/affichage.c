#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <SDL/SDL.h>
#include <ctype.h>

#include "../headers/file.h"
#include "../headers/grille.h"
#include "../headers/affichage.h"



SDL_Surface* initSDLwindow(int width, int height){

    if(SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        fprintf( stderr, "Video initialization failed: %s\n", SDL_GetError( ) );
        SDL_Quit();
    }
    SDL_Surface *screen=SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE);

    fillScreen(screen, 30, 30, 30);
    SDL_WM_SetCaption("Color Flood Equilibre", NULL);


    return screen;
}

// px, py coordonnées haut, gauche du pixel
void drawRectangle(SDL_Surface *ecran, int px, int py, int size, int r, int g, int b) {
    SDL_Rect rect;
    rect.x=px;
    rect.y=py;
    rect.h=rect.w=size;
    SDL_FillRect(ecran, &rect, SDL_MapRGB(ecran->format, r, g, b));
}

void fillScreen(SDL_Surface *ecran, int r, int g, int b) {
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, r, g, b));
    SDL_Flip(ecran);
}

void printMatrixSDL(Matrix mat, int size, SDL_Surface *ecran){    
    int rectsize=ecran->w/size;
    for(int i = 0; i < size ; i++) {
        for(int j = 0; j < size ; j++) {
            switch(mat[j][i]) {
                case 1 :
                    /* RED */
                    drawRectangle(ecran,  i*rectsize,  j*rectsize, rectsize, 201, 3, 14);
                    break;
                case 2 :
                    /* GREEN */
                    drawRectangle(ecran,  i*rectsize,  j*rectsize, rectsize, 77, 142, 11);
                    break;              
                case 3 :
                    /* YELLOW */
                    drawRectangle(ecran,  i*rectsize,  j*rectsize, rectsize, 194, 143, 10);
                    break;
                case 4:
                    /* BLUE */
                    drawRectangle(ecran,  i*rectsize,  j*rectsize, rectsize, 53, 91, 235);
                    break;
                case 5 :
                    /* MAGENTA */
                    drawRectangle(ecran,  i*rectsize,  j*rectsize, rectsize, 116, 76, 112);
                    break;
                case 6 :
                    /* CYAN */
                    drawRectangle(ecran,  i*rectsize,  j*rectsize, rectsize, 13, 112, 104);
                    break;
                default:
                    printf("error\n");
            }
        }
    }
    SDL_Flip(ecran);
}

