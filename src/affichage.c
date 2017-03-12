/**
 * \file affichage.c
 * \brief Fonctionnalité S2 : SDL
 * \author Team Équilibre
 * \version 0.0.1
 * \date 10 Mars 2017
 */
#include <string.h>
#include <unistd.h>
#include <SDL/SDL.h>

#include "../headers/file.h"
#include "../headers/grille.h"
#include "../headers/affichage.h"

/**
 * \fn int getsValue(char* str, int min)
 * \brief Demande à l'utilisateur une valeur
 *
 * \param char* str Le message à affiché.
 * \param int min Le minimum de la valeur souhaité.
 * \return int la valeur entrée par l'utilisateur
 */
int getsValue(char* str, int min) {
    int res = 0;
    char *p1, s1[100];
    while (1) {
        printf("%s", str);
        if (!fgets(s1, sizeof(s1), stdin))
            perror("Error fgets");
        res = strtol(s1, &p1, 10);
        if  (res >= min) {
            return res;
        }
        printf("Wrong input, please retry.\n");
    }
}


/**
 * \fn SDL_Surface* initSDLwindow(int width, int height)
 * \brief Initialise la fenêtre à l'aide de la SDL
 *
 * \param int width la longeur de la fenetre.
 * \param int height la largeur de la fenetre.
 * \return SDL_Surface* la surface SDL 
 */
SDL_Surface* initSDLwindow(int width, int height) {

    if(SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        fprintf( stderr, "Video initialization failed: %s\n", SDL_GetError( ) );
        SDL_Quit();
    }
    SDL_Surface *screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_RESIZABLE);

    fillScreen(screen, 30, 30, 30);
    SDL_WM_SetCaption("Color Flood Equilibre", NULL);


    return screen;
}


/**
 * \fn void drawRectangle(SDL_Surface *ecran, int px, int py, int size, int r, int g, int b)
 * \brief dessine un carrée dans la fenetre 
 *
 * \param SDL_Surface *ecran la surface sur laquelle dessiner
 * \param int px la position X du pixel haut gauche
 * \param int py la position Y du pixel haut gauche
 * \param int size la tailel du carrée à affiché
 * \param int r la composante rouge de la couleur du carrée
 * \param int g la composante verte de la couleur du carrée
 * \param int b la composante bleue  de la couleur du carrée
 */
void drawRectangle(SDL_Surface *ecran, int px, int py, int size, int r, int g, int b) {
    SDL_Rect rect;
    rect.x = px;
    rect.y = py;
    rect.h = size;
    rect.w = size;
    SDL_FillRect(ecran, &rect, SDL_MapRGB(ecran->format, r, g, b));
}


/**
 * \fn void fillScreen(SDL_Surface *ecran, int r, int g, int b)
 * \brief Colorie le "fond" de la fenetre 
 *
 * \param SDL_Surface *ecran la surface SDL
 * \param int r la composante rouge de la couleur du carrée
 * \param int g la composante verte de la couleur du carrée
 * \param int b la composante bleue  de la couleur du carrée
 */
void fillScreen(SDL_Surface *ecran, int r, int g, int b) {
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, r, g, b));
    SDL_Flip(ecran);
}


/**
 * \fn void printMatrixSDL(Matrix mat, int size, SDL_Surface *ecran, int dark)
 * \brief affiche la grille sur la fenetre
 *
 * \param Matrix mat la grille
 * \param int size la taille de la grille
 * \param SDL_Surface *ecran la surface SDL
 * \param int dark decallage vers la gauche des couleurs
 */
void printMatrixSDL(Matrix mat, int size, SDL_Surface *ecran, int dark) { 
    fillScreen(ecran, 30, 30, 30);
    int sizeToConsider = ecran->w;
    if (ecran->w > ecran->h)
        sizeToConsider = ecran->h;
    int rectsize = sizeToConsider/size;
    int offset = (sizeToConsider%size)/2;
    int offsetW = (ecran->w - sizeToConsider)/2 + offset;
    int offsetH = (ecran->h - sizeToConsider)/2 + offset;
    for(int i = 0; i < size ; i++) {
        for(int j = 0; j < size ; j++) {
            switch(mat[i][j]) {
                case 1 :
                    /* RED */
                    drawRectangle(ecran,  (j*rectsize) + offsetW,  (i*rectsize) + offsetH, rectsize, 201-dark, 20-dark, 24-dark);
                    break;
                case 2 :
                    /* GREEN */
                    drawRectangle(ecran,  (j*rectsize) + offsetW,  (i*rectsize) + offsetH, rectsize, 77-dark, 142-dark, 21-dark);
                    break;              
                case 3 :
                    /* YELLOW */
                    drawRectangle(ecran,  (j*rectsize) + offsetW,  (i*rectsize) + offsetH, rectsize, 194-dark, 143-dark, 20-dark);
                    break;
                case 4:
                    /* BLUE */
                    drawRectangle(ecran,  (j*rectsize) + offsetW,  (i*rectsize) + offsetH, rectsize, 45-dark, 85-dark, 220-dark);
                    break;
                case 5 :
                    /* MAGENTA */
                    drawRectangle(ecran,  (j*rectsize) + offsetW,  (i*rectsize) + offsetH, rectsize, 116-dark, 76-dark, 112-dark);
                    break;
                case 6 :
                    /* CYAN */
                    drawRectangle(ecran,  (j*rectsize) + offsetW,  (i*rectsize) + offsetH, rectsize, 23-dark, 150-dark, 150-dark);
                    break;
                default:
                    printf("error\n");
            }
        }
    }
    SDL_Flip(ecran);
}


/**
 * \fn void printWin()
 * \brief fonction de fin de partie
 *
 */
void printWin() {
    SDL_Event event;
    int quit = 1;
    while(quit) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT: 
                quit = 0; 
                break;
            case SDL_MOUSEBUTTONUP: 
                quit = 0; 
                break;
        }
    }
}


/**
 * \fn int getValueMatrix(int x, int y, Matrix matrix, int size, SDL_Surface *ecran)
 * \brief Retrouve la valeur de la case sous ajacente au clic
 *
 * \param int x position X du clic
 * \param int y position Y du clic
 * \param Matrix mat la grille
 * \param int size la taille de la grille
 * \param SDL_Surface *ecran la surface SDL
 * \return int la valeur de la case
 */
int getValueMatrix(int x, int y, Matrix matrix, int size, SDL_Surface *ecran) {
    int sizeToConsider = ecran->w;
    if (ecran->w > ecran->h) 
        sizeToConsider = ecran->h;
    int rectsize = sizeToConsider/size;
    int offset = (sizeToConsider%size)/2;
    int offsetW = (ecran->w - sizeToConsider)/2 + offset;
    int offsetH = (ecran->h - sizeToConsider)/2 + offset;
    if (x > (offsetW) && x < (ecran->w - offsetW) && y > (offsetH) && y < (ecran->h - offsetH)) {
        return matrix[(y - offsetH)/rectsize][(x - offsetW)/rectsize];
    }
    return 0;
}
