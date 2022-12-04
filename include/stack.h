#ifndef STACK_H
#define STACK_H
#include "list.h"

typedef list stack;
typedef list_iter stack_iter;

/**
 * create a new stack iterator
 *
 * @returns newly created stack iterator if successful, NULL otherwise
 *
 * @note runtime O(1)
 * @see list_iter_create()
 */
#define stack_iter_create(l) list_iter_create(l)

/**
 * delete stack iterator
 *
 * @param l_iter
 * stack iterator
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
#define stack_iter_delete(l_iter) list_iter_delete(l_iter)

/**
 * reset stack iterator to its initial position
 *
 * @param l_iter
 * stack iterator
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
#define stack_iter_reset(l_iter) list_iter_reset(l_iter)

/**
 * check if stack iterator has another item
 *
 * @param l_iter
 * stack iterator
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
#define stack_iter_has_next(l_iter) list_iter_has_next(l_iter)

/**
 * get the next item from the stack iterator
 *
 * @param l_iter
 * stack iterator
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
#define stack_iter_next(l_iter) list_iter_next(l_iter)

/**
 * create a new stack
 *
 * @returns newly created stack if successful, NULL otherwise
 *
 * @note runtime O(1)
 * @see list_create()
 */
#define stack_create() list_create()

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
 * @see list_delete()
 */
#define stack_delete(s) list_delete(s)

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
 * @see list_get_size()
 */
#define stack_get_size(s) list_get_size(s)

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
 * @see list_is_empty() 
 */
#define stack_is_empty(s) list_is_empty(s)

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
 * @see list_get_front_data()
 */
#define stack_top(s) list_get_front_data(s)

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
 * @see list_prepend_element()
 */
#define stack_push(s, e) list_prepend_element(s, e)

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
 * @see list_delete_front()
 */
#define stack_pop(s) list_delete_front(s)

#endif
