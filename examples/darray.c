#include <darray.h>
#include <stdio.h>
#include <string.h>

bool condition(void *element, void *other)
{
     char *str = element;
     return str[0] == 'A' || str[0] == 'B';
}

void darray_print(darray *d)
{
     printf("[");
     DARRAY_FOREACH(i, d) {
	  char *data = darray_get_element_at_index(d, i);
	  printf("%s", data);
	  if (i < darray_get_size(d) - 1) {
	       printf(", ");
	  }

     }
     printf("]\n");
}

int main(int argc, char *argv[])
{
     // create darray
     darray *d = darray_create();

     // add command line arguments to the end of darray
     for (int i = 1; i < argc; i++) {
	  darray_append_element(d, argv[i]);
     }

     // print darray size
     printf("darray size: '%lu'\n", darray_get_size(d));

     // print darray capacity
     printf("darray capacity: '%lu'\n", darray_get_capacity(d));

     // print darray 'is empty'
     bool is_empty = darray_is_empty(d);
     char *is_empty_str = (is_empty) ? "true" : "false";
     printf("darray empty: '%s'\n", is_empty_str);

     // print darray
     darray_print(d);

     // remove all elements (which are C strings) of darray which start with 'A' or 'B'
     darray *sub_array = darray_delete_elements(d, NULL, &condition);

     // print (sub) darray
     printf("removing -> ");
     darray_print(sub_array);

     // print darray
     darray_print(d);

     // free (sub) darray
     darray_delete(&sub_array);

     // free darray
     darray_delete(&d);

     return 0;
}
