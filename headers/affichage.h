#ifndef __AFFICHAGE_H
#define __AFFICHAGE_H

int menu(SDL_Surface *ecran, int *size, int *maxCoups, int nbCoupsSolveur);
int getsValue(char* str, int min);
SDL_Surface* initSDLwindow();
void drawRectangle(SDL_Surface *ecran, int px, int py, int sizew, int sizeh, int r, int g, int b);
void fillScreen(SDL_Surface *ecran, int r, int g, int b);
void printMatrixSDL(Matrix mat, int size, SDL_Surface *ecran, int dark);
int getValueMatrix(int x, int y, Matrix matrix, int size, SDL_Surface *ecran);
void affiche_win(SDL_Surface *ecran,int size, int couleur);
void affiche_lose(SDL_Surface *ecran,int size);

#endif
