#ifndef SLLIST_H
#define SLLIST_H
#include <stdbool.h>
#include <stdlib.h>
#define SLLIST_FOR_EACH(curr, l) \
for (node *curr = (sllist_is_empty(l) == false) ? sllist_get_front(l) : NULL; curr != NULL; curr = curr->next)

/**
 * definition of a node
 */
struct node {
    struct node *next;
    void *data;
};

typedef struct node node;

/**
 * definition of a sllist (single linked list)
 */
typedef struct {
    node *header;
    node *trailer;
    size_t size;
} sllist;

/**
 * creates a new node
 * returns a pointer to it if successful, NULL otherwise
 *
 * O(1)
 */
node *node_create();

/**
 * deletes the node pointed to by 'n'
 * returns true if successful, false otherwise
 *
 * O(1)
 */
bool node_delete(node **n);

/**
 * creates a new sllist
 * returns a pointer to it if successful, NULL otherwise
 *
 * O(1)
 */
sllist *sllist_create();

/**
 * deletes the sllist pointed to by 'l'
 * returns true if successful, false otherwise
 *
 * O(1)
 */
bool sllist_delete(sllist **l);

/**
 * returns the size of sllist 'd'
 *
 * O(1)
 */
size_t sllist_get_size(sllist *l);

/**
 * returns true if sllist 'l' is empty, false otherwise
 *
 * O(1)
 */
bool sllist_is_empty(sllist *l);

/**
 * returns the first node of sllist 'l' if it exists, NULL otherwise
 *
 * O(1)
 */
node *sllist_get_front(sllist *l);

/**
 * returns the first node's data of sllist 'l' if it exists, NULL otherwise
 *
 * O(1)
 */
void *sllist_get_front_data(sllist *l);

/**
 * returns the last node of sllist 'l' if it exists, NULL otherwise
 *
 * O(1)
 */
node *sllist_get_rear(sllist *l);

/**
 * returns the last node's data of sllist 'l' if it exists, NULL otherwise
 *
 * O(1)
 */
void *sllist_get_rear_data(sllist *l);

/**
 * adds 'element' to the front of sllist 'l'
 * returns true if successful, false otherwise
 *
 * O(1)
 */
bool sllist_prepend_element(sllist *l, void *element);

/**
 * adds 'element' to the end of sllist 'l'
 * returns true if successful, false otherwise
 *
 * O(1)
 */
bool sllist_append_element(sllist *l, void *element);

/**
 * removes the first element of sllist 'l'
 * returns the removed element if successful, NULL otherwise
 *
 * O(1)
 */
void *sllist_delete_front(sllist *l);

/**
 * removes the last element of sllist 'l' 
 * returns the removed element if successful, NULL otherwise
 *
 * O(n)
 */
void *sllist_delete_rear(sllist *l);

#endif
