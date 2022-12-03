#include <stdio.h>
#include "stack.h"

int main(int argc, char *argv[])
{
    // create stack
    stack *s = stack_create();

    // add command line arguments to stack
    for (int i = 1; i < argc; i++) {
        stack_push(s, argv[i]);
    }

    // print stack size
    printf("stack size: '%lu'\n", stack_get_size(s));

    // print stack 'is empty'
    bool is_empty = stack_is_empty(s);
    char *is_empty_str = (is_empty) ? "true" : "false";
    printf("stack empty: '%s'\n", is_empty_str);

    // print stack's 'most recently added element' (ie top of stack)
    char *data = stack_top(s);
    printf("stack top: '%s'\n", data);
 
    // pop each element of stack and print it
    printf("[");
    while (!stack_is_empty(s)) {
        char *data = stack_pop(s);
        printf("%s", data);
        if (stack_get_size(s) >= 1) {
            printf(", ");
        }
    }
    printf("]\n");

    // free stack
    stack_delete(&s);

    return 0;
}
