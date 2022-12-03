#include <stdio.h>
#include <string.h>
#include "darray.h"

void darray_print(darray *d)
{
     printf("[");
     darray_iter *d_iter = darray_iter_create(d);
     while (darray_iter_has_next(d_iter)) {
	  void *curr_element = darray_iter_next(d_iter);
	  printf("%s", (char *)curr_element);
	  if (darray_iter_has_next(d_iter)) {
	       printf(", ");
	       
	  }
     }
     darray_iter_delete(&d_iter);
     printf("]\n");
}

bool condition(void *element, void *other)
{
     char *str = strdup(other);
     char *match = strtok(str, "|");
     while (match != NULL) {
	  if (strcmp((char*) element, match) == 0) {
	       free(str);
	       return true;
	  }
	  match = strtok(NULL, "|");
     }

     free(str);
     return false;
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

     // remove all elements (which are C strings) of darray which are Alpha or Beta
     darray *sub_array = darray_delete_elements(d, "Alpha|Beta", &condition);

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
