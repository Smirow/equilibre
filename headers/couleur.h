#ifndef __COULEUR_H
#define __COULEUR_H

extern void remplace(Matrix grille,int x,int y,int c);
extern FIFO initFIFOVide();
extern int vide(FIFO f);
extern void constructeur(coordonnees coord,FIFO f);
extern coordonnees depile(FIFO f);

#endif