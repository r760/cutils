#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/log.h"
#include "../include/queue.h"

extern queue *g_q;

void queue_print()
{
     printf("[");
     queue_iter *d_iter = queue_iter_create(g_q);
     while (queue_iter_has_next(d_iter)) {
	  void *curr_element = queue_iter_next(d_iter);
	  printf("%s", (char *)curr_element);
	  if (queue_iter_has_next(d_iter)) {
	       printf(", ");
	  }
     }
     queue_iter_delete(&d_iter);
     printf("]\n");
}

bool queue_handler(char *command)
{
     LOG_ERROR(command != NULL, error, "command is NULL");

     char *function = strtok(NULL, " ");

     if (strcmp(function, "get_size") == 0) {
	  size_t size = queue_get_size(g_q); 
	  printf("%lu\n", size);
     } else if (strcmp(function, "is_empty") == 0) {
	  bool empty = queue_is_empty(g_q);
	  printf("%s\n", (empty) ? "true" : "false");
     } else if (strcmp(function, "peek") == 0) {
	  char *str = queue_peek(g_q);
	  printf("%s\n", str);
     } else if (strcmp(function, "enqueue") == 0) {
	  char *arg = strtok(NULL, " ");
	  queue_enqueue(g_q, strdup(arg));
	  queue_print();
     } else if (strcmp(function, "dequeue") == 0) {
	  char *str = queue_dequeue(g_q);
	  if (str) free(str);
	  queue_print();
     } else {
	  LOG_ERROR(1 == 2, error, "function '%s' is unrecognized", function);
     }

     return true;

error:
     return false;
}
