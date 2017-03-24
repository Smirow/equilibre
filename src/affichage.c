#include <string.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <time.h>

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
    SDL_Surface *screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_RESIZABLE);

    fillScreen(screen, 30, 30, 30);
    SDL_WM_SetCaption("Color Flood Equilibre", NULL);


    return screen;
}

// px, py coordonnées haut, gauche du pixel
void drawRectangle(SDL_Surface *ecran, int px, int py, int size, int r, int g, int b) {
    SDL_Rect rect;
    rect.x = px;
    rect.y = py;
    rect.h = size;
    rect.w = size;
    SDL_FillRect(ecran, &rect, SDL_MapRGB(ecran->format, r, g, b));
}

void fillScreen(SDL_Surface *ecran, int r, int g, int b) {
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, r, g, b));
    SDL_Flip(ecran);
}

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



/*void drawRectangle(SDL_Surface *ecran, int px, int py, int size, int r, int g, int b) */
void affiche_win(SDL_Surface *ecran,int size){
    int x = 0,y = 0;
    int sizeToConsider = ecran->w;
    if (ecran->w > ecran->h) 
        sizeToConsider = ecran->h;
    int offset = (sizeToConsider%size)/2;
    int offsetW = (ecran->w - sizeToConsider)/2 + offset/2;
    int offsetH = (ecran->h - sizeToConsider)/2 + offset;
    int sizeSquare = sizeToConsider/17;

    x = offsetW + 2*sizeSquare;
    y = offsetH + ecran->h/3;
    for (int i = 0; i < 3; ++i)
    {
        drawRectangle(ecran, x, y+i*sizeSquare, sizeSquare, 255, 255, 255);
        drawRectangle(ecran, x+4*sizeSquare, y+i*sizeSquare, sizeSquare, 255, 255, 255);        
    }
    drawRectangle(ecran, x+sizeSquare/2+5, y+3*sizeSquare, sizeSquare, 255, 255, 255);   
    drawRectangle(ecran, x+sizeSquare+5, y+4*sizeSquare, sizeSquare, 255, 255, 255);   
    drawRectangle(ecran, x+sizeSquare*2, y+3*sizeSquare, sizeSquare, 255, 255, 255);   
    drawRectangle(ecran, x+sizeSquare*3-5, y+4*sizeSquare, sizeSquare, 255, 255, 255);   
    drawRectangle(ecran, x+sizeSquare*7/2-5, y+3*sizeSquare, sizeSquare, 255, 255, 255);   
    drawRectangle(ecran, x+sizeSquare*2, y+2*sizeSquare+12, sizeSquare, 255, 255, 255);   

    for (int i = 0; i < 5; ++i)
    {
         drawRectangle(ecran, x+6*sizeSquare, y+i*sizeSquare, sizeSquare, 255, 255, 255);   
         drawRectangle(ecran, x+8*sizeSquare, y+i*sizeSquare, sizeSquare, 255, 255, 255);   
         drawRectangle(ecran, x+12*sizeSquare, y+i*sizeSquare, sizeSquare, 255, 255, 255);   
    }
         drawRectangle(ecran, x+9*sizeSquare, y+sizeSquare, sizeSquare, 255, 255, 255);   
         drawRectangle(ecran, x+10*sizeSquare, y+2*sizeSquare, sizeSquare, 255, 255, 255);
         drawRectangle(ecran, x+11*sizeSquare, y+3*sizeSquare, sizeSquare, 255, 255, 255);

}

void affiche_lose(SDL_Surface *ecran,int size){
    int x = 0,y = 0;
    int sizeToConsider = ecran->w;
    if (ecran->w > ecran->h) 
        sizeToConsider = ecran->h;
    int offset = (sizeToConsider%size)/2;
    int offsetW = (ecran->w - sizeToConsider)/2 + offset/2;
    int offsetH = (ecran->h - sizeToConsider)/2 + offset;
    int sizeSquare = sizeToConsider/22;

    x = offsetW + 2*sizeSquare;
    y = offsetH + ecran->h/3;

    int puiss2=0;
    int ok=0;
    for(int j=0 ; j<252 ; j++)
    {
        if(ok==0)
        {
            puiss2+=2;
            if(puiss2>250)
            {
                ok=1;
            }
        }
        else
        {
            puiss2-=2;
        }
        for (int i = 0; i < 7; ++i)
        {
            drawRectangle(ecran, x, y+i*sizeSquare, sizeSquare, puiss2, 0 ,255-puiss2);                   //L
    
            drawRectangle(ecran, x+5*sizeSquare, y+i*sizeSquare, sizeSquare, puiss2, 0 ,255-puiss2);      //O 
            drawRectangle(ecran, x+8*sizeSquare, y+i*sizeSquare, sizeSquare, puiss2, 0 ,255-puiss2);    
    
            drawRectangle(ecran, x+15*sizeSquare, y+i*sizeSquare, sizeSquare, puiss2, 0 ,255-puiss2);      //E    
        }
    
        for (int i = 0; i < 4; ++i)
        {
            drawRectangle(ecran, x+i*sizeSquare, y+6*sizeSquare, sizeSquare, puiss2, 0 ,255-puiss2);      //L
    
            drawRectangle(ecran, x+(i+5)*sizeSquare, y, sizeSquare, puiss2, 0 ,255-puiss2);               //0
            drawRectangle(ecran, x+(i+5)*sizeSquare, y+6*sizeSquare, sizeSquare, puiss2, 0 ,255-puiss2); 
    
            drawRectangle(ecran, x+(i+10)*sizeSquare, y, sizeSquare, puiss2, 0 ,255-puiss2);              //S
            drawRectangle(ecran, x+(i+10)*sizeSquare, y+3*sizeSquare, sizeSquare, puiss2, 0 ,255-puiss2);      
            drawRectangle(ecran, x+(i+10)*sizeSquare, y+6*sizeSquare, sizeSquare, puiss2, 0 ,255-puiss2);    
            drawRectangle(ecran, x+10*sizeSquare, y+i*sizeSquare, sizeSquare, puiss2, 0 ,255-puiss2);      
            drawRectangle(ecran, x+13*sizeSquare, y+(i+3)*sizeSquare, sizeSquare, puiss2, 0 ,255-puiss2);      
    
            drawRectangle(ecran, x+(i+15)*sizeSquare, y, sizeSquare, puiss2, 0 ,255-puiss2);              //E     
            drawRectangle(ecran, x+(i+15)*sizeSquare, y+6*sizeSquare, sizeSquare, puiss2, 0 ,255-puiss2);      
        }
    
        for (int i = 0; i < 3; ++i)
        {
            drawRectangle(ecran, x+(i+15)*sizeSquare, y+3*sizeSquare, sizeSquare, puiss2, 0 ,255-puiss2);      
        }
        SDL_Flip(ecran);
        nanosleep((const struct timespec[]){{0, 10000000L}}, NULL);
    }
}