#ifndef DARRAY_H
#define DARRAY_H
#include <stdbool.h>
#include <stdlib.h>
#define DARRAY_FOREACH(i, d) for (size_t i = 0; !darray_is_empty(d) && i < darray_get_size(d); i++)

/**
 * time complexity assumptions:
 *  malloc is O(1), realloc O(1)
 */

/**
 * definition of a dynamic array
 */
typedef struct
{
    size_t size, capacity, size_of_data;
    void **data;
} darray;

/**
 * creates a new dynamic array 
 * returns a pointer to it if successful, NULL otherwise
 *
 * O(1)
 */
darray* darray_create();

/**
 * deletes the dynamic array pointed to by 'd'
 * returns true if successful, false otherwise
 *
 * O(1)
 */
bool darray_delete(darray **d);

/**
 * returns true if dynamic array 'd' is empty, false otherwise
 *
 * O(1)
 */
bool darray_is_empty(darray *d);

/**
 * adds 'element' to the end of dynamic array 'd'
 * returns true if successful, false otherwise
 *
 * O(1)
 */
bool darray_append_element(darray *d, void *element);

/**
 * adds 'element' to the front of dynamic array 'd'
 * returns true if successful, false otherwise
 *
 * O(n)
 */
bool darray_prepend_element(darray *d, void *element);

/**
 * removes the last element of dynamic array 'd' 
 * returns the removed element if successful, NULL otherwise
 *
 * O(1)
 */
void *darray_delete_rear(darray *d);

/**
 * removes the first element of dynamic array 'd'
 * returns the removed element if successful, NULL otherwise
 *
 * O(n)
 */
void *darray_delete_front(darray *d);

/**
 * inserts 'element' at 'index' of dynamic array 'd'
 * returns true if successful, false otherwise
 *
 * O(n)
 */
bool darray_insert_element_at_index(darray *d, void *element, size_t index);

/**
 * removes element at 'index' of dynamic array 'd'
 * returns the removed element if successful, NULL otherwise
 *
 * O(n)
 */
void *darray_delete_at_index(darray *d, size_t index);

/**
 * returns element at 'index' of dynamic array 'd' if successful, NULL otherwise
 *
 * O(1)
 */
void *darray_get_element_at_index(darray *d, size_t index);

/**
 * sets 'index' of dynamic array 'd' to 'element'
 * returns true if successful, false otherwise
 *
 * O(1)
 */
bool darray_set_element_at_index(darray *d, void* element, size_t index);

/**
 * reverses dynamic array 'd' element-wise
 * returns true if successful, false otherwise
 *
 * O(n)
 */
bool darray_reverse(darray *d);

/**
 * returns the size of dynamic array 'd'
 *
 * O(1)
 */
size_t darray_get_size(darray *d);

/**
 * returns the capacity of dynamic array 'd'
 *
 * O(1)
 */
size_t darray_get_capacity(darray *d);

#endif
