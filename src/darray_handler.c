#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/log.h"
#include "../include/darray.h"

extern darray *g_d;

void darray_print()
{
     printf("[");
     darray_iter *d_iter = darray_iter_create(g_d);
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

static bool condition(void *element, void *other)
{
     LOG_ERROR(element != NULL, error, "element is NULL");
     LOG_ERROR(other != NULL, error, "other is NULL");

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
error:
     return false;
}

bool darray_handler(char *command)
{
     LOG_ERROR(command != NULL, error, "command is NULL");

     char *function = strtok(NULL, " ");

     if (strcmp(function, "get_size") == 0) {
	  size_t size = darray_get_size(g_d); 
	  printf("%lu\n", size);
     } else if (strcmp(function, "get_capacity") == 0) {
	  size_t capacity = darray_get_capacity(g_d); 
	  printf("%lu\n", capacity);
     } else if (strcmp(function, "is_empty") == 0) {
	  bool empty = darray_is_empty(g_d);
	  printf("%s\n", (empty) ? "true" : "false");
     } else if (strcmp(function, "prepend_element") == 0) {
	  char *arg = strtok(NULL, " ");
	  darray_prepend_element(g_d, strdup(arg));
	  darray_print();
     } else if (strcmp(function, "append_element") == 0) {
	  char *arg = strtok(NULL, " ");
	  darray_append_element(g_d, strdup(arg));
	  darray_print();
     } else if (strcmp(function, "delete_front") == 0) {
	  char *str = darray_delete_front(g_d);
	  if (str) free(str);
	  darray_print();
     } else if (strcmp(function, "delete_rear") == 0) {
	  char *str = darray_delete_rear(g_d);
	  if (str) free(str);
	  darray_print();
     } else if (strcmp(function, "insert_element_at_index") == 0) {
	  char *arg = strtok(NULL, " ");
	  char *str = strdup(arg);
	  arg = strtok(NULL, " ");
	  size_t index = atoi(arg);
	  darray_insert_element_at_index(g_d, str, index);
	  darray_print();
     } else if (strcmp(function, "delete_element_at_index") == 0) {
	  char *arg = strtok(NULL, " ");
	  size_t index = atoi(arg);
	  char *str = darray_delete_element_at_index(g_d, index);
	  if (str) free(str);
	  darray_print();
     } else if (strcmp(function, "get_element_at_index") == 0) {
	  char *arg = strtok(NULL, " ");
	  size_t index = atoi(arg);
	  char *str = darray_get_element_at_index(g_d, index);
	  printf("%s\n", str);
     } else if (strcmp(function, "set_element_at_index") == 0) {
	  char *arg = strtok(NULL, " ");
	  char *str = strdup(arg);
	  arg = strtok(NULL, " ");
	  size_t index = atoi(arg);

	  char *old_str = darray_get_element_at_index(g_d, index);
	  darray_set_element_at_index(g_d, str, index);
	  if (old_str) free(old_str);
	  darray_print();
     } else if (strcmp(function, "count_elements") == 0) {
	  char *arg = strtok(NULL, " ");
	  // arg should take the form of str0|str1|str2
	  size_t count = darray_count_elements(g_d, arg, &condition, false);
	  printf("%lu\n", count);
     } else if (strcmp(function, "get_elements") == 0) {
	  char *arg = strtok(NULL, " ");
	  // arg should take the form of str0|str1|str2
	  darray *d = darray_get_elements(g_d, arg, &condition);
	  printf("[");
	  while (d != NULL && !darray_is_empty(d)) {
	       char *element = darray_delete_front(d);
	       printf("%s", element);
	       if (darray_get_size(d) >= 1) {
		    printf(", ");
	       }
	  }
	  printf("]\n");
	  darray_delete(&d);
     } else if (strcmp(function, "delete_elements") == 0) {
	  char *arg = strtok(NULL, " ");
	  // arg should take the form of str0|str1|str2
	  darray *d = darray_delete_elements(g_d, arg, &condition);
	  darray_print();
	  printf("[");
	  while (d != NULL && !darray_is_empty(d)) {
	       char *element = darray_delete_front(d);
	       printf("%s", element);
	       if (darray_get_size(d) >= 1) {
		    printf(", ");
	       }
	       free(element);
	  }
	  printf("]\n");
	  darray_delete(&d);
     } else if (strcmp(function, "reverse") == 0) {
	  darray_reverse(g_d);
	  darray_print();
     } else {
	  LOG_ERROR(1 == 2, error, "function '%s' is unrecognized", function);
     }

     return true;

error:
     return false;
}
