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
all:	$(BINDIR)/darray_cli $(BINDIR)/sllist_cli $(BINDIR)/stack_cli $(BINDIR)/queue_cli

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

## bin/darray_cli: compile bin/darray_cli
$(BINDIR)/darray_cli:	$(SRCDIR)/darray_cli.c $(LIBDIR)/liblog.a $(LIBDIR)/libdarray.a
	make bin > /dev/null
	$(CC) $(CFLAGS) $(DFLAGS) $< -llog -ldarray -o $@

## bin/sllist_cli: compile bin/sllist_cli
$(BINDIR)/sllist_cli:	$(SRCDIR)/sllist_cli.c $(LIBDIR)/liblog.a $(LIBDIR)/libsllist.a
	make bin > /dev/null
	$(CC) $(CFLAGS) $(DFLAGS) $< -llog -lsllist -o $@

## bin/stack_cli: compile bin/stack_cli
$(BINDIR)/stack_cli:	$(SRCDIR)/stack_cli.c $(LIBDIR)/liblog.a $(LIBDIR)/libsllist.a
	make bin > /dev/null
	$(CC) $(CFLAGS) $(DFLAGS) $< -llog -lsllist -o $@

## bin/queue_cli: compile bin/queue_cli
$(BINDIR)/queue_cli:	$(SRCDIR)/queue_cli.c $(LIBDIR)/liblog.a $(LIBDIR)/libsllist.a
	make bin > /dev/null
	$(CC) $(CFLAGS) $(DFLAGS) $< -llog -lsllist -o $@

## run_darray_cli: run darray_cli
run_darray_cli:	$(BINDIR)/darray_cli
	./$<

## run_sllist_cli: run sllist_cli
run_sllist_cli:	$(BINDIR)/sllist_cli
	./$<

## run_stack_cli: run stack_cli
run_stack_cli:	$(BINDIR)/stack_cli
	./$<

## run_queue_cli: run queue_cli
run_queue_cli:	$(BINDIR)/queue_cli
	./$<

## run_tests: run tests
run_tests:	$(BINDIR)/darray_cli $(BINDIR)/sllist_cli $(BINDIR)/stack_cli $(BINDIR)/queue_cli
	cd $(TESTSDIR); ./run.sh

## run_valgrind_tests: run tests (and check for memory leaks)
run_valgrind_tests:	$(BINDIR)/darray_cli $(BINDIR)/sllist_cli $(BINDIR)/stack_cli $(BINDIR)/queue_cli
	cd $(TESTSDIR); ./run.sh --check-memory-leaks

## install: install log, darray, sllist, stack, queue header-files and libraries
install:	$(LIBDIR)/liblog.a $(LIBDIR)/libdarray.a $(LIBDIR)/libsllist.a
	[ -d /usr/local/include ] || sudo mkdir -p /usr/local/include
	[ -d /usr/local/lib ] || sudo mkdir -p /usr/local/lib
	cd $(INCLUDEDIR); find . -type f -name "*.h" -exec sudo cp -v {} /usr/local/include/ \;
	cd $(LIBDIR); find . -type f -name "*.a" -exec sudo cp -v {} /usr/local/lib/ \;

## uninstall: uninstall log, darray, sllist, stack, queue header-files and libraries
uninstall:	$(LIBDIR)/liblog.a $(LIBDIR)/libdarray.a $(LIBDIR)/libsllist.a
	cd $(INCLUDEDIR); find . -type f -name "*.h" -exec sudo rm -v /usr/local/include/{} \;
	cd $(LIBDIR); find . -type f -name "*.a" -exec sudo rm -v /usr/local/lib/{} \;

## clean: remove binaries, object files, and shared object files, static libraries, and empty lib and bin dirs
clean:
	rm -f $(LIBDIR)/*.o $(LIBDIR)/*.so $(LIBDIR)/*.a $(BINDIR)/*
	rmdir $(LIBDIR) $(BINDIR) &> /dev/null || true
