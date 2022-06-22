#include <stdlib.h>
#include <stdio.h>
#include "../include/log.h"
#include "../include/sllist.h"
#define BUFF_SIZE 100

void sllist_print(sllist *l)
{
    void *data = NULL;

    printf("[");
    SLLIST_FOR_EACH(curr, l) {
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

    sllist *l = sllist_create();

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
        } else if (strcmp(command, "ar") == 0) { // append rear
            char *arg = strtok(NULL, " ");
            int *j = malloc(sizeof(int));
            *j = atoi(arg);
            sllist_append_element(l, j);
            sllist_print(l);
        } else if (strcmp(command, "af") == 0) {
            // append front
            char *arg = strtok(NULL, " ");
            int *j = malloc(sizeof(int));
            *j = atoi(arg);
            sllist_prepend_element(l, j);
            sllist_print(l);
        } else if (strcmp(command, "dr") == 0) {
            // delete rear
            int *j = sllist_delete_rear(l);
            if (j != NULL) {
                free(j);
            }
            sllist_print(l);
        } else if (strcmp(command, "df") == 0) {
            // delete front
            int *j = sllist_delete_front(l);
            if (j != NULL) {
                free(j);
            }
            sllist_print(l);
        } else if (strcmp(command, "gs") == 0) {
            // get size
            printf("%lu\n", sllist_get_size(l));
        } else if (strcmp(command, "print") == 0) {
            // print sllist
            sllist_print(l);
        } else if (strcmp(command, "clear") == 0) {
            // clear screen
            system("clear");
        }
    }

    sllist_delete(&l);
    LOG_ERROR(l == NULL, "failed to cleanup sllist");
    return 0;

error:
    return 1;
}
