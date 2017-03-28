#ifndef __SOLV_RAND_H
#define __SOLV_RAND_H

#include "../headers/couleur.h"


FIFO* solv_random(Matrix grille, int size);
int best_solv_rand(Matrix matrix, int size);
int size_random(Matrix matrix, int size);
FIFO* best_solv_rand_FIFO(Matrix matrix, int size);

#endif