#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/log.h"
#include "../include/darray.h"
#include "../include/sllist.h"
#include "../include/stack.h"
#include "../include/queue.h"
#include "../include/hmap.h"
#define BUFF_SIZE 100

darray *g_d = NULL;
sllist *g_l = NULL;
stack *g_s = NULL;
queue *g_q = NULL;
hmap *g_h = NULL;

extern bool darray_handler(char *command);
extern bool sllist_handler(char *command);
extern bool stack_handler(char *command);
extern bool queue_handler(char *command);
extern bool hmap_handler(char *command);

static bool init()
{
     g_d = darray_create();
     LOG_ERROR(g_d != NULL, error, "failed to create darray");

     g_l = sllist_create();
     LOG_ERROR(g_l != NULL, error, "failed to create sllist");

     g_s = stack_create();
     LOG_ERROR(g_s != NULL, error, "failed to create stack");

     g_q = queue_create();
     LOG_ERROR(g_q != NULL, error, "failed to create queue");

     g_h = hmap_create(5, 0.75, &hmap_str_hash, &hmap_str_equals_key, &hmap_str_equals_value);
     LOG_ERROR(g_h != NULL, error, "failed to create hmap");

     return true;

error:
     return false;
}

static void eat_new_lines(char *str)
{
     size_t i = 0;
     while (str[i] != '\0') {
	  if (str[i] == '\n') {
	       str[i] = '\0';
	  }
	  i++;
     }
}

static bool cleanup()
{
     bool rv = true;
     rv = darray_delete(&g_d);
     LOG_ERROR(rv == true, error, "failed to free darray");

     rv = sllist_delete(&g_l);
     LOG_ERROR(rv == true, error, "failed to free sllist");

     rv = stack_delete(&g_s);
     LOG_ERROR(rv == true, error, "failed to free stack");

     rv = queue_delete(&g_q);
     LOG_ERROR(rv == true, error, "failed to free queue");

     rv = hmap_delete(&g_h);
     LOG_ERROR(rv == true, error, "failed to free hmap");

     return true;

error:
     return false;
}

int main(int argc, char *argv[])
{
     bool rv = init();
     LOG_ERROR(rv == true, error, "failed to initialize data structures");

     char buffer[BUFF_SIZE];
     while (fgets(buffer, BUFF_SIZE, stdin)) {
	  eat_new_lines(buffer);

	  char *command = strtok(buffer, " ");
	  LOG_ERROR(command != NULL, error, "failed to get next token from buffer '%s'", buffer);

	  if (strcmp(command, "exit") == 0) {
	       break;
	  } else if (strcmp(command, "darray") == 0) {
	       rv = darray_handler(command);
	  } else if (strcmp(command, "sllist") == 0) {
	       rv = sllist_handler(command);
	  } else if (strcmp(command, "stack") == 0) {
	       rv = stack_handler(command);
	  } else if (strcmp(command, "queue") == 0) {
	       rv = queue_handler(command);
	  } else if (strcmp(command, "hmap") == 0) {
	       rv = hmap_handler(command);
	  } else {
	       LOG_ERROR(1 == 2, error, "command '%s' is unrecognized", command);
	  }
     }

     rv = cleanup();
     LOG_ERROR(rv == true, error, "failed to cleanup");

     return 0;

error:
     return 1;
}
