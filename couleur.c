#include "couleur.h"
#include "grille.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>

void remplace(Matrix grille,int x,int y,int c){
	grille[x][y]= c;
}