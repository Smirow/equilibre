#ifndef __AFFICHAGE_H
#define __AFFICHAGE_H
#include <SDL/SDL.h>


SDL_Surface* initSDLwindow();
void drawRectangle(SDL_Surface *ecran, int px, int py, int size, int r, int g, int b);
void fillScreen(SDL_Surface *ecran, int r, int g, int b);
void printMatrixSDL(Matrix mat, int size, SDL_Surface *ecran);

#endif
