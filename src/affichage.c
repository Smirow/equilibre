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



void affiche_win(SDL_Surface *ecran,int size, int couleur){
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

    int varr=0, varg=0, varb=0;
    int compteurcouleur=0, switchcouleur=0, click=0, r=0, g=0, b=0;
    SDL_Event event;

    switch(couleur)
    {
        case 1 :
            r=201, g=20, b=24;
            break;
        case 2 :
            r=77, g=142, b=21;
            break;              
        case 3 :
            r=194, g=143, b=20;
            break;
        case 4:
            r=45, g=85, b=220;
            break;
        case 5 :
            r=116, g=76, b=112;
            break;
        case 6 :
            r=23, g=150, b=150;
            break;
        default :
            r=0, g=0, b=0;
            break;
    }
    while(click==0)
    {
        if(switchcouleur==0)
        {
            varr+=r/30, varg+=g/30, varb+=b/30;
            compteurcouleur++;
            if(compteurcouleur==30)
                switchcouleur=1;
        }
        else
        {
            varr-=r/30, varg-=g/30, varb-=b/30;
            compteurcouleur--;
            if(compteurcouleur==0)
                switchcouleur=0;
        }
        for (int i = 0; i < 3; ++i)
        {
            drawRectangle(ecran, x, y+i*sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);
            drawRectangle(ecran, x+4*sizeSquare, y+i*sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);        
        }
        drawRectangle(ecran, x+sizeSquare/2+5, y+3*sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);   
        drawRectangle(ecran, x+sizeSquare+5, y+4*sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);   
        drawRectangle(ecran, x+sizeSquare*2, y+3*sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);   
        drawRectangle(ecran, x+sizeSquare*3-5, y+4*sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);   
        drawRectangle(ecran, x+sizeSquare*7/2-5, y+3*sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);   
        drawRectangle(ecran, x+sizeSquare*2, y+2*sizeSquare+12, sizeSquare, 255-varr, 255-varg, 255-varb);   

        for (int i = 0; i < 5; ++i)
        {
             drawRectangle(ecran, x+6*sizeSquare, y+i*sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);   
             drawRectangle(ecran, x+8*sizeSquare, y+i*sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);   
             drawRectangle(ecran, x+12*sizeSquare, y+i*sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);   
        }
             drawRectangle(ecran, x+9*sizeSquare, y+sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);   
             drawRectangle(ecran, x+10*sizeSquare, y+2*sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);
             drawRectangle(ecran, x+11*sizeSquare, y+3*sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);

        SDL_Flip(ecran);
        nanosleep((const struct timespec[]){{0, 10000000L}}, NULL);
        while(SDL_PollEvent(&event))
        { 
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                    click = 1;
            }
            if(event.type==SDL_QUIT)
                click=1;
        }
    }
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

    int r=0, g=0, b=240;
    int switchcouleur=0, click=0;
    SDL_Event event;
    while(click==0)
    {
        if(switchcouleur==0)
        {
            r+=8;
            b-=8;
            if(r>=240)
                switchcouleur=1;
        }
        else if(switchcouleur==1)
        {
            g+=8;
            r-=8;
            if(g>=240)
                switchcouleur=2;
        }
        else
        {
            b+=8;
            g-=8;
            if(b>=240)
                switchcouleur=0;
        }
        for (int i = 0; i < 7; ++i)
        {
            drawRectangle(ecran, x, y+i*sizeSquare, sizeSquare, r, g ,b);                   //L
    
            drawRectangle(ecran, x+5*sizeSquare, y+i*sizeSquare, sizeSquare, r, g ,b);      //O 
            drawRectangle(ecran, x+8*sizeSquare, y+i*sizeSquare, sizeSquare, r, g ,b);    
    
            drawRectangle(ecran, x+15*sizeSquare, y+i*sizeSquare, sizeSquare, r, g ,b);      //E    
        }
    
        for (int i = 0; i < 4; ++i)
        {
            drawRectangle(ecran, x+i*sizeSquare, y+6*sizeSquare, sizeSquare, r, g ,b);      //L
    
            drawRectangle(ecran, x+(i+5)*sizeSquare, y, sizeSquare, r, g ,b);               //0
            drawRectangle(ecran, x+(i+5)*sizeSquare, y+6*sizeSquare, sizeSquare, r, g ,b); 
    
            drawRectangle(ecran, x+(i+10)*sizeSquare, y, sizeSquare, r, g ,b);              //S
            drawRectangle(ecran, x+(i+10)*sizeSquare, y+3*sizeSquare, sizeSquare, r, g ,b);      
            drawRectangle(ecran, x+(i+10)*sizeSquare, y+6*sizeSquare, sizeSquare, r, g ,b);    
            drawRectangle(ecran, x+10*sizeSquare, y+i*sizeSquare, sizeSquare, r, g , b);      
            drawRectangle(ecran, x+13*sizeSquare, y+(i+3)*sizeSquare, sizeSquare, r, g ,b);      
    
            drawRectangle(ecran, x+(i+15)*sizeSquare, y, sizeSquare, r, g ,b);              //E     
            drawRectangle(ecran, x+(i+15)*sizeSquare, y+6*sizeSquare, sizeSquare, r, g ,b);      
        }
    
        for (int i = 0; i < 3; ++i)
        {
            drawRectangle(ecran, x+(i+15)*sizeSquare, y+3*sizeSquare, sizeSquare, r, g ,b);      
        }
        SDL_Flip(ecran);
        nanosleep((const struct timespec[]){{0, 20000000L}}, NULL);
        while(SDL_PollEvent(&event))
        { 
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                    click = 1;
            }
            if(event.type==SDL_QUIT)
                click=1;
        }

    }
}