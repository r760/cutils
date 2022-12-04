#ifndef QUEUE_H
#define QUEUE_H
#include "list.h"

typedef list queue;
typedef list_iter queue_iter;

/**
 * create a new queue iterator
 *
 * @returns newly created queue iterator if successful, NULL otherwise
 *
 * @note runtime O(1)
 * @see list_iter_create()
 */
#define queue_iter_create(l) list_iter_create(l)

/**
 * delete queue iterator
 *
 * @param l_iter
 * queue iterator
 *
 * @pre
 * l_iter is not NULL
 *
 * @pre
 * *l_iter is not NULL
 *
 * @returns true if successful, false otherwise
 *
 * @note runtime O(1)
 * @see list_iter_delete()
 */
#define queue_iter_delete(l_iter) list_iter_delete(l_iter)

/**
 * reset queue iterator to its initial position
 *
 * @param l_iter
 * queue iterator
 *
 * @pre
 * l_iter is not NULL
 *
 * @pre
 * *l_iter is not NULL
 *
 * @returns true if successful, false otherwise
 *
 * @note runtime O(1)
 * @see list_iter_reset()
 */
#define queue_iter_reset(l_iter) list_iter_reset(l_iter)

/**
 * check if queue iterator has another item
 *
 * @param l_iter
 * queue iterator
 *
 * @pre
 * l_iter is not NULL
 *
 * @pre
 * *l_iter is not NULL
 *
 * @returns true if successful, false otherwise
 *
 * @note runtime O(1)
 * @see list_iter_has_next()
 */
#define queue_iter_has_next(l_iter) list_iter_has_next(l_iter)

/**
 * get the next item from the queue iterator
 *
 * @param l_iter
 * queue iterator
 *
 * @pre
 * l_iter is not NULL
 *
 * @pre
 * *l_iter is not NULL
 *
 * @returns pair if successful, false otherwise
 *
 * @note runtime O(1)
 * @see list_iter_next()
 */
#define queue_iter_next(l_iter) list_iter_next(l_iter)

/**
 * create a new queue
 *
 * @returns newly created queue if successful, NULL otherwise
 *
 * @note runtime O(1)
 * @see list_create()
 */
#define queue_create() list_create()

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
 * @see list_delete()
 */
#define queue_delete(q) list_delete(q)

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
 * @see list_get_size()
 */
#define queue_get_size(q) list_get_size(q)

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
 * @see list_is_empty()
 */
#define queue_is_empty(q) list_is_empty(q)

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
 * @see list_get_front_data()
 */
#define queue_peek(q) list_get_front_data(q)

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
 * @see list_append_element()
 */
#define queue_enqueue(q, e) list_append_element(q, e)

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
 * @see list_delete_front()
 */
#define queue_dequeue(q) list_delete_front(q)

#endif
