CC=gcc
CFLAGS=-Wall -g

help:	Makefile
	@sed -n 's/^##[ ]*/\n/p' $< | sed 's/: /:\n\t/g; 1d'

## all: compile everything
all:	darray sllist stack queue log logic

## darray: compile darray
darray:	darray.c
	$(CC) $(CFLAGS) $< -ldarray -o $@

## sllist: compile sllist
sllist:	sllist.c
	$(CC) $(CFLAGS) $< -lsllist -o $@

## stack: compile stack
stack:	stack.c
	$(CC) $(CFLAGS) $< -lsllist -o $@

## queue: compile queue
queue:	queue.c
	$(CC) $(CFLAGS) $< -lsllist -o $@

## log: compile log
log:	log.c
	$(CC) $(CFLAGS) $< -llog -o $@

## logic: compile logic
logic:	logic.c
	$(CC) $(CFLAGS) $< -o $@

## darray_example: an example of how to run darray
darray_example:	darray
	./darray Alpha Beta Charlie Delta Echo

## sllist_example: an example of how to run sllist
sllist_example:	sllist
	./sllist Alpha Beta Charlie Delta Echo

## stack_example: an example of how to run stack
stack_example:	stack
	./stack Alpha Beta Charlie Delta Echo

## queue_example: an example of how to run queue
queue_example:	queue
	./queue Alpha Beta Charlie Delta Echo

## log_example: an example of how to run log
log_example:	log
	./log

## logic_example: an example of how to run logic
logic_example:	logic
	./logic

## example: run examples of darray, sllist, stack, queue, log, and logic
example:	darray_example sllist_example stack_example queue_example log_example logic_example

## clean: remove binaries
clean:
	rm -vf darray sllist stack queue log logic
