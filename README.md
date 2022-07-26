# cutils
utilities for the C programming language

## data structures
- dynamic array
- single linked list
- stack
- queue

## logging tools
- log info macro
- log debug macros
- log warning macros
- log error macros

## other
- logic operator macros

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
