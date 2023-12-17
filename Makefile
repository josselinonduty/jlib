SRCDIR=src
BINDIR=bin
INCLUDEDIR=include
DOCSDIR=docs
CC=gcc
CFLAGS=-Wall -pedantic -std=c99 -I$(INCLUDEDIR)
LDFLAGS=-lm -lcunit
EXEC=$(BINDIR)/tests
LIB=libjlib

DOCS=doxygen
DOCSCONFIG=Doxyfile
DEBUG=valgrind
DFLAGS=--leak-check=full --show-leak-kinds=all --track-origins=yes

SRC=$(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/**/*.c)
OBJ=$(SRC:%.c=%.o)
SHAREDOBJ=$(SRC:%.c=%.relative.o)

all: bin

bin: $(EXEC)

$(EXEC): $(OBJ)
	@mkdir -p $(BINDIR)
	@$(CC) -o $@ $(OBJ) $(LDFLAGS)

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) -o $@ -c $< $(CFLAGS)

$(SRCDIR)/%/%.o: $(SRCDIR)/%/%.c
	@$(CC) -o $@ -c $< $(CFLAGS)

docs: $(DOCSDIR)
	mkdir -p $(DOCSDIR)
	$(DOCS) $(DOCSCONFIG)

debug: $(EXEC)
	$(DEBUG) $(EXEC) $(DFLAGS)

build: build/static build/dynamic

build/static: $(BINDIR)/lib/$(LIB).a

$(BINDIR)/lib/$(LIB).a: $(OBJ)
	@mkdir -p $(BINDIR)/lib
	@ar -rcs $(BINDIR)/lib/$(LIB).a $(OBJ)

build/dynamic: $(BINDIR)/lib/$(LIB).so

$(BINDIR)/lib/$(LIB).so: $(SHAREDOBJ)
	@mkdir -p $(BINDIR)/lib
	@$(CC) -shared -o $(BINDIR)/lib/$(LIB).so $(SHAREDOBJ) $(LDFLAGS)

$(SRCDIR)/%.relative.o: $(SRCDIR)/%.c
	@$(CC) -fPIC -o $@ -c $< $(CFLAGS)

$(SRCDIR)/%/%.relative.o: $(SRCDIR)/%/%.c
	@$(CC) -fPIC -o $@ -c $< $(CFLAGS)

run: $(EXEC)
	@./$(EXEC) compress ./examples/source.txt

clean: clean/objects clean/exec clean/docs

clean/objects:
	@rm -f ./$(SRCDIR)/*.o
	@rm -f ./$(SRCDIR)/**/*.o

clean/exec:
	@rm -f ./$(EXEC)

clean/docs:
	@rm -rf ./$(DOCSDIR)

install/debian:
	apt-get install libcunit1 libcunit1-doc libcunit1-dev