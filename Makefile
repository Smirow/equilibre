# ABOU ALI Magued, Février 2017

APPLI = equilibre
SRCDIR = src
CSRC = $(SRCDIR)/main.c $(SRCDIR)/grille.c $(SRCDIR)/file.c
HDIR = headers
CHDR = $(HDIR)/grille.h $(HDIR)/file.h
OBJDIR = obj
COBJ = $(OBJDIR)/main.o $(OBJDIR)/grille.o $(OBJDIR)/file.o
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -ansi

all: $(APPLI)

$(APPLI): $(COBJ)
	$(CC) -o $(APPLI) $(COBJ)

$(COBJ): $(CSRC) $(CHDR)
	$(CC) $(CFLAGS) -o $(OBJDIR)/main.o -c $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -o $(OBJDIR)/grille.o -c $(SRCDIR)/grille.c
	$(CC) $(CFLAGS) -o $(OBJDIR)/file.o -c $(SRCDIR)/file.c

clean:
	rm -rf obj/*.o $(APPLI)
