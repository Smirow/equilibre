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

int autoDraw=0;


// px, py coordonnées haut, gauche du pixel
void drawRectangle(SDL_Surface *ecran, int px, int py, int size, int r, int g, int b) {
    SDL_Rect rect;
    rect.x=px;
    rect.y=py;
    rect.h=rect.w=size;
    SDL_FillRect(ecran, &rect, SDL_MapRGB(ecran->format, r, g, b));
    SDL_Flip(ecran);
}

void fillScreen(SDL_Surface *ecran, int r, int g, int b) {
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, r, g, b));
    SDL_Flip(ecran);
}

void printMatrixSDL(Matrix mat, int size, SDL_Surface *ecran){    
    int rectsize=500/size;
    for(int i=0 ; i<size ; i++)
    {
	    for(int j=0 ; j<size ; j++)
	    {
	    	switch(mat[i][j])
	    	{
	    		case 1 :
    				drawRectangle(ecran,  i*rectsize,  j*rectsize, rectsize,  255,  0,  0);
	    			break;
    			case 2 :
    				drawRectangle(ecran,  i*rectsize,  j*rectsize, rectsize,  0,  255,  0);
	    			break;    			
	    		case 3 :
    				drawRectangle(ecran,  i*rectsize,  j*rectsize, rectsize,  0,  0,  255);
	    			break;
	    		case 4:
    				drawRectangle(ecran,  i*rectsize,  j*rectsize, rectsize,  255,  0,  255);
	    			break;
    			case 5 :
    				drawRectangle(ecran,  i*rectsize,  j*rectsize, rectsize,  255,  255,  255);
	    			break;
	    		case 6 :
    				drawRectangle(ecran,  i*rectsize,  j*rectsize, rectsize,  0,  255,  255);
	    			break;
                default:
                    printf("error\n");
	    	}

	    }
    }

    
    
   

}






SDL_Surface* initSDLwindow(){
	SDL_Surface *ecran = NULL;
	ecran=SDL_SetVideoMode(500, 600, 32, SDL_HWSURFACE);
    fillScreen(ecran, 230,230,230);
	SDL_WM_SetCaption("Color Flood equilibre", NULL);

	return ecran;
}