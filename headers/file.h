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


/**
 * \struct flux
 * \brief Objet flux.
 */
typedef struct flux {
  FILE *f;
} flux;

flux* openFile(char const*);
void close(flux*);
char* readALine(flux*);
int endOfFile(flux*);
int checkFileFormat(flux*);