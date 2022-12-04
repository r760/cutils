#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/log.h"
#include "../include/list.h"

extern list *g_l;

void list_print()
{
     printf("[");
     list_iter *d_iter = list_iter_create(g_l);
     while (list_iter_has_next(d_iter)) {
	  void *curr_element = list_iter_next(d_iter);
	  printf("%s", (char *)curr_element);
	  if (list_iter_has_next(d_iter)) {
	       printf(", ");
	  }
     }
     list_iter_delete(&d_iter);
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

bool list_handler(char *command)
{
     LOG_ERROR(command != NULL, error, "command is NULL");

     char *function = strtok(NULL, " ");

     if (strcmp(function, "get_size") == 0) {
	  size_t size = list_get_size(g_l); 
	  printf("%lu\n", size);
     } else if (strcmp(function, "is_empty") == 0) {
	  bool empty = list_is_empty(g_l);
	  printf("%s\n", (empty) ? "true" : "false");
     } else if (strcmp(function, "get_front_data") == 0) {
	  char *str = list_get_front_data(g_l);
	  printf("%s\n", str);
     } else if (strcmp(function, "get_rear_data") == 0) {
	  char *str = list_get_rear_data(g_l);
	  printf("%s\n", str);
     } else if (strcmp(function, "prepend_element") == 0) {
	  char *arg = strtok(NULL, " ");
	  list_prepend_element(g_l, strdup(arg));
	  list_print();
     } else if (strcmp(function, "append_element") == 0) {
	  char *arg = strtok(NULL, " ");
	  list_append_element(g_l, strdup(arg));
	  list_print();
     } else if (strcmp(function, "delete_front") == 0) {
	  char *str = list_delete_front(g_l);
	  if (str) free(str);
	  list_print();
     } else if (strcmp(function, "delete_rear") == 0) {
	  char *str = list_delete_rear(g_l);
	  if (str) free(str);
	  list_print();
     } else if (strcmp(function, "count_elements") == 0) {
	  char *arg = strtok(NULL, " ");
	  // arg should take the form of str0|str1|str2
	  size_t count = list_count_elements(g_l, arg, &condition);
	  printf("%lu\n", count);
     } else if (strcmp(function, "get_elements") == 0) {
	  char *arg = strtok(NULL, " ");
	  // arg should take the form of str0|str1|str2
	  list *l = list_get_elements(g_l, arg, &condition);
	  printf("[");
	  while (l != NULL && !list_is_empty(l)) {
	       char *element = list_delete_front(l);
	       printf("%s", element);
	       if (list_get_size(l) >= 1) {
		    printf(", ");
	       }
	  }
	  printf("]\n");
	  list_delete(&l);
     } else if (strcmp(function, "delete_elements") == 0) {
	  char *arg = strtok(NULL, " ");
	  // arg should take the form of str0|str1|str2
	  list *l = list_delete_elements(g_l, arg, &condition);
	  list_print();
	  printf("[");
	  while (l != NULL && !list_is_empty(l)) {
	       char *element = list_delete_front(l);
	       printf("%s", element);
	       if (list_get_size(l) >= 1) {
		    printf(", ");
	       }
	       free(element);
	  }
	  printf("]\n");
	  list_delete(&l);
     } else {
	  LOG_ERROR(1 == 2, error, "function '%s' is unrecognized", function);
     }

     return true;

error:
     return false;
}
