#ifndef STACK_H
#define STACK_H
#include "sllist.h"

typedef sllist stack;

/**
 * walk stack
 *
 * @note runtime O(n)
 * @see SLLIST_FOR_EACH
 */
#define STACK_FOR_EACH SLLIST_FOR_EACH

/**
 * create a new stack
 *
 * @returns newly created stack if successful, NULL otherwise
 *
 * @note runtime O(1)
 * @see sllist_create()
 */
#define stack_create() sllist_create()

/**
 * delete stack
 *
 * @param s
 * stack
 *
 * @pre
 * s is not NULL
 *
 * @returns true if successful, false otherwise
 *
 * @note runtime O(1)
 * @see sllist_delete()
 */
#define stack_delete(s) sllist_delete(s)

/**
 * get size of stack
 *
 * @param s
 * stack
 *
 * @pre
 * s is not NULL
 *
 * @returns size of stack
 *
 * @note runtime O(1)
 * @see sllist_get_size()
 */
#define stack_get_size(s) sllist_get_size(s)

/**
 * check if stack is empty
 *
 * @param s 
 * stack
 *
 * @pre
 * s is not NULL
 *
 * @returns true if stack is empty, false otherwise
 *
 * @note runtime O(1)
 * @see sllist_is_empty() 
 */
#define stack_is_empty(s) sllist_is_empty(s)

/**
 * get most recently added element to stack
 *
 * @param s
 * stack
 *
 * @pre
 * s is not NULL
 *
 * @pre
 * s is not empty
 *
 * @returns most recently added element to stack if it exists, NULL otherwise
 *
 * @note runtime O(1)
 * @see sllist_get_front_data()
 */
#define stack_top(s) sllist_get_front_data(s)

/**
 * push element to stack
 *
 * @param s
 * stack
 *
 * @param e
 * element
 *
 * @pre
 * s is not NULL
 *
 * @pre
 * e is not NULL
 *
 * @returns true if successful, false otherwise
 *
 * @note runtime O(1)
 * @see sllist_prepend_element()
 */
#define stack_push(s, e) sllist_prepend_element(s, e)

/**
 * pop stack
 *
 * @param s
 * stack
 *
 * @pre
 * s is not NULL
 *
 * @pre
 * s is not empty
 *
 * @returns most recently added element to stack if it exists, NULL otherwise
 *
 * @note runtime O(1)
 * @see sllist_delete_front()
 */
#define stack_pop(s) sllist_delete_front(s)

#endif
