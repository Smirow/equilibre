#include "../headers/couleur.h"

int main(void) {
	srand(time(NULL));

	FIFO *f;
	coordonnees* coord = initcoord();
	f = initFIFOVide();
	for (int i = 0; i < 5; ++i)
	{
		modifcoord(i,i,coord);
		constructeur(coord,f);    	
	}
	affiche(f);
	coord = defile(f);
	affiche(f);
    /*
    flux* f = openFile("test.txt");

    int size = checkFileFormat(f);
    Matrix M = initFromFile(f);
    printMatrix(M, size);

    close(f);
    */

}
