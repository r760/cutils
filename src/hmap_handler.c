#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/log.h"
#include "../include/hmap.h"

extern hmap *g_h;

void hmap_print()
{
     printf("[");
     hmap_iter *d_iter = hmap_iter_create(g_h);
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

void hmap_print_buckets()
{
     printf("--- --- --- --- ---\n");
     for (size_t i = 0; i < g_h->capacity; i++) {
	  printf("%lu: {", i);
	  darray *d = g_h->data[i];
	  printf("[");
	  if (d != NULL) {
	       darray_iter *d_iter = darray_iter_create(d);
	       while (darray_iter_has_next(d_iter)) {
		    pair *p = (pair *) darray_iter_next(d_iter);
		    char *key = p->key, *value = p->value;
		    printf("{\"%s\":\"%s\"}", key, value);
		    if (darray_iter_has_next(d_iter)) {
			 printf(", ");
		    }
	       }
	       darray_iter_delete(&d_iter);
	  }
	  printf("]}\n");
     }
     printf("--- --- --- --- ---\n");
}

bool hmap_handler(char *command)
{
     LOG_ERROR(command != NULL, error, "command is NULL");

     char *function = strtok(NULL, " ");

     if (strcmp(function, "get_size") == 0) {
	  size_t size = hmap_get_size(g_h); 
	  printf("%lu\n", size);
     } else if (strcmp(function, "get_capacity") == 0) {
	  size_t capacity = hmap_get_capacity(g_h); 
	  printf("%lu\n", capacity);
     } else if (strcmp(function, "is_empty") == 0) {
	  bool empty = hmap_is_empty(g_h);
	  printf("%s\n", (empty) ? "true" : "false");
     } else if (strcmp(function, "get_load_factor") == 0) {
	  double lf = hmap_get_load_factor(g_h);
	  printf("%.2f\n", lf);
     } else if (strcmp(function, "insert_key_value") == 0) {
	  char *arg = strtok(NULL, " ");
	  char *key = strdup(arg);
	  arg = strtok(NULL, " ");
	  char *value = strdup(arg);
	  hmap_insert_key_value(&g_h, key, value);
	  // hmap_print();
     } else if (strcmp(function, "get_value_by_key") == 0) {
	  char *arg = strtok(NULL, " ");
	  char *key = arg;
	  char *value = hmap_get_value_by_key(g_h, key);
	  printf("%s\n", value);
     } else if (strcmp(function, "delete_key_value_by_key") == 0) {
	  char *arg = strtok(NULL, " ");
	  char *key = arg;
	  pair *p = hmap_delete_key_value_by_key(g_h, key);
	  key = p->key;
	  char *value = p->value;
	  printf("{'%s':'%s'}\n", key, value);
	  pair_delete(&p);
	  if (key) free(key);
	  if (value) free(value);
     } else if (strcmp(function, "replace_value_for_key") == 0) {
	  char *arg = strtok(NULL, " ");
	  char *key = arg;
	  arg = strtok(NULL, " ");
	  char *value = strdup(arg);
	  value = hmap_replace_value_for_key(g_h, key, value);
	  printf("%s\n", value);
	  if (value) free(value);
	  // hmap_print();
     } else if (strcmp(function, "contains_key") == 0) {
	  char *arg = strtok(NULL, " ");
	  char *key = arg;
	  bool contains = hmap_contains_key(g_h, key);
	  printf("%s\n", (contains) ? "true" : "false");
     } else if (strcmp(function, "contains_value") == 0) {
	  char *arg = strtok(NULL, " ");
	  char *value = arg;
	  bool contains = hmap_contains_value(g_h, value);
	  printf("%s\n", (contains) ? "true" : "false");
     } else if (strcmp(function, "print") == 0) {
	  hmap_print();
     } else if (strcmp(function, "print_buckets") == 0) {
	  hmap_print_buckets();
     } else {
	  LOG_ERROR(1 == 2, error, "function '%s' is unrecognized", function);
     }

     /*
       hmap_resize(hmap **h, size_t new_capacity);
     */

     return true;

error:
     return false;
}
