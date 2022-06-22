#ifndef QUEUE_H
#define QUEUE_H
#include "sllist.h"

typedef sllist queue;

#define QUEUE_FOR_EACH SLLIST_FOR_EACH

/**
 * creates a new queue
 * returns a pointer to it if successful, NULL otherwise
 *
 * O(1)
 */
#define queue_create() sllist_create()

/**
 * deletes the queue pointed to by 'q'
 * returns true if successful, false otherwise
 *
 * O(1)
 */
#define queue_delete(q) sllist_delete(q)

/**
 * returns the size of queue 'q'
 *
 * O(1)
 */
#define queue_get_size(q) sllist_get_size(q)

/**
 * returns true if queue 'q' is empty, false otherwise
 *
 * O(1)
 */
#define queue_is_empty(q) sllist_is_empty(q)

/**
 * returns the most anciently added element to queue 'q' if it exists, NULL otherwise
 *
 * O(1)
 */
#define queue_peek(q) sllist_get_rear_data(q)

/**
 * adds element 'e' to queue 'q'
 * returns true if successful, false otherwise
 *
 * O(1)
 */
#define queue_enqueue(q, e) sllist_append_element(q, e)

/**
 * removes the most anciently added element in queue 'q'
 * returns the most anciently added element to queue 'q' if it exists, NULL otherwise
 *
 * O(n)
 */
#define queue_dequeue(q) sllist_delete_rear(q)

#endif
