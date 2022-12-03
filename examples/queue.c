#include <stdio.h>
#include "queue.h"

int main(int argc, char *argv[])
{
    // create queue
    queue *q = queue_create();

    // add command line arguments to queue
    for (int i = 1; i < argc; i++) {
        queue_enqueue(q, argv[i]);
    }

    // print queue size
    printf("queue size: '%lu'\n", queue_get_size(q));

    // print queue 'is empty'
    bool is_empty = queue_is_empty(q);
    char *is_empty_str = (is_empty) ? "true" : "false";
    printf("queue empty: '%s'\n", is_empty_str);

    // print queue's 'most anciently added element'
    char *data = queue_peek(q);
    printf("queue peek: '%s'\n", data);

    // dequeue each element of queue and print it
    printf("[");
    while (!queue_is_empty(q)) {
        char *data = queue_dequeue(q);
        printf("%s", data);
        if (queue_get_size(q) >= 1) {
            printf(", ");
        }
    }
    printf("]\n");

    // free queue
    queue_delete(&q);

    return 0;
}
