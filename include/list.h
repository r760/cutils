#ifndef SLLIST_H
#define SLLIST_H
#include <stdbool.h>
#include <stdlib.h>

/**
 * definition of a node
 */
struct node {
     /**
      * next node
      */
     struct node *next; 
     /**
      * data contained in current node
      */
     void *data; 
};

typedef struct node node;

/**
 * definition of a list (single linked list)
 */
typedef struct {
     /**
      * header node of list
      */
     node *header; 
     /**
      * trailer node of list
      */
     node *trailer; 
     /**
      * size of list, which excludes; header, and trailer nodes
      */
     size_t size; 
} list;

/**
 * definition of a list iterator
 */
typedef struct
{
     /**
      * list
      */
     list *l;
     /**
      * current node in list
      */
     node *curr;
} list_iter;

/**
 * create a new list iterator
 *
 * @param l
 * list
 *
 * @pre
 * l is not NULL

 * @returns newly created list iterator if successful, NULL otherwise
 *
 * @note runtime O(1)
 */
list_iter *list_iter_create(list *l);

/**
 * delete list iterator
 *
 * @param l_iter
 * list iterator
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
 */
bool list_iter_delete(list_iter **l_iter);

/**
 * reset list iterator to its initial position
 *
 * @param l_iter
 * list iterator
 *
 * @pre
 * l_iter is not NULL
 *
 * @returns true if successful, false otherwise
 *
 * @note runtime O(1)
 */
bool list_iter_reset(list_iter *l_iter);

/**
 * check if list iterator has another item
 *
 * @param l_iter
 * list iterator
 *
 * @pre
 * l_iter is not NULL
 *
 * @returns true if list iterator has another item, false otherwise
 *
 * @note runtime O(1)
 */
bool list_iter_has_next(list_iter *l_iter);

/**
 * get the next item from the list iterator
 *
 * @param l_iter
 * list iterator
 *
 * @pre
 * l_iter is not NULL
 *
 * @returns the next item from the list iterator if it has one, NULL otherwise
 *
 * @note runtime O(1)
 */
void *list_iter_next(list_iter *l_iter);

/**
 * create a new node
 * 
 * @returns newly created node if successful, NULL otherwise
 *
 * @note runtime O(1)
 */
node *node_create();

/**
 * delete node
 *
 * @param n
 * node
 *
 * @pre
 * n is not NULL
 *
 * @pre
 * *n is not NULL
 *
 * @returns true if successful, false otherwise
 *
 * @note runtime O(1)
 */
bool node_delete(node **n);

/**
 * create a new list
 *
 * @returns newly created list if successful, NULL otherwise
 *
 * @note runtime O(1)
 */
list *list_create();

/**
 * delete list
 *
 * @param l
 * list
 *
 * @pre
 * l is not NULL
 *
 * @pre
 * *l is not NULL
 *
 * @returns true if successful, false otherwise
 *
 * @note runtime O(n)
 */
bool list_delete(list **l);

/**
 * get size of list
 *
 * @param l
 * list
 *
 * @pre
 * l is not NULL
 *
 * @returns size of list
 *
 * @note runtime O(1)
 */
size_t list_get_size(list *l);

/**
 * check if list is empty
 *
 * @param l
 * list
 *
 * @pre
 * l is not NULL
 *
 * @returns true if list is empty, false otherwise
 *
 * @note runtime O(1)
 */
bool list_is_empty(list *l);

/**
 * get first node of list
 *
 * @param l
 * list
 *
 * @pre
 * l is not NULL
 *
 * @pre
 * l is not empty
 *
 * @returns first node of list if it exists, NULL otherwise
 *
 * @note runtime O(1)
 */
node *list_get_front(list *l);

/**
 * get list's first node's data
 *
 * @param l
 * list
 *
 * @pre
 * l is not NULL
 *
 * @pre
 * l is not empty
 *
 * @returns list's first node's data if it exists, NULL otherwise
 *
 * @note runtime O(1)
 */
void *list_get_front_data(list *l);

/**
 * get last node of list
 *
 * @param l
 * list
 *
 * @pre
 * l is not NULL
 *
 * @pre
 * l is not empty
 *
 * @returns last node of list if it exists, NULL otherwise
 *
 * @note runtime O(1)
 */
node *list_get_rear(list *l);

/**
 * get list's last node's data
 *
 * @param l
 * list
 *
 * @pre
 * l is not NULL
 *
 * @pre
 * l is not empty
 *
 * @returns list's last node's data if it exists, NULL otherwise
 *
 * @note runtime O(1)
 */
void *list_get_rear_data(list *l);

/**
 * add element to front of list
 *
 * @param l
 * list
 *
 * @param element
 * element
 *
 * @pre
 * l is not NULL
 *
 * @pre
 * element is not NULL
 *
 * @returns true if successful, false otherwise
 *
 * @note runtime O(1)
 */
bool list_prepend_element(list *l, void *element);

/**
 * add element to end of list
 *
 * @param l
 * list
 *
 * @param element
 * element
 *
 * @pre
 * l is not NULL
 *
 * @pre
 * element is not NULL
 *
 * @returns true if successful, false otherwise
 *
 * @note runtime O(1)
 */
bool list_append_element(list *l, void *element);

/**
 * remove first element of the list
 *
 * @param l
 * list
 *
 * @pre
 * l is not NULL
 *
 * @pre
 * l is not empty
 *
 * @returns removed element from list if successful, NULL otherwise
 *
 * @note runtime O(1)
 */
void *list_delete_front(list *l);

/**
 * remove last element of list
 *
 * @param l
 * list
 *
 * @pre
 * l is not NULL
 *
 * @pre
 * l is not empty
 *
 * @returns removed element from list if successful, NULL otherwise
 *
 * @note runtime O(n)
 */
void *list_delete_rear(list *l);

/**
 * get number of elements in list which satisfy specified condition
 *
 * @param l
 * list
 *
 * @param other
 * argument to pass to condition function
 *
 * @param condition 
 * condition (function pointer)
 *
 * @pre
 * l is not NULL
 *
 * @pre
 * l is not empty
 *
 * @pre
 * condition is not NULL
 *
 * @returns number of elements found
 *
 * @note runtime O(n)
 */
size_t list_count_elements(list *l, void *other, bool (*condition)(void *element, void *other));

/**
 * get elements in list which satisfy specified condition
 *
 * @param l 
 * list
 *
 * @param other
 * argument to pass to condition function 
 *
 * @param condition 
 * condition (function pointer)
 *
 * @pre
 * l is not NULL
 *
 * @pre
 * l is not empty
 *
 * @pre
 * condition is not NULL
 *
 * @returns a list filled with the found elements if successful, NULL otherwise
 *
 * @note runtime O(n)
 */
list *list_get_elements(list *l, void *other, bool (*condition)(void *element, void *other));

/**
 * remove elements in list which satisfy specified condition
 *
 * @param l 
 * list
 *
 * @param other
 * argument to pass to condition function 
 *
 * @param condition 
 * condition (function pointer)
 *
 * @pre
 * l is not NULL
 *
 * @pre
 * l is not empty
 *
 * @pre
 * condition is not NULL
 *
 * @returns a list filled with the removed elements if successful, NULL otherwise
 *
 * @note runtime O(n^2)
 */
list *list_delete_elements(list *l, void *other, bool (*condition)(void *element, void *other));

#endif
