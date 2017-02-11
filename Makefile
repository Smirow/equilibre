# ABOU ALI Magued, Février 2017

CC = gcc
SRCDIR = src
HDIR = headers
OBJDIR = obj
TESTDIR = test
MKDIR = mkdir -p

APP = equilibre.out
CSRC = $(SRCDIR)/main.c $(SRCDIR)/grille.c $(SRCDIR)/file.c
CHDR = $(HDIR)/grille.h $(HDIR)/file.h
COBJMAIN = $(OBJDIR)/main.o
COBJ = $(OBJDIR)/grille.o $(OBJDIR)/file.o
CFLAGS = -std=c99 -Wall -Wextra -I $(HOME)/local/include

TEST = test.out
CSRCTEST = $(TESTDIR)/main.c $(TESTDIR)/$(SRCDIR)/grilleTest.c
CHDRTEST = $(TESTDIR)/$(HDIR)/grilleTest.h
COBJTEST = $(TESTDIR)/$(OBJDIR)/main.o $(TESTDIR)/$(OBJDIR)/grilleTest.o
CFLAGSTEST = -L $(HOME)/local/lib -lcunit


app: $(APP)

$(APP): $(COBJMAIN) $(COBJ)
	$(CC) $(CFLAGS) -o $(APP) $(COBJMAIN) $(COBJ)

$(COBJMAIN): $(CSRC) $(CHDR) $(OBJDIR)
	$(CC) $(CFLAGS) -o $(OBJDIR)/main.o -c $(SRCDIR)/main.c

$(COBJ): $(CSRC) $(CHDR) $(OBJDIR)
	$(CC) $(CFLAGS) -o $(OBJDIR)/grille.o -c $(SRCDIR)/grille.c
	$(CC) $(CFLAGS) -o $(OBJDIR)/file.o -c $(SRCDIR)/file.c

$(OBJDIR):
	$(MKDIR) $(OBJDIR)


test: $(TEST)

$(TEST): $(COBJTEST) $(COBJ)
	$(CC) $(CFLAGSTEST) -o $(TEST) $(COBJTEST) $(COBJ)

$(COBJTEST): $(CSRCTEST) $(CHDRTEST) $(TESTDIR)/$(OBJDIR)
	$(CC) $(CFLAGS) -o $(TESTDIR)/$(OBJDIR)/main.o -c $(TESTDIR)/main.c
	$(CC) $(CFLAGS) -o $(TESTDIR)/$(OBJDIR)/grilleTest.o -c $(TESTDIR)/$(SRCDIR)/grilleTest.c

$(TESTDIR)/$(OBJDIR):
	$(MKDIR) $(TESTDIR)/$(OBJDIR)


clean:
	rm -rf *.out $(OBJDIR) $(TESTDIR)/$(OBJDIR) $(APP) $(TEST)
