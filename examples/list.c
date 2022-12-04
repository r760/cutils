#include <stdio.h>
#include "list.h"

int main(int argc, char *argv[])
{
    // create list
    list *l = list_create();

    // add command line arguments to the rear of list
    for (int i = 1; i < argc; i++) {
        list_append_element(l, argv[i]);
    }

    // print list size
    printf("list size: '%lu'\n", list_get_size(l));

    // print list 'is empty'
    bool is_empty = list_is_empty(l);
    char *is_empty_str = (is_empty) ? "true" : "false";
    printf("list empty: '%s'\n", is_empty_str);

    // print list's 'most anciently added element'
    char *data = list_get_front_data(l);
    printf("list most anciently added element: '%s'\n", data);

    // remove each element of list from the front and print it
    printf("[");
    while (!list_is_empty(l)) {
        char *data = list_delete_front(l);
        printf("%s", data);
        if (list_get_size(l) >= 1) {
            printf(", ");
        }
    }
    printf("]\n");

    // free list
    list_delete(&l);

    return 0;
}
