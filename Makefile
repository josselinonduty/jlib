# ------------ Directory structure ------------
BINDIR=bin
CC=gcc
DOCSDIR=docs
INCLUDEDIR=include
SRCDIR=src
TESTDIR=tests
# ------------ Library configuration ------------
LIB=libjlib
SHAREDOBJ=$(SRC:%.c=%.relative.o)
# ------------ Documentation configuration ------------
DOCS=doxygen
DOCSCONFIG=Doxyfile
# ------------ Debug configuration ------------
DEBUG=valgrind
DFLAGS=--leak-check=full --show-leak-kinds=all --track-origins=yes
# ------------ Build configuration ------------
SRC=$(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/**/*.c)
OBJ=$(SRC:%.c=%.o)
CFLAGS=-Wall -pedantic -std=c99 -I$(INCLUDEDIR)
LDFLAGS=-lm -lcunit -lncurses
# ------------ Test configuration ------------
TEST=$(BINDIR)/$(TESTDIR)/run
CFLAGSTEST=-Wall -pedantic -std=c99 -I$(INCLUDEDIR) -I$(TESTDIR)/$(INCLUDEDIR)
LDFLAGSTEST=$(LDFLAGS) $(BINDIR)/lib/$(LIB).a
SRCTEST=$(wildcard $(TESTDIR)/$(SRCDIR)/*.c) $(wildcard $(TESTDIR)/$(SRCDIR)/**/*.c)
OBJTEST=$(SRCTEST:%.c=%.o)

# ---------------------------------
#               Targets            
# ---------------------------------

all: build/static
.PHONY: all

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) -o $@ -c $< $(CFLAGS)

$(SRCDIR)/%/%.o: $(SRCDIR)/%/%.c
	@$(CC) -o $@ -c $< $(CFLAGS)

docs: $(DOCSDIR)
	mkdir -p $(DOCSDIR)
	$(DOCS) $(DOCSCONFIG)
.PHONY: docs

debug: $(EXEC)
	@$(DEBUG) -s $(DFLAGS) $(TEST) 2>&1 | tee $(BINDIR)/$(TESTDIR)/.valgrind.log
.PHONY: debug

debug/headless: $(EXEC)
	@$(DEBUG) -s $(DFLAGS) $(TEST) 2>&1 | tee $(BINDIR)/$(TESTDIR)/.valgrind.log | \
		grep -q "All heap blocks were freed -- no leaks are possible"; \
		if [ $$? -ne 0 ]; then \
			echo "Memory leaks detected!"; \
			exit 1; \
		fi;
.PHONY: debug/headless

build: build/static build/dynamic
.PHONY: build

build/static: $(BINDIR)/lib/$(LIB).a
.PHONY: build/static

$(BINDIR)/lib/$(LIB).a: $(OBJ)
	@mkdir -p $(BINDIR)/lib
	@ar -rcs $(BINDIR)/lib/$(LIB).a $(OBJ)

build/dynamic: $(BINDIR)/lib/$(LIB).so
.PHONY: build/dynamic

$(BINDIR)/lib/$(LIB).so: $(SHAREDOBJ)
	@mkdir -p $(BINDIR)/lib
	@$(CC) -shared -o $(BINDIR)/lib/$(LIB).so $(SHAREDOBJ) $(LDFLAGS)

$(SRCDIR)/%.relative.o: $(SRCDIR)/%.c
	@$(CC) -fPIC -o $@ -c $< $(CFLAGS)

$(SRCDIR)/%/%.relative.o: $(SRCDIR)/%/%.c
	@$(CC) -fPIC -o $@ -c $< $(CFLAGS)

tests: $(TEST)
	@./$(TEST)
.PHONY: tests

$(TEST): $(BINDIR)/lib/$(LIB).a  $(OBJTEST)
	@mkdir -p $(BINDIR)/$(TESTDIR)
	$(CC) -o $(TEST) $(OBJTEST) $(LDFLAGSTEST)

$(TESTDIR)/%.o: $(TESTDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGSTEST)

$(TESTDIR)/%/%.o: $(TESTDIR)/%/%.c
	$(CC) -o $@ -c $< $(CFLAGSTEST)

clean: clean/objects clean/lib clean/exec clean/docs clean/debug
.PHONY: clean

clean/objects:
	@rm -f ./$(SRCDIR)/*.o
	@rm -f ./$(SRCDIR)/**/*.o
	@rm -f ./$(TESTDIR)/$(SRCDIR)/*.o
	@rm -f ./$(TESTDIR)/$(SRCDIR)/**/*.o
.PHONY: clean/objects

clean/lib:
	@rm -f ./$(BINDIR)/lib/*.a
	@rm -f ./$(BINDIR)/lib/*.so
.PHONY: clean/lib

clean/exec:
	@rm -f ./$(TEST)
.PHONY: clean/exec

clean/docs:
	@rm -rf ./$(DOCSDIR)
.PHONY: clean/docs

clean/debug:
	@rm -f ./$(BINDIR)/.valgrind.log
.PHONY: clean/debug

install/debian:
	apt-get install libcunit1 libcunit1-doc libcunit1-dev libncurses6 libncursesw6 valgrind -y
.PHONY: install/debian

changelog:
	./changelog.sh > CHANGELOG.m
.PHONY: changelog