#include <stdio.h>
#include <stdlib.h>
#include "../include/log.h"
#include "../include/darray.h"
#define BUFF_SIZE 100

void darray_print(darray *d)
{
    printf("[");
    DARRAY_FOREACH(i, d) {
        printf("%d", *(int *)darray_get_element_at_index(d, i));
        if (i < darray_get_size(d) - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(int argc, char *argv[])
{
    char buffer[BUFF_SIZE];

    darray *d = darray_create();

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
        } else if (strcmp(command, "ar") == 0) {
            // append rear
            char *arg = strtok(NULL, " ");
            int *j = malloc(sizeof(int));
            *j = atoi(arg);
            darray_append_element(d, j);
            darray_print(d);
        } else if (strcmp(command, "af") == 0) {
            // append front
            char *arg = strtok(NULL, " ");
            int *j = malloc(sizeof(int));
            *j = atoi(arg);
            darray_prepend_element(d, j);
            darray_print(d);
        } else if (strcmp(command, "dr") == 0) {
            // delete rear
            int *j = darray_delete_rear(d);
            if (j != NULL) {
                free(j);
            }
            darray_print(d);
        } else if (strcmp(command, "df") == 0) {
            // delete front
            int *j = darray_delete_front(d);
            if (j != NULL) {
                free(j);
            }
            darray_print(d);
        } else if (strcmp(command, "rev") == 0) {
            // reverse
            darray_reverse(d);
            darray_print(d);
        } else if (strcmp(command, "a@i") == 0) {
            // add at index
            char *arg = strtok(NULL, " ");
            int *j = malloc(sizeof(int));
            *j = atoi(arg);
            arg = strtok(NULL, " ");
            int k;
            k = atoi(arg);
            darray_insert_element_at_index(d, j, k);
            darray_print(d);
        } else if (strcmp(command, "d@i") == 0) {
            // delete at index
            char *arg = strtok(NULL, " ");
            int j;
            j = atoi(arg);
            void *data = darray_delete_at_index(d, j);
            if (data != NULL) {
                free(data);
            }
            darray_print(d);
        } else if (strcmp(command, "gs") == 0) {
            // get size
            printf("%lu\n", darray_get_size(d));
        } else if (strcmp(command, "gc") == 0) {
            // get capactiy
            printf("%lu\n", darray_get_capacity(d));
        } else if (strcmp(command, "print") == 0) {
            // print darray
            darray_print(d);
        } else if (strcmp(command, "clear") == 0) {
            // clear screen
            system("clear");
        }
    }

    darray_delete(&d);
    LOG_ERROR(d == NULL, "failed to cleanup darray");
    return 0;

error:
    return 1;
}
