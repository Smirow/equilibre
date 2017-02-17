#include "../headers/couleur.h"

int main(void) {
	srand(time(NULL));

	FIFO *f;
	coordonnees* coord = initcoord();
	f = initFIFOVide();
	int boolwin=0;
	/*for (int i = 0; i < 5; ++i)
	{
		modifcoord(i,i,coord);
		constructeur(coord,f);    	
	}
	affiche(f);
	coord = defile(f);
	affiche(f);*/

    flux* file = openFile("test.txt");

    int size = checkFileFormat(file);
    Matrix M = initFromFile(file);
    printMatrix(M, size);
    close(file);


    int tap=1;
	while(tap!=0 && !boolwin)
	{
		printf("RENTRE UNE COULEUR STP :");	
		scanf("%d", &tap);
		while(tap < 1 || tap > 7)
		{
			printf("RENTRE UNE COULEUR STP :");	
			scanf("%d", &tap);
		}
		boolwin = win(changeCC(M, tap, size), size);
    	printMatrix(M, size);
	}

	return 0;
}
