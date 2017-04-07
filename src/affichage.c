#include <string.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <time.h>

#include "../headers/file.h"
#include "../headers/grille.h"
#include "../headers/affichage.h"



int menu(SDL_Surface *ecran, int *size, int *maxCoups, int nbCoupsSolveur) {
	SDL_Surface *titre=NULL, *taille=NULL, *difficulte=NULL, *fleched=NULL;
    SDL_Rect position;
    SDL_Event event;
    SDL_Color couleurtxt = {255, 255, 255, 0}; //le 0 enlève un warning
    char txttaille[100], txtdiff[100], niveaudiff[50];
    int vardiff=0, vartaille=0, positionmenu_x=0, positionmenu_y=0;

	TTF_Font *policetitre = NULL, *policetxt=NULL;

    policetitre = TTF_OpenFont("Symtext.ttf", 30);
    policetxt = TTF_OpenFont("Symtext.ttf", 20);
    titre = TTF_RenderText_Solid(policetitre, "Color Flood - Equilibre", couleurtxt);


    int continuer=1, quitter=1;
    while (continuer && quitter)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                return 0;
                break;
            case SDL_KEYDOWN:
            	switch(event.key.keysym.sym)
            	{
            		case SDLK_RETURN:
            			if(positionmenu_x==0)
	            			return 1;
	            		else
	            			return 0;
	            		break;
	            	case SDLK_UP:
	            		positionmenu_y--;
                        positionmenu_x=0;
	            		if(positionmenu_y<0)
	            			positionmenu_y=2;
    					fillScreen(ecran, rand()%255, rand()%255, rand()%255);
	            		break;
	            	case SDLK_DOWN:
	            		positionmenu_y++;
                        positionmenu_x=0;
	            		if(positionmenu_y>2)
	            			positionmenu_y=0;
    					fillScreen(ecran, rand()%255, rand()%255, rand()%255);
	            		break;
	            	case SDLK_LEFT:
	            		switch(positionmenu_y)
	            		{
	            			case 0:
	            				vartaille--;
	            				if(vartaille<0)
	            					vartaille=3;
	            				break;
	            			case 1:
	            				vardiff--;
	            				if(vardiff<0)
	            					vardiff=3;
	            				break;
		            		case 2:
			            		positionmenu_x++;
			            		positionmenu_x%=2;
			            		break;
	            		}
   						fillScreen(ecran, rand()%255, rand()%255, rand()%255); //pour rafraichir l'ecran lorsque le rectangle gris change de place
	            		break;
	            	case SDLK_RIGHT:
	            		switch(positionmenu_y)
	            		{
	            			case 0:
	            				vartaille++;
	            				if(vartaille>3)
	            					vartaille=0;
	            				break;
	            			case 1:
	            				vardiff++;
	            				if(vardiff>3)
	            					vardiff=0;
	            				break;
		            		case 2:
			            		positionmenu_x++;
			            		positionmenu_x%=2;
			            		break;
			            }
    					fillScreen(ecran, rand()%255, rand()%255, rand()%255);
	            		break;
	            	default:
	            		break;
		        }
            	break;
            case SDL_MOUSEBUTTONUP:
        		if (event.button.button == SDL_BUTTON_LEFT)
        		{
        			if(event.button.x>146 && event.button.x<181 && event.button.y>200 && event.button.y<235) //reduire la taille
        			{
        				positionmenu_y=0;
        				vartaille--;
        				if(vartaille<0)
        					vartaille=3;
        			}
        			else if(event.button.x>390 && event.button.x<425 && event.button.y>200 && event.button.y<235) //augmenter la taille
        			{
        				positionmenu_y=0;
        				vartaille++;
        				if(vartaille>3)
        					vartaille=0;
        			}
        			else if(event.button.x>194 && event.button.x<229 && event.button.y>314 && event.button.y<349) //reduire la difficulté
        			{
        				positionmenu_y=1;
        				vardiff--;
        				if(vardiff<0)
        					vardiff=3;
        			}
        			else if(event.button.x>469 && event.button.x<504 && event.button.y>314 && event.button.y<349) //augmenter la difficulté
        			{
        				positionmenu_y=1;
        				vardiff++;
        				if(vardiff>3)
        					vardiff=0;
        			} 
        			else if(event.button.x>80 && event.button.x<235 && event.button.y>450 && event.button.y<500) //démarrer
        				return 1;
        			else if(event.button.x>325 && event.button.x<445 && event.button.y>450 && event.button.y<500) //quitter
        				return 0;
    				fillScreen(ecran, rand()%255, rand()%255, rand()%255);

        		}
        		break;

        }

        switch(vartaille)
   		{
   			case 0:
   				*size=12;
   				break;
   			case 1:
   				*size=18;
   				break;
   			case 2:
   				*size=24;
   				break;
   			case 3:
   				*size=8;
   				break;
   		}

        sprintf(txttaille, "Taille   <         %d*%d", *size, *size);
        if(vartaille==3)
        {
        	sprintf(txttaille, "Taille   <   Personnalisee");
    	}
   		taille = TTF_RenderText_Solid(policetxt, txttaille, couleurtxt);

   		switch(vardiff)
   		{
   			case 0:
   				sprintf(niveaudiff, " Sans pression");
   				*maxCoups=nbCoupsSolveur+100;
   				break;
   			case 1:
   				sprintf(niveaudiff, "      Facile");
   				*maxCoups=nbCoupsSolveur+5;
   				break;
   			case 2:
   				sprintf(niveaudiff, "     Difficile");
   				*maxCoups=nbCoupsSolveur+2;
   				break;
   			case 3:
   				sprintf(niveaudiff, "Niveau solveur");
   				*maxCoups=nbCoupsSolveur;
   				break;
   		}
    	drawRectangle(ecran, 146, 200, 35, 35, 60, 60, 60); //carré gris de la fleche gauche de Taille
    	drawRectangle(ecran, 390, 200, 35, 35, 60, 60, 60); //carré gris de la fleche droite de Taille
    	drawRectangle(ecran, 194, 314, 35, 35, 60, 60, 60); //carré gris de la fleche gauche de Difficulté
    	drawRectangle(ecran, 469, 314, 35, 35, 60, 60, 60); //carré gris de la fleche droite de Difficulté
    	drawRectangle(ecran, ecran->w/1.55, ecran->h-50, 120, 45, 60, 60, 60); //carré gris Démarrer
    	drawRectangle(ecran, ecran->w/6, ecran->h-50, 150, 45, 60, 60, 60); //carré gris Quitter

        if(positionmenu_x==0 && positionmenu_y==2) //affichage des rectangles gris en fonction de la position dans le menu
        	drawRectangle(ecran, ecran->w/6, ecran->h-50, 150, 45, 100, 100, 100);
        else if(positionmenu_y==2)
        	drawRectangle(ecran, ecran->w/1.55, ecran->h-50, 120, 45, 100, 100, 100);
        else if(positionmenu_y==1)
        	drawRectangle(ecran, ecran->w/10-8, 2*ecran->h/3.2-7, 144, 45, 100, 100, 100);
        else
        	drawRectangle(ecran, ecran->w/10-8, ecran->h/2.5-7, 95, 45, 100, 100, 100);


        sprintf(txtdiff, "Difficulte   <    %s", niveaudiff);

    	difficulte = TTF_RenderText_Solid(policetxt, txtdiff, couleurtxt);
    	fleched = TTF_RenderText_Solid(policetxt, ">", couleurtxt);


        position.x = ecran->w/16;
        position.y = ecran->h/20;
        SDL_BlitSurface(titre, NULL, ecran, &position);

        position.x = ecran->w/10;
        position.y = ecran->h/2.5;
        SDL_BlitSurface(taille, NULL, ecran, &position);
        position.x = ecran->w-100;
        SDL_BlitSurface(fleched, NULL, ecran, &position);

        position.x = ecran->w/10;
        position.y = 2*ecran->h/3.2;
        SDL_BlitSurface(difficulte, NULL, ecran, &position);
        position.x = ecran->w-20;
        SDL_BlitSurface(fleched, NULL, ecran, &position);


        position.x = ecran->w/5;
        position.y = ecran->h-45;
        SDL_BlitSurface(TTF_RenderText_Solid(policetxt, "Demarrer", couleurtxt), NULL, ecran, &position);

        position.x = 2*ecran->w/3;
        position.y = ecran->h-45;
        SDL_BlitSurface(TTF_RenderText_Solid(policetxt, "Quitter", couleurtxt), NULL, ecran, &position);



        SDL_Flip(ecran);
    }

    TTF_CloseFont(policetitre);
    TTF_CloseFont(policetxt);
    return 1;
}

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

