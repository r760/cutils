#include <stdio.h>
#include "sllist.h"

int main(int argc, char *argv[])
{
    // create sllist
    sllist *l = sllist_create();

    // add command line arguments to the rear of sllist
    for (int i = 1; i < argc; i++) {
        sllist_append_element(l, argv[i]);
    }

    // print sllist size
    printf("sllist size: '%lu'\n", sllist_get_size(l));

    // print sllist 'is empty'
    bool is_empty = sllist_is_empty(l);
    char *is_empty_str = (is_empty) ? "true" : "false";
    printf("sllist empty: '%s'\n", is_empty_str);

    // print sllist's 'most anciently added element'
    char *data = sllist_get_front_data(l);
    printf("sllist most anciently added element: '%s'\n", data);

    // remove each element of sllist from the front and print it
    printf("[");
    while (!sllist_is_empty(l)) {
        char *data = sllist_delete_front(l);
        printf("%s", data);
        if (sllist_get_size(l) >= 1) {
            printf(", ");
        }
    }
    printf("]\n");

    // free sllist
    sllist_delete(&l);

    return 0;
}
