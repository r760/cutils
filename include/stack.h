#ifndef STACK_H
#define STACK_H
#include "list.h"

typedef list stack;

typedef list_iter stack_iter;

#define stack_iter_create(s) list_iter_create(s)

#define stack_iter_delete(s_iter) list_iter_delete(s_iter)

#define stack_iter_reset(s_iter) list_iter_reset(s_iter)

#define stack_iter_has_next(s_iter) list_iter_has_next(s_iter)

#define stack_iter_next(s_iter) list_iter_next(s_iter)

#define stack_create() list_create()

#define stack_delete(s) list_delete(s)

#define stack_get_size(s) list_get_size(s)

#define stack_is_empty(s) list_is_empty(s)

#define stack_top(s) list_get_front_data(s)

#define stack_push(s, e) list_prepend_element(s, e)

#define stack_pop(s) list_delete_front(s)

#endif