void drawRectangle(SDL_Surface *ecran, int px, int py, int sizew, int sizeh, int r, int g, int b) {
    SDL_Rect rect;
    rect.x = px;
    rect.y = py;
    rect.h = sizeh;
    rect.w = sizew;
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
                    drawRectangle(ecran,  (j*rectsize) + offsetW,  (i*rectsize) + offsetH, rectsize, rectsize, 201-dark, 20-dark, 24-dark);
                    break;
                case 2 :
                    /* GREEN */
                    drawRectangle(ecran,  (j*rectsize) + offsetW,  (i*rectsize) + offsetH, rectsize, rectsize, 77-dark, 142-dark, 21-dark);
                    break;              
                case 3 :
                    /* YELLOW */
                    drawRectangle(ecran,  (j*rectsize) + offsetW,  (i*rectsize) + offsetH, rectsize, rectsize, 194-dark, 143-dark, 20-dark);
                    break;
                case 4:
                    /* BLUE */
                    drawRectangle(ecran,  (j*rectsize) + offsetW,  (i*rectsize) + offsetH, rectsize, rectsize, 45-dark, 85-dark, 220-dark);
                    break;
                case 5 :
                    /* MAGENTA */
                    drawRectangle(ecran,  (j*rectsize) + offsetW,  (i*rectsize) + offsetH, rectsize, rectsize, 116-dark, 76-dark, 112-dark);
                    break;
                case 6 :
                    /* CYAN */
                    drawRectangle(ecran,  (j*rectsize) + offsetW,  (i*rectsize) + offsetH, rectsize, rectsize, 23-dark, 150-dark, 150-dark);
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
            drawRectangle(ecran, x, y+i*sizeSquare, sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);
            drawRectangle(ecran, x+4*sizeSquare, y+i*sizeSquare, sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);        
        }
        drawRectangle(ecran, x+sizeSquare/2+5, y+3*sizeSquare, sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);   
        drawRectangle(ecran, x+sizeSquare+5, y+4*sizeSquare, sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);   
        drawRectangle(ecran, x+sizeSquare*2, y+3*sizeSquare, sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);   
        drawRectangle(ecran, x+sizeSquare*3-5, y+4*sizeSquare, sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);   
        drawRectangle(ecran, x+sizeSquare*7/2-5, y+3*sizeSquare, sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);   
        drawRectangle(ecran, x+sizeSquare*2, y+2*sizeSquare+12, sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);   

        for (int i = 0; i < 5; ++i)
        {
             drawRectangle(ecran, x+6*sizeSquare, y+i*sizeSquare, sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);   
             drawRectangle(ecran, x+8*sizeSquare, y+i*sizeSquare, sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);   
             drawRectangle(ecran, x+12*sizeSquare, y+i*sizeSquare, sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);   
        }
             drawRectangle(ecran, x+9*sizeSquare, y+sizeSquare, sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);   
             drawRectangle(ecran, x+10*sizeSquare, y+2*sizeSquare, sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);
             drawRectangle(ecran, x+11*sizeSquare, y+3*sizeSquare, sizeSquare, sizeSquare, 255-varr, 255-varg, 255-varb);

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
            drawRectangle(ecran, x, y+i*sizeSquare, sizeSquare, sizeSquare, r, g ,b);                   //L
    
            drawRectangle(ecran, x+5*sizeSquare, y+i*sizeSquare, sizeSquare, sizeSquare, r, g ,b);      //O 
            drawRectangle(ecran, x+8*sizeSquare, y+i*sizeSquare, sizeSquare, sizeSquare, r, g ,b);    
    
            drawRectangle(ecran, x+15*sizeSquare, y+i*sizeSquare, sizeSquare, sizeSquare, r, g ,b);      //E    
        }
    
        for (int i = 0; i < 4; ++i)
        {
            drawRectangle(ecran, x+i*sizeSquare, y+6*sizeSquare, sizeSquare, sizeSquare, r, g ,b);      //L
    
            drawRectangle(ecran, x+(i+5)*sizeSquare, y, sizeSquare, sizeSquare, r, g ,b);               //0
            drawRectangle(ecran, x+(i+5)*sizeSquare, y+6*sizeSquare, sizeSquare, sizeSquare, r, g ,b); 
    
            drawRectangle(ecran, x+(i+10)*sizeSquare, y, sizeSquare, sizeSquare, r, g ,b);              //S
            drawRectangle(ecran, x+(i+10)*sizeSquare, y+3*sizeSquare, sizeSquare, sizeSquare, r, g ,b);      
            drawRectangle(ecran, x+(i+10)*sizeSquare, y+6*sizeSquare, sizeSquare, sizeSquare, r, g ,b);    
            drawRectangle(ecran, x+10*sizeSquare, y+i*sizeSquare, sizeSquare, sizeSquare, r, g , b);      
            drawRectangle(ecran, x+13*sizeSquare, y+(i+3)*sizeSquare, sizeSquare, sizeSquare, r, g ,b);      
    
            drawRectangle(ecran, x+(i+15)*sizeSquare, y, sizeSquare, sizeSquare, r, g ,b);              //E     
            drawRectangle(ecran, x+(i+15)*sizeSquare, y+6*sizeSquare, sizeSquare, sizeSquare, r, g ,b);      
        }
    
        for (int i = 0; i < 3; ++i)
        {
            drawRectangle(ecran, x+(i+15)*sizeSquare, y+3*sizeSquare, sizeSquare, sizeSquare, r, g ,b);      
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