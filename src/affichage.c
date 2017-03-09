#include <string.h>
#include <unistd.h>
#include <SDL/SDL.h>

#include "../headers/file.h"
#include "../headers/grille.h"
#include "../headers/affichage.h"


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

SDL_Surface* initSDLwindow(int width, int height){

    if(SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        fprintf( stderr, "Video initialization failed: %s\n", SDL_GetError( ) );
        SDL_Quit();
    }
    SDL_Surface *screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE);

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

void printMatrixSDL(Matrix mat, int size, SDL_Surface *ecran, int dark){    
    int rectsize=ecran->w/size;
    for(int i = 0; i < size ; i++) {
        for(int j = 0; j < size ; j++) {
            switch(mat[i][j]) {
                case 1 :
                    /* RED */
                    drawRectangle(ecran,  j*rectsize,  i*rectsize, rectsize, 201-dark, 3-dark, 14-dark);
                    break;
                case 2 :
                    /* GREEN */
                    drawRectangle(ecran,  j*rectsize,  i*rectsize, rectsize, 77-dark, 142-dark, 11-dark);
                    break;              
                case 3 :
                    /* YELLOW */
                    drawRectangle(ecran,  j*rectsize,  i*rectsize, rectsize, 194-dark, 143-dark, 10-dark);
                    break;
                case 4:
                    /* BLUE */
                    drawRectangle(ecran,  j*rectsize,  i*rectsize, rectsize, 53-dark, 91-dark, 235-dark);
                    break;
                case 5 :
                    /* MAGENTA */
                    drawRectangle(ecran,  j*rectsize,  i*rectsize, rectsize, 116-dark, 76-dark, 112-dark);
                    break;
                case 6 :
                    /* CYAN */
                    drawRectangle(ecran,  j*rectsize,  i*rectsize, rectsize, 13-dark, 112-dark, 104-dark);
                    break;
                default:
                    printf("error\n");
            }
        }
    }
    SDL_Flip(ecran);
}

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

int getValueMatrix(int x, int y, Matrix matrix, int size, SDL_Surface *ecran) {
    if (x < ecran->h && y < ecran->w)
        return matrix[y/(ecran->w/size)][x/(ecran->w/size)];
    return 0;
}
