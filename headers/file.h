/**
 * \file file.c
 * \brief Gestion des accès fichiers
 * \author Team Équilibre
 * \version 0.0.1
 * \date 10 fevrier 2017
 */

#ifndef __FILE_H
#define __FILE_H


/**
 * \struct flux
 * \brief Objet flux.
 */
typedef struct flux {
  FILE *f;
} flux;

flux* openFile(char const*);
void closeFile(flux*);
char* readALine(flux*);
int endOfFile(flux*);
int checkFileFormat(flux*);

#endif
