# ABOU ALI Magued, Février 2017

APPLI = equilibre.out
TEST = test.out
SRCDIR = src
SRCDIRTEST = test
CSRC = $(SRCDIR)/main.c $(SRCDIR)/grille.c $(SRCDIR)/file.c
CSRCTEST = $(SRCDIRTEST)/test.c
HDIR = headers
CHDR = $(HDIR)/grille.h $(HDIR)/file.h
OBJDIR = obj
COBJ = $(OBJDIR)/main.o $(OBJDIR)/grille.o $(OBJDIR)/file.o
COBJTEST = $(OBJDIR)/test.o
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -I$(HOME)/local/include
CFLAGSTEST = -L$(HOME)/local/lib -lcunit

app: $(APPLI)

$(APPLI): $(COBJ)
	$(CC) $(CFLAGS) -o $(APPLI) $(COBJ)

$(COBJ): $(CSRC) $(CHDR)
	$(CC) $(CFLAGS) -o $(OBJDIR)/main.o -c $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -o $(OBJDIR)/grille.o -c $(SRCDIR)/grille.c
	$(CC) $(CFLAGS) -o $(OBJDIR)/file.o -c $(SRCDIR)/file.c


test: $(TEST)

$(TEST): $(COBJTEST)
	$(CC) $(CFLAGSTEST) -o $(TEST) $(COBJTEST)

$(COBJTEST): $(CSRCTEST)
	$(CC) $(CFLAGS) -o $(OBJDIR)/test.o -c $(SRCDIRTEST)/test.c


clean:
	rm -rf *.out obj/*.o test/.temp.txt $(APPLI) $(TEST)
