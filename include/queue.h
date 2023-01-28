#ifndef QUEUE_H
#define QUEUE_H
#include "list.h"

typedef list queue;

typedef list_iter queue_iter;

#define queue_iter_create(q) list_iter_create(q)

#define queue_iter_delete(q_iter) list_iter_delete(q_iter)

#define queue_iter_reset(q_iter) list_iter_reset(q_iter)

#define queue_iter_has_next(q_iter) list_iter_has_next(q_iter)

#define queue_iter_next(q_iter) list_iter_next(q_iter)

#define queue_create() list_create()

#define queue_delete(q) list_delete(q)

#define queue_get_size(q) list_get_size(q)

#define queue_is_empty(q) list_is_empty(q)

#define queue_peek(q) list_get_front_data(q)

#define queue_enqueue(q, e) list_append_element(q, e)

#define queue_dequeue(q) list_delete_front(q)

#endif
