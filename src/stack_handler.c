#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/log.h"
#include "../include/stack.h"

extern stack *g_s;

void stack_print()
{
     printf("[");
     stack_iter *d_iter = stack_iter_create(g_s);
     while (stack_iter_has_next(d_iter)) {
	  void *curr_element = stack_iter_next(d_iter);
	  printf("%s", (char *)curr_element);
	  if (stack_iter_has_next(d_iter)) {
	       printf(", ");
	  }
     }
     stack_iter_delete(&d_iter);
     printf("]\n");
}

bool stack_handler(char *command)
{
     LOG_ERROR(command != NULL, error, "command is NULL");

     char *function = strtok(NULL, " ");

     if (strcmp(function, "get_size") == 0) {
	  size_t size = stack_get_size(g_s); 
	  printf("%lu\n", size);
     } else if (strcmp(function, "is_empty") == 0) {
	  bool empty = stack_is_empty(g_s);
	  printf("%s\n", (empty) ? "true" : "false");
     } else if (strcmp(function, "top") == 0) {
	  char *str = stack_top(g_s);
	  printf("%s\n", str);
     } else if (strcmp(function, "push") == 0) {
	  char *arg = strtok(NULL, " ");
	  stack_push(g_s, strdup(arg));
	  stack_print();
     } else if (strcmp(function, "pop") == 0) {
	  char *str = stack_pop(g_s);
	  if (str) free(str);
	  stack_print();
     } else {
	  LOG_ERROR(1 == 2, error, "function '%s' is unrecognized", function);
     }

     return true;

error:
     return false;
}
