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
 * definition of a sllist (single linked list)
 */
typedef struct {
     /**
      * header node of sllist
      */
     node *header; 
     /**
      * trailer node of sllist
      */
     node *trailer; 
     /**
      * size of sllist, which excludes; header, and trailer nodes
      */
     size_t size; 
} sllist;

/**
 * definition of a sllist iterator
 */
typedef struct
{
     /**
      * sllist
      */
     sllist *l;
     /**
      * current node in sllist
      */
     node *curr;
} sllist_iter;

/**
 * create a new sllist iterator
 *
 * @returns newly created sllist iterator if successful, NULL otherwise
 *
 * @note runtime O(1)
 */
sllist_iter *sllist_iter_create(sllist *l);

/**
 * delete sllist iterator
 *
 * @param l_iter
 * sllist iterator
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
bool sllist_iter_delete(sllist_iter **l_iter);

/**
 * reset sllist iterator to its initial position
 *
 * @param l_iter
 * sllist iterator
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
bool sllist_iter_reset(sllist_iter *l_iter);

/**
 * check if sllist iterator has another item
 *
 * @param l_iter
 * sllist iterator
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
bool sllist_iter_has_next(sllist_iter *l_iter);

/**
 * get the next item from the sllist iterator
 *
 * @param l_iter
 * sllist iterator
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
 */
void *sllist_iter_next(sllist_iter *l_iter);

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
 * create a new sllist
 *
 * @returns newly created sllist if successful, NULL otherwise
 *
 * @note runtime O(1)
 */
sllist *sllist_create();

/**
 * delete sllist
 *
 * @param l
 * sllist
 *
 * @pre
 * l is not NULL
 *
 * @pre
 * *l is not NULL
 *
 * @returns true if successful, false otherwise
 *
 * @note runtime O(1)
 */
bool sllist_delete(sllist **l);

/**
 * get size of sllist
 *
 * @param l
 * sllist
 *
 * @pre
 * l is not NULL
 *
 * @returns size of sllist
 *
 * @note runtime O(1)
 */
size_t sllist_get_size(sllist *l);

/**
 * check if sllist is empty
 *
 * @param l
 * sllist
 *
 * @pre
 * l is not NULL
 *
 * @returns true if sllist is empty, false otherwise
 *
 * @note runtime O(1)
 */
bool sllist_is_empty(sllist *l);

/**
 * get first node of sllist
 *
 * @param l
 * sllist
 *
 * @pre
 * l is not NULL
 *
 * @pre
 * l is not empty
 *
 * @returns first node of sllist if it exists, NULL otherwise
 *
 * @note runtime O(1)
 */
node *sllist_get_front(sllist *l);

/**
 * get sllist's first node's data
 *
 * @param l
 * sllist
 *
 * @pre
 * l is not NULL
 *
 * @pre
 * l is not empty
 *
 * @returns sllist's first node's data if it exists, NULL otherwise
 *
 * @note runtime O(1)
 */
void *sllist_get_front_data(sllist *l);

/**
 * get last node of sllist
 *
 * @param l
 * sllist
 *
 * @pre
 * l is not NULL
 *
 * @pre
 * l is not empty
 *
 * @returns last node of sllist if it exists, NULL otherwise
 *
 * @note runtime O(1)
 */
node *sllist_get_rear(sllist *l);

/**
 * get sllist's last node's data
 *
 * @param l
 * sllist
 *
 * @pre
 * l is not NULL
 *
 * @pre
 * l is not empty
 *
 * @returns sllist's last node's data if it exists, NULL otherwise
 *
 * @note runtime O(1)
 */
void *sllist_get_rear_data(sllist *l);

/**
 * add element to front of sllist
 *
 * @param l
 * sllist
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
bool sllist_prepend_element(sllist *l, void *element);

/**
 * add element to end of sllist
 *
 * @param l
 * sllist
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
bool sllist_append_element(sllist *l, void *element);

/**
 * remove first element of the sllist
 *
 * @param l
 * sllist
 *
 * @pre
 * l is not NULL
 *
 * @pre
 * l is not empty
 *
 * @returns removed element from sllist if successful, NULL otherwise
 *
 * @note runtime O(1)
 */
void *sllist_delete_front(sllist *l);

/**
 * remove last element of sllist
 *
 * @param l
 * sllist
 *
 * @pre
 * l is not NULL
 *
 * @pre
 * l is not empty
 *
 * @returns removed element from sllist if successful, NULL otherwise
 *
 * @note runtime O(n)
 */
void *sllist_delete_rear(sllist *l);

/**
 * get number of elements in sllist which satisfy specified condition
 *
 * @param l
 * sllist
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
size_t sllist_count_elements(sllist *l, void *other, bool (*condition)(void *element, void *other));

/**
 * get elements in sllist which satisfy specified condition
 *
 * @param l 
 * sllist
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
 * @returns a sllist filled with the found elements if successful, NULL otherwise
 *
 * @note runtime O(n)
 */
sllist *sllist_get_elements(sllist *l, void *other, bool (*condition)(void *element, void *other));

/**
 * remove elements in sllist which satisfy specified condition
 *
 * @param l 
 * sllist
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
 * @returns a sllist filled with the removed elements if successful, NULL otherwise
 *
 * @note runtime O(n^2)
 */
sllist *sllist_delete_elements(sllist *l, void *other, bool (*condition)(void *element, void *other));

#endif
