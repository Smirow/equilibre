#include "../headers/couleur.h"


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


int main(void) {
	srand(time(NULL));

    /* Petit fixe pour valgrind */
	int *hh = NULL;
	hh = malloc(sizeof(int));
	free(hh);
	/* ----------- */

    int boolwin = 0;
    int maxCoups = 0;

    flux* fichier = openFile("test.txt");

    int size = checkFileFormat(fichier);
    Matrix M = initFromFile(fichier);

    int preMax = 0;
    char *p, s[100];
    printf("Entrez un nombre maximum de coups: ");
    fgets(s, sizeof(s), stdin);
    preMax = strtol(s, &p, 10);
    if(preMax >= 1) {
		maxCoups = preMax;
	}
    else {
        printf("Erreur, bye.\n");
        exit(1);
    }



	
    int n;
    int nbCoups = 0;
    printf("---------------------------------\n");
    printMatrix(M, size);
	printf("Entrez une couleur: ");
    while (!boolwin && nbCoups < maxCoups) {
        n = getColor();
        if(n >= 1 && n <= 7) {
            nbCoups++;
			changeCC(M, n, size);
		    boolwin = win(M, size);
            printf("Il vous reste %d coups.\n", maxCoups-nbCoups);
			printMatrix(M, size);
		}
		else {
		    printf("Entrez une couleur possible.\n");
		}
        if (boolwin) printf("Vous avez gagné !\n");
        else if (nbCoups >= maxCoups) printf("Vous avez depassé le nombre max de coups...\n");
        else printf("Rentrez une couleur: ");
    }

	freeMatrix(M, size);
	close(fichier);
	return 0;

}