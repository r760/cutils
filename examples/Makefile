CC=gcc
CFLAGS=-Wall -g
DFLAGS=

INCLUDEDIR=../include
LIBDIR=../lib

CFLAGS+=-I$(INCLUDEDIR)
CFLAGS+=-L$(LIBDIR)

help:	Makefile
	@sed -n 's/^##[ ]*/\n/p' $< | sed 's/: /:\n\t/g; 1d'

## all: compile everything
all:	darray list stack queue hmap log logic

## darray: compile darray
darray:	darray.c
	$(CC) $(CFLAGS) $< -ldarray -o $@

## list: compile list
list:	list.c
	$(CC) $(CFLAGS) $< -llist -o $@

## stack: compile stack
stack:	stack.c
	$(CC) $(CFLAGS) $< -llist -o $@

## queue: compile queue
queue:	queue.c
	$(CC) $(CFLAGS) $< -llist -o $@

## hmap: compile hmap
hmap:	hmap.c
	$(CC) $(CFLAGS) $< -lhmap -o $@

## log: compile log
log:	log.c
	$(CC) $(CFLAGS) $< -llog -o $@

## logic: compile logic
logic:	logic.c
	$(CC) $(CFLAGS) $< -o $@

## darray_example: an example of how to run darray
darray_example:	darray
	./darray Alpha Beta Charlie Delta Echo

## list_example: an example of how to run list
list_example:	list
	./list Alpha Beta Charlie Delta Echo

## stack_example: an example of how to run stack
stack_example:	stack
	./stack Alpha Beta Charlie Delta Echo

## queue_example: an example of how to run queue
queue_example:	queue
	./queue Alpha Beta Charlie Delta Echo

## hmap_example: an example of how to run hmap
hmap_example:	hmap
	./hmap Alpha 1 Beta 2 Charlie 3 Delta 4 Echo 5

## log_example: an example of how to run log
log_example:	log
	./log

## logic_example: an example of how to run logic
logic_example:	logic
	./logic

## example: run examples of darray, list, stack, queue, hmap, log, and logic
example:	darray_example list_example stack_example queue_example hmap_example log_example logic_example

## clean: remove binaries
clean:
	rm -vf darray list stack queue hmap log logic
