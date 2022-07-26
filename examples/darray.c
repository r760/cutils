#include <darray.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    // create darray
    darray *d = darray_create();

    // add command line arguments to the end of darray
    for (int i = 1; i < argc; i++) {
        darray_append_element(d, argv[i]);
    }

    // print darray size
    printf("darray size '%lu'\n", darray_get_size(d));

    // print darray 'is empty'
    bool is_empty = darray_is_empty(d);
    char *is_empty_str = (is_empty) ? "true" : "false";
    printf("darray empty '%s'\n", is_empty_str);

    // remove first element of darray and print it
    printf("[");
    while (!darray_is_empty(d)) {
        char *data = darray_delete_front(d); 
        printf("%s", data);
        if (darray_get_size(d) >= 1) {
            printf(", ");
        }
    }
    printf("]\n");

    // free darray
    darray_delete(&d);

    return 0;
}
