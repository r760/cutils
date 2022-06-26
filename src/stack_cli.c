#include <stdlib.h>
#include <stdio.h>
#include "../include/log.h"
#include "../include/stack.h"
#define BUFF_SIZE 100

void stack_print(stack *s)
{
    void *data = NULL;

    printf("[");
    STACK_FOR_EACH(curr, s) {
        data = curr->data;
        printf("%d", *(int*)data);
        if (curr->next != NULL) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(int argc, char *argv[])
{
    char buffer[BUFF_SIZE];

    stack *s = stack_create();

    while (fgets(buffer, BUFF_SIZE, stdin)) {
        size_t i = 0;
        while (buffer[i] != '\0') {
            if (buffer[i] == '\n') {
                buffer[i] = '\0';
            }
            i++;
        }

        // LOG_DEBUG("%s", buffer);

        char *command = strtok(buffer, " ");

        if (strcmp(command, "exit") == 0) {
            // exit cli
            break;
        } else if (strcmp(command, "pu") == 0) {
            // push
            char *arg = strtok(NULL, " ");
            int *j = malloc(sizeof(int));
            *j = atoi(arg);
            stack_push(s, j);
            stack_print(s);
        } else if (strcmp(command, "po") == 0) {
            // pop
            int *j = stack_pop(s);
            if (j != NULL) {
                free(j);
            }
            stack_print(s);
        } else if (strcmp(command, "to") == 0) {
            // top
            int *j = stack_top(s);
            if (j != NULL) {
                printf("%d\n", *j);
            }
        } else if (strcmp(command, "gs") == 0) {
            // get size
            printf("%lu\n", stack_get_size(s));
        } else if (strcmp(command, "print") == 0) {
            // print stack
            stack_print(s);
        } else if (strcmp(command, "clear") == 0) {
            // clear screen
            system("clear");
        }
    }

    stack_delete(&s);
    LOG_ERROR(s == NULL, error, "failed to cleanup stack");
    return 0;

error:
    return 1;
}
