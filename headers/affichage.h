/**
 * \file couleur.h
 * \brief Fonctionnalité S1.2 : Couleur
 * \author Team Équilibre
 * \version 0.0.1
 * \date 18 fevrier 2017
 *
 */

#ifndef __COULEUR_H
#define __COULEUR_H
#include "../headers/file.h"
#include "../headers/grille.h"

void drawRectangle(SDL_Surface *ecran, int px, int py, int size, int r, int g, int b);
void fillScreen(SDL_Surface *ecran, int r, int g, int b);
void printMatrixSDL(Matrix mat, int size, SDL_Surface *ecran);
SDL_Surface* initSDLwindow();

#endif
