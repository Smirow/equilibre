#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>



int getColor() {
    char s[100];
    fgets(s, sizeof(s), stdin);
    int res = 0;
    switch(s[0]) {
        case 'R':
            res = 1;
            break;
        case 'G':
            res = 2;
            break;
        case 'Y':
            res = 3;
            break;
        case 'B':
            res = 4;
            break;
        case 'M':
            res = 5;
            break;
        case 'C':
            res = 6;
            break;
        default:
            res = 0;
    }
    return res;
}


int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
 
    SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
 
    SDL_Quit();
 
    return EXIT_SUCCESS;
}