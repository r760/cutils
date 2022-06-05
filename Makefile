CC=gcc
CFLAGS=-Wall -g
DFLAGS=-DE_LOG_COLORS -DE_LOG_INFO -DE_LOG_DEBUG -DE_LOG_WARN -DE_LOG_ERROR

INCLUDEDIR=include
SRCDIR=src
LIBDIR=lib
BINDIR=bin
TESTSDIR=tests

CFLAGS+=-I$(INCLUDEDIR)
CFLAGS+=-L$(LIBDIR)

## all: compile everything
all:	$(BINDIR)/darray_cli $(LIBDIR)/liblog.so

## lib: create lib dir
lib:
	mkdir $(LIBDIR)

## bin: create bin dir
bin:
	mkdir $(BINDIR)

## lib/liblog.so: compile shared object lib/liblog.so
$(LIBDIR)/liblog.so:	$(SRCDIR)/log.c
	make lib > /dev/null
	$(CC) $(CFLAGS) $(DFLAGS) -fPIC -shared -lc $^ -o $@

## lib/libdarray.so: compile shared object lib/libdarray.so
$(LIBDIR)/libdarray.so:	$(SRCDIR)/log.c $(SRCDIR)/darray.c
	make lib > /dev/null
	$(CC) $(CFLAGS) $(DFLAGS) -fPIC -shared -lc $^ -o $@

## bin/darray_cli: compile bin/darray_cli
$(BINDIR)/darray_cli:	$(SRCDIR)/darray_cli.c $(LIBDIR)/libdarray.so
	make bin > /dev/null
	$(CC) $(CFLAGS) $(DFLAGS) $< -ldarray -o $@

## run_darray_cli: run darray_cli
run_darray_cli:	$(BINDIR)/darray_cli
	export LD_LIBRARY_PATH=$(shell pwd)/$(LIBDIR); ./$<

## run_tests: run tests
run_tests:	$(BINDIR)/darray_cli
	export LD_LIBRARY_PATH=$(shell pwd)/$(LIBDIR); cd $(TESTSDIR); ./run.sh

## run_valgrind_tests: run tests (and check for memory leaks)
run_valgrind_tests:	$(BINDIR)/darray_cli
	export LD_LIBRARY_PATH=$(shell pwd)/$(LIBDIR); cd $(TESTSDIR); ./run.sh --check-memory-leaks

## clean: remove binaries, object files, and shared object files, and empty lib and bin dirs
clean:
	rm -f $(LIBDIR)/*.o $(LIBDIR)/*.so $(BINDIR)/*
	rmdir $(LIBDIR) $(BINDIR) || true

help:	Makefile
	@sed -n 's/^##[ ]*/\n/p' $< | sed 's/: /:\n\t/g; 1d'
