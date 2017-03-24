/**
 * \file file.c
 * \brief Gestion des accès fichiers
 * \author Team Équilibre
 * \version 0.0.1
 * \date 10 fevrier 2017
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/file.h"

int BUFF_MAX = 200;


/**
 * \fn flux* openFile(char const* s)
 * \brief Ouverture d'un fichier.
 *
 * \param char const* s correspondant au path du fichier.
 * \return flux* Un object de type flux*.
 */
flux* openFile(char const* s) {
    flux* r = malloc(sizeof(*r));
    r->f = fopen(s, "r");
    if (!r->f) {
        fprintf(stderr,"impossible d'ouvrir fichier %s\n", s);
        exit(1);
    }
    return r;
}


/**
 * \fn void close(flux* f)
 * \brief Fermeture du flux et libération mémoire..
 *
 * \param flux* f correspondant au flux à fermer.
 */
void closeFile(flux* f) {
    fclose(f->f);
    free(f);
}


/**
 * \fn char* readALine(flux* f)
 * \brief Lecture d'une ligne sur le flux.
 *
 * \param flux* f correspondant au flux à lire..
 * \return char* La ligne char*.
 */
char* readALine(flux* f) {
    char* buf = malloc(BUFF_MAX);
    char* ret = fgets(buf, BUFF_MAX, f->f);
    if (ret) {
        char* end = strchr(buf, '\n');
        if (end) *end = 0;
    } else {
        free(buf);
    }
    return ret;
}


/**
 * \fn int endOfFile(flux* f)
 * \brief Vérifie si le la fin du fichier est atteinte.
 *
 * \param flux* f correspondant au flux à lire.
 * \return int 1 ou 0.
 */
int endOfFile(flux* f) {
    return feof(f->f);
}


/**
 * \fn int checkFileFormat(flux* f)
 * \brief Vérifie le formatage du fichier.
 *
 * \param flux* f correspondant au flux à lire.
 * \return int len la taille de la matrice carrée.
 */
int checkFileFormat(flux* f) {
    char* m = readALine(f);
    int len = (int) strlen(m);
    rewind(f->f);
    if (m) {
        for(int i = 1; i <= len; i++){
            char* m = readALine(f);
            if(m) {
                if(!((int) strlen(m) == len)) {
                    fprintf(stderr, "Impossible de lire le fichier ligne %d. \n", i);
                    exit(1);
                }
            }
            else {
                fprintf(stderr, "Impossible de lire le fichier ligne %d. \n", i);
                exit(1);
            }
            free(m);
        }
    }
    else  {
        fprintf(stderr, "Impossible de lire le fichier ligne 1.");
        exit(1);
    }
    free(m);
    rewind(f->f);
    return len;
}
