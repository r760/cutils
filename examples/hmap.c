#include <stdio.h>
#include <string.h>
#include "hmap.h"

void hmap_print(hmap *h)
{
     printf("[");
     hmap_iter *d_iter = hmap_iter_create(h);
     while (hmap_iter_has_next(d_iter)) {
	  pair *curr_element = hmap_iter_next(d_iter);
	  printf("{'%s':'%s'}", (char *)curr_element->key, (char*)curr_element->value);
	  if (hmap_iter_has_next(d_iter)) {
	       printf(", ");
	  }
     }
     hmap_iter_delete(&d_iter);
     printf("]\n");
}

int main(int argc, char *argv[])
{
     // create hmap
     hmap *h = hmap_create(5, 0.75, &hmap_str_hash, &hmap_str_equals_key, &hmap_str_equals_value);

     // insert key value pairs from command line arguments into hmap
     for (int i = 1; i < argc-1; i+=2) {
	  hmap_insert_key_value(&h, argv[i], argv[i+1]);
     }

     // print hmap size
     printf("hmap size: '%lu'\n", hmap_get_size(h));

     // print hmap capacity
     printf("hmap capacity: '%lu'\n", hmap_get_capacity(h));

     // print hmap 'is empty'
     bool is_empty = hmap_is_empty(h);
     char *is_empty_str = (is_empty) ? "true" : "false";
     printf("hmap empty: '%s'\n", is_empty_str);

     // print hmap
     hmap_print(h);

     // replace value for key
     hmap_replace_value_for_key(h, "Alpha", "One");

     // print hmap
     hmap_print(h);

     // delete key value pair by key
     hmap_delete_key_value_by_key(h, "Alpha");

     // print hmap
     hmap_print(h);

     // free hmap
     hmap_delete(&h);

     return 0;
}
