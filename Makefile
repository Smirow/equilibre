# ABOU ALI Magued, Février 2017

CC = gcc
SRCDIR = src
HDIR = headers
OBJDIR = obj
TESTDIR = test
MKDIR = mkdir -p

APP = equilibre.out
CSRC = $(SRCDIR)/main.c $(SRCDIR)/grille.c $(SRCDIR)/file.c $(SRCDIR)/couleur.c
CHDR = $(HDIR)/grille.h $(HDIR)/file.h $(HDIR)/couleur.h
COBJMAIN = $(OBJDIR)/main.o
COBJ = $(OBJDIR)/grille.o $(OBJDIR)/file.o $(OBJDIR)/couleur.o
CFLAGS = -std=c99 -Wall -Wextra -I $(HOME)/local/include

TEST = test.out
CSRCTEST = $(TESTDIR)/main.c $(TESTDIR)/$(SRCDIR)/grilleTest.c $(TESTDIR)/$(SRCDIR)/couleurTest.c
CHDRTEST = $(TESTDIR)/$(HDIR)/grilleTest.h $(TESTDIR)/$(HDIR)/couleurTest.h
COBJTEST = $(TESTDIR)/$(OBJDIR)/main.o $(TESTDIR)/$(OBJDIR)/grilleTest.o $(TESTDIR)/$(OBJDIR)/couleurTest.o
CFLAGSTEST = -L $(HOME)/local/lib


app: $(APP)

$(APP): $(COBJMAIN) $(COBJ)
	$(CC) $(CFLAGS) -o $(APP) $(COBJMAIN) $(COBJ)

$(COBJMAIN): $(CSRC) $(CHDR) $(OBJDIR)
	$(CC) $(CFLAGS) -o $(OBJDIR)/main.o -c $(SRCDIR)/main.c

$(COBJ): $(CSRC) $(CHDR) $(OBJDIR)
	$(CC) $(CFLAGS) -o $(OBJDIR)/grille.o -c $(SRCDIR)/grille.c
	$(CC) $(CFLAGS) -o $(OBJDIR)/file.o -c $(SRCDIR)/file.c
	$(CC) $(CFLAGS) -o $(OBJDIR)/couleur.o -c $(SRCDIR)/couleur.c

$(OBJDIR):
	$(MKDIR) $(OBJDIR)


test: $(TEST)

$(TEST): $(COBJTEST) $(COBJ)
	$(CC) $(CFLAGSTEST) -o $(TEST) $(COBJTEST) $(COBJ) -lcunit

$(COBJTEST): $(CSRCTEST) $(CHDRTEST) $(TESTDIR)/$(OBJDIR)
	$(CC) $(CFLAGS) -o $(TESTDIR)/$(OBJDIR)/main.o -c $(TESTDIR)/main.c
	$(CC) $(CFLAGS) -o $(TESTDIR)/$(OBJDIR)/grilleTest.o -c $(TESTDIR)/$(SRCDIR)/grilleTest.c
	$(CC) $(CFLAGS) -o $(TESTDIR)/$(OBJDIR)/couleurTest.o -c $(TESTDIR)/$(SRCDIR)/couleurTest.c

$(TESTDIR)/$(OBJDIR):
	$(MKDIR) $(TESTDIR)/$(OBJDIR)

doc:
	doxygen .doxygen.conf
	cd docs/latex && make
	cp docs/latex/refman.pdf ./doc.pdf
	rm -dr docs

clean:
	rm -rf *.out docs doc.pdf $(OBJDIR) $(TESTDIR)/$(OBJDIR) $(APP) $(TEST)
