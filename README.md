# cutils
utilities for the C programming language

- to view the documentation go to [https://r760.github.io/cutils/](https://r760.github.io/cutils/)

## data structures
- dynamic array
- single linked list
- stack
- queue

note:
- logging tools are used to do error checking, and by default log colors are enabled...
log colors can be turned off by defining `N_LOG_COLORS`

## logging (and error checking/handling) tools
- log info macro
- log debug macros
- log warning macros
- log error macros

note:
- log colors can be turned off by defining `N_LOG_COLORS`
- log info macros can be turned off by defining `N_LOG_INFO`
- log debug macros can be turned off by defining `N_LOG_DEBUG`
- log warning macros can be turned off by defining `N_LOG_WARN`
- log error macros can be turned off by defining `N_LOG_ERROR`

for example, consider the following program (example.c)
```
#include <log.h>

int main(int argc, char *argv[])
{
    LOG_INFO("argc: '%d'", argc);

    for (int i = 1; i < argc; i++) {
        LOG_DEBUG("argv[%d]: '%s'", i, argv[i]);
    }

    printf("hello, world!\n");

    return 0;
}
```
which can be compiled using different define directives inorder to toggle log off select log features;

Version 1:
```
{/tmp} >>> gcc -Wall -g example.c -llog -o example
{/tmp} >>> ./example 1 2 3
Sat Aug 21 00:00:00 2022 INFO  (example.c:5) main()  --> argc: '4'
Sat Aug 21 00:00:00 2022 DEBUG (example.c:8) main()  --> argv[1]: '1'
Sat Aug 21 00:00:00 2022 DEBUG (example.c:8) main()  --> argv[2]: '2'
Sat Aug 21 00:00:00 2022 DEBUG (example.c:8) main()  --> argv[3]: '3'
hello, world!
```
Version 2:
```
{/tmp} >>> gcc -Wall -g -DN_LOG_INFO example.c -llog -o example
{/tmp} >>> {/tmp} >>> ./example 1 2 3
Sat Aug 21 00:01:00 2022 DEBUG (example.c:8) main()  --> argv[1]: '1'
Sat Aug 21 00:01:00 2022 DEBUG (example.c:8) main()  --> argv[2]: '2'
Sat Aug 21 00:01:00 2022 DEBUG (example.c:8) main()  --> argv[3]: '3'
hello, world!
```
Version 3:
```
{/tmp} >>> gcc -Wall -g -DN_LOG_INFO -DN_LOG_DEBUG example.c -llog -o example
{/tmp} >>> ./example 1 2 3
hello, world!
```

## other
- logic operator macros

## how to view all Makefile directives ?
```
make help
```

## how to compile ?
- with log colors
```
make all
```
- without log colors
```
make DFLAGS=-DN_LOG_COLORS all
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
