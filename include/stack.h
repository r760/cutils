#ifndef STACK_H
#define STACK_H
#include "sllist.h"

typedef sllist stack;

#define STACK_FOR_EACH SLLIST_FOR_EACH

/**
 * creates a new stack
 * returns a pointer to it if successful, NULL otherwise
 *
 * O(1)
 */
#define stack_create() sllist_create()

/**
 * deletes the stack pointed to by 's'
 * returns true if successful, false otherwise
 *
 * O(1)
 */
#define stack_delete(s) sllist_delete(s)

/**
 * returns the size of stack 's'
 *
 * O(1)
 */
#define stack_get_size(s) sllist_get_size(s)

/**
 * returns true if stack 's' is empty, false otherwise
 *
 * O(1)
 */
#define stack_is_empty(l) sllist_is_empty(l)

/**
 * returns the most recently added element to stack 's' if it exists, NULL otherwise
 *
 * O(1)
 */
#define stack_top(s) sllist_get_front_data(s)

/**
 * pushes element 'e' on to stack 's'
 * returns true if successful, false otherwise
 *
 * O(1)
 */
#define stack_push(s, e) sllist_prepend_element(s, e)

/**
 * pops stack 's'
 * returns the most recently added element to stack 's' if it exists, NULL otherwise
 *
 * O(1)
 */
#define stack_pop(s) sllist_delete_front(s)

#endif
