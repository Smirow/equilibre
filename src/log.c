#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/stat.h>

#include "../headers/log.h"

const char* getStatusChar(enum status sta) {
   switch (sta) {
       case game: return "GAME";
       case solver: return "SOLVER";
       case info: return "INFO";
       case debug: return "DEBUG";
       case warning: return "WARNING";
       case error: return "ERROR";
   }
}


void printLog(status sta, const char* str, ...) {
    if (sta != debug || (sta == debug && DEBUG)) {
        FILE *gamelog;
        gamelog = fopen("logs/game.log", "a+");

        time_t  now;
        char    buffer[20];
        va_list args;

        va_start(args, str);
        time(&now);
        strftime(buffer, sizeof(buffer), "%x - %H:%M:%S", localtime(&now));
        /* To stdout only game's logs or erros except in DEBUG we will print all logs to stdout */
        if (DEBUG || sta == game || sta == error) {
            fprintf(stdout,"[%s]", buffer);
            fprintf(stdout,"[%s] ", getStatusChar(sta));
            vfprintf(stdout, str, args);
            fputc('\n', stdout);
        }
        /* To File */
        fprintf(gamelog,"[%s]", buffer);
        fprintf(gamelog,"[%s] ", getStatusChar(sta));
        vfprintf(gamelog, str, args);
        fputc('\n', gamelog);

        va_end(args);
        fclose(gamelog);
    }
}


void initLog() {
    mkdir("logs", 0700);
    FILE *gamelog;
    gamelog = fopen("logs/game.log", "ab+");
    if (gamelog == NULL) {
        /* Quitte le programme en cas d'erreur d'initialisation */
        perror("Error when initializing log files ");
        exit(1);
    }
    else {
        printLog(info, "-----------------------------");
        printLog(info, "Log initialized successfully.");
        fclose(gamelog);
    }
}