SRCDIR=src
BINDIR=bin
INCLUDEDIR=include
DOCSDIR=docs
CC=gcc
CFLAGS=-Wall -pedantic -std=c99 -I$(INCLUDEDIR)
LDFLAGS=-lm -lcunit
EXEC=$(BINDIR)/test

DOCS=doxygen
DOCSCONFIG=Doxyfile
DEBUG=valgrind
DFLAGS=--leak-check=full --show-leak-kinds=all --track-origins=yes

SRC=$(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/**/*.c)
OBJ=$(SRC:%.c=%.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	@$(CC) -o $@ $(OBJ) $(LDFLAGS)

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) -o $@ -c $< $(CFLAGS)

$(SRCDIR)/%/%.o: $(SRCDIR)/%/%.c
	@$(CC) -o $@ -c $< $(CFLAGS)

docs: $(DOCSDIR)
	mkdir -p $(DOCSDIR)
	$(DOCS) $(DOCSCONFIG)*

debug: $(EXEC)
	$(DEBUG) $(EXEC) $(DFLAGS)

clean:
	@rm -f ./$(BINDIR)/*
	@rm -f ./$(SRCDIR)/*.o
	@rm -f ./$(SRCDIR)/**/*.o
	@rm -f ./$(EXEC)
	@rm -rf ./$(DOCSDIR)