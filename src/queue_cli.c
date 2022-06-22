#include <stdlib.h>
#include <stdio.h>
#include "../include/log.h"
#include "../include/queue.h"
#define BUFF_SIZE 100

void queue_print(queue *q)
{
    void *data = NULL;

    printf("[");
    QUEUE_FOR_EACH(curr, q) {
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

    queue *q = queue_create();

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
        } else if (strcmp(command, "e") == 0) {
            // enqueue
            char *arg = strtok(NULL, " ");
            int *j = malloc(sizeof(int));
            *j = atoi(arg);
            queue_enqueue(q, j);
            queue_print(q);
        } else if (strcmp(command, "d") == 0) {
            // dequeue
            int *j = queue_dequeue(q);
            if (j != NULL) {
                free(j);
            }
            queue_print(q);
        } else if (strcmp(command, "p") == 0) {
            // peek
            int *j = queue_peek(q);
            if (j != NULL) {
                printf("%d\n", *j);
            }
        } else if (strcmp(command, "gs") == 0) {
            // get size
            printf("%lu\n", queue_get_size(q));
        } else if (strcmp(command, "print") == 0) {
            // print queue
            queue_print(q);
        } else if (strcmp(command, "clear") == 0) {
            // clear screen
            system("clear");
        }
    }

    queue_delete(&q);
    LOG_ERROR(q == NULL, "failed to cleanup queue");
    return 0;

error:
    return 1;
}
