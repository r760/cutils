# cutils
utilities for the C programming language

## data structures
- dynamic array [view docs](file:///home/richard/Github/cutils/docs/html/darray_8h.html)
- single linked list [view docs](file:///home/richard/Github/cutils/docs/html/sllist_8h.html)
- stack [view docs](file:///home/richard/Github/cutils/docs/html/stack_8h.html)
- queue [view docs](file:///home/richard/Github/cutils/docs/html/queue_8h.html)

## logging tools
- log info macro [view docs](file:///home/richard/Github/cutils/docs/html/log_8h.html)
- log debug macros [view docs](file:///home/richard/Github/cutils/docs/html/log_8h.html)
- log warning macros [view docs](file:///home/richard/Github/cutils/docs/html/log_8h.html)
- log error macros [view docs](file:///home/richard/Github/cutils/docs/html/log_8h.html)

## other
- logic operator macros [view docs](file:///home/richard/Github/cutils/docs/html/logic_8h.html)

## how to view all Makefile directives ?
```
make help
```

## how to compile ?
```
make all
```

## how to install ?
```
make install
```

## how to uninstall ?
```
make uninstall
```

## how to use; data structures, logging tools, and logic operators
- take a look inside the `cutils/examples` directory: it contains examples of how to use;
darray, sllist, stack, queue data structures, logging tools, and logic operators ... it also shows
which header files are needed to be included in the source files (.c files), and how to compile
everything in the Makefile... to view all Makefile directives you can use
```
make help
```

note:
- inorder to be able to compile all the examples inside the `cutils/examples` directory, you must first install all cutils tools
- the examples mentioned above do not show how to use every function... for an exhaustive description
of every function view the docs
