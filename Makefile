CC=gcc
CFLAGS=-Wall -g
DFLAGS=

INCLUDEDIR=include
SRCDIR=src
LIBDIR=lib
BINDIR=bin
TESTSDIR=tests

CFLAGS+=-I$(INCLUDEDIR)
CFLAGS+=-L$(LIBDIR)

help:	Makefile
	@sed -n 's/^##[ ]*/\n/p' $< | sed 's/: /:\n\t/g; 1d'

## all: compile everything
all:	$(BINDIR)/cli_tester

## lib: create lib dir
lib:
	mkdir $(LIBDIR)

## bin: create bin dir
bin:
	mkdir $(BINDIR)

## lib/%.o: compile object files
$(LIBDIR)/%.o:	$(SRCDIR)/%.c
	make lib > /dev/null
	$(CC) $(CFLAGS) $(DFLAGS) -c $^ -o $@

## lib/liblog.a: compile static library lib/liblog.a
$(LIBDIR)/liblog.a:	$(LIBDIR)/log.o
	ar rcs $@ $^

## lib/libdarray.a: compile static library lib/libdarray.a
$(LIBDIR)/libdarray.a:	$(LIBDIR)/log.o $(LIBDIR)/darray.o
	ar rcs $@ $^

## lib/libsllist.a: compile static library lib/libsllist.a
$(LIBDIR)/libsllist.a:	$(LIBDIR)/log.o $(LIBDIR)/sllist.o
	ar rcs $@ $^

## lib/libhmap.a: compile static library lib/libhmap.a
$(LIBDIR)/libhmap.a:	$(LIBDIR)/log.o $(LIBDIR)/darray.o $(LIBDIR)/hmap.o
	ar rcs $@ $^

## bin/cli_tester: compile bin/cli_tester
$(BINDIR)/cli_tester:	$(SRCDIR)/cli_tester.c $(SRCDIR)/*_handler.c $(SRCDIR)/darray.c $(SRCDIR)/sllist.c $(SRCDIR)/hmap.c $(LIBDIR)/liblog.a $(LIBDIR)/libdarray.a $(LIBDIR)/libsllist.a $(LIBDIR)/libhmap.a
	make bin > /dev/null
	$(CC) $(CFLAGS) $(DFLAGS) $(SRCDIR)/cli_tester.c $(SRCDIR)/*_handler.c -llog -ldarray -lsllist -lhmap -o $@

## run_cli_tester: run cli_tester
run_cli_tester:	$(BINDIR)/cli_tester
	./$<

## run_tests: run tests
run_tests:	$(BINDIR)/cli_tester
	cd $(TESTSDIR); ./run.sh

## run_valgrind_tests: run tests (and check for memory leaks)
run_valgrind_tests:    $(BINDIR)/cli_tester
	cd $(TESTSDIR); ./run.sh --check-memory-leaks

## install: install log, darray, sllist, stack, queue header-files and libraries
install:	$(LIBDIR)/liblog.a $(LIBDIR)/libdarray.a $(LIBDIR)/libsllist.a $(LIBDIR)/libhmap.a
	[ -d /usr/local/include ] || sudo mkdir -p /usr/local/include
	[ -d /usr/local/lib ] || sudo mkdir -p /usr/local/lib
	[ -d /usr/local/src ] || sudo mkdir -p /usr/local/src
	cd $(INCLUDEDIR); find . -type f -name "*.h" -exec sudo cp -v {} /usr/local/include/ \;
	cd $(LIBDIR); find . -type f -name "*.a" -exec sudo cp -v {} /usr/local/lib/ \;
	cd $(SRCDIR); find . -type f -name "*.c" -exec sudo cp -v {} /usr/local/src/ \;

## uninstall: uninstall log, darray, sllist, stack, queue header-files and libraries
uninstall:	$(LIBDIR)/liblog.a $(LIBDIR)/libdarray.a $(LIBDIR)/libsllist.a
	cd $(INCLUDEDIR); find . -type f -name "*.h" -exec sudo rm -v /usr/local/include/{} \;
	cd $(LIBDIR); find . -type f -name "*.a" -exec sudo rm -v /usr/local/lib/{} \;
	cd $(SRCDIR); find . -type f -name "*.c" -exec sudo rm -v /usr/local/src/{} \;

## clean: remove lib, and bin dirs (and everything inside)
clean:
	rm -rf $(LIBDIR) $(BINDIR) &> /dev/null || true
