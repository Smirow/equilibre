#ifndef __AFFICHAGE_H
#define __AFFICHAGE_H

int getsValue(char* str, int min);
SDL_Surface* initSDLwindow();
void drawRectangle(SDL_Surface *ecran, int px, int py, int size, int r, int g, int b);
void fillScreen(SDL_Surface *ecran, int r, int g, int b);
void printMatrixSDL(Matrix mat, int size, SDL_Surface *ecran);
int getValueMatrix(int x, int y, Matrix matrix, int size, SDL_Surface *ecran);
void printWin();

#endif
