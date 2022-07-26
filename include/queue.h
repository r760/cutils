#ifndef QUEUE_H
#define QUEUE_H
#include "sllist.h"

typedef sllist queue;

/**
 * walk queue
 *
 * @note runtime O(n)
 * @see SLLIST_FOR_EACH
 */
#define QUEUE_FOR_EACH SLLIST_FOR_EACH

/**
 * create a new queue
 *
 * @returns newly created queue if successful, NULL otherwise
 *
 * @note runtime O(1)
 * @see sllist_create()
 */
#define queue_create() sllist_create()

/**
 * delete queue
 *
 * @param q
 * queue
 *
 * @pre
 * q is not NULL
 *
 * @returns true if successful, false otherwise
 *
 * @note runtime O(1)
 * @see sllist_delete()
 */
#define queue_delete(q) sllist_delete(q)

/**
 * get size of queue
 *
 * @param q
 * queue
 *
 * @pre
 * q is not NULL
 *
 * @returns size of queue
 *
 * @note runtime O(1)
 * @see sllist_get_size()
 */
#define queue_get_size(q) sllist_get_size(q)

/**
 * check if queue is empty
 *
 * @param q
 * queue
 *
 * @pre
 * q is not NULL
 *
 * @returns true if queue is empty, false otherwise
 *
 * @note runtime O(1)
 * @see sllist_is_empty()
 */
#define queue_is_empty(q) sllist_is_empty(q)

/**
 * get most anciently added element to queue
 *
 * @param q
 * queue
 *
 * @pre
 * q is not NULL
 *
 * @pre
 * q is not empty
 *
 * @returns most anciently added element to queue if it exists, NULL otherwise
 *
 * @note runtime O(1)
 * @see sllist_get_front_data()
 */
#define queue_peek(q) sllist_get_front_data(q)

/**
 * add element to queue
 *
 * @param q
 * queue
 *
 * @param e
 * element
 *
 * @pre
 * q is not NULL
 *
 * @pre
 * e is not NULL
 *
 * @returns true if successful, false otherwise
 *
 * @note runtime O(1)
 * @see sllist_append_element()
 */
#define queue_enqueue(q, e) sllist_append_element(q, e)

/**
 * remove most anciently added element to queue
 *
 * @param q
 * queue
 *
 * @pre
 * q is not NULL
 *
 * @pre
 * q is not empty
 *
 * @returns most anciently added element to queue if it exists, NULL otherwise
 *
 * @note runtime O(1)
 * @see sllist_delete_front()
 */
#define queue_dequeue(q) sllist_delete_front(q)

#endif
