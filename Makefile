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
all:	$(BINDIR)/darray_cli $(LIBDIR)/liblog.a

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

## lib/log.o: compile object lib/log.o
$(LIBDIR)/log.o:	$(LIBDIR)/log.o

## lib/darray.o: compile object lib/darray.o
$(LIBDIR)/darray.o:	$(LIBDIR)/darray.o

## lib/liblog.a: compile static library lib/liblog.a
$(LIBDIR)/liblog.a:	$(LIBDIR)/log.o
	ar rcs $@ $^

## lib/libdarray.a: compile static library lib/libdarray.a
$(LIBDIR)/libdarray.a:	$(LIBDIR)/log.o $(LIBDIR)/darray.o
	ar rcs $@ $^

## bin/darray_cli: compile bin/darray_cli
$(BINDIR)/darray_cli:	$(SRCDIR)/darray_cli.c $(LIBDIR)/libdarray.a
	make bin > /dev/null
	$(CC) $(CFLAGS) $(DFLAGS) $< -ldarray -o $@

## run_darray_cli: run darray_cli
run_darray_cli:	$(BINDIR)/darray_cli
	./$<

## run_tests: run tests
run_tests:	$(BINDIR)/darray_cli
	cd $(TESTSDIR); ./run.sh

## run_valgrind_tests: run tests (and check for memory leaks)
run_valgrind_tests:	$(BINDIR)/darray_cli
	cd $(TESTSDIR); ./run.sh --check-memory-leaks

## clean: remove binaries, object files, and shared object files, static libraries, and empty lib and bin dirs
clean:
	rm -f $(LIBDIR)/*.o $(LIBDIR)/*.so $(LIBDIR)/*.a $(BINDIR)/*
	rmdir $(LIBDIR) $(BINDIR) || true

help:	Makefile
	@sed -n 's/^##[ ]*/\n/p' $< | sed 's/: /:\n\t/g; 1d'
