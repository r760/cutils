#ifndef DARRAY_H
#define DARRAY_H
#include <stdbool.h>
#include <stdlib.h>

/**
 * definition of a dynamic array
 */
typedef struct
{
     /**
      * size of dynamic array, ie the number of elements currently contained in dynamic array
      */
     size_t size;
     /**
      * capacity of dynamic array, ie the number of elements that can be contained in dynamic array
      *
      * @note capacity of dynamic array is dynamically increased/decreased as needed
      */
     size_t capacity;
     /**
      * size of data in dynamic array, this is set to the size of void *
      */
     size_t size_of_data;
     /**
      * data held in dynamic array
      */
     void **data;
} darray;

/**
 * definition of a dynamic array iterator
 */
typedef struct
{
     /**
      * dynamic array
      */
     darray *d;
     /**
      * index of the current entry in the dynamic array
      */
     size_t i;
} darray_iter;

/**
 * create a new dynamic array iterator
 *
 * @param d
 * dynamic array
 *
 * @pre
 * d is not NULL
 *
 * @returns newly created dynamic array iterator if successful, NULL otherwise
 *
 * @note runtime O(1)
 */
darray_iter *darray_iter_create(darray *d);

/**
 * delete dynamic array iterator
 *
 * @param d_iter
 * dynamic array iterator
 *
 * @pre
 * d_iter is not NULL
 *
 * @pre
 * *d_iter is not NULL
 *
 * @returns true if successful, false otherwise
 *
 * @note runtime O(1)
 */
bool darray_iter_delete(darray_iter **d_iter);

/**
 * reset dynamic array iterator to its initial position
 *
 * @param d_iter
 * dynamic array iterator
 *
 * @pre
 * d_iter is not NULL
 *
 * @pre
 * *d_iter is not NULL
 *
 * @returns true if successful, false otherwise
 *
 * @note runtime O(1)
 */
bool darray_iter_reset(darray_iter *d_iter);

/**
 * check if dynamic array iterator has another item
 *
 * @param d_iter
 * dynamic array iterator
 *
 * @pre
 * d_iter is not NULL
 *
 * @pre
 * *d_iter is not NULL
 *
 * @returns true if dynamic array iterator has another item, false otherwise
 *
 * @note runtime O(1)
 */
bool darray_iter_has_next(darray_iter *d_iter);

/**
 * get the next item from the dynamic array iterator
 *
 * @param d_iter
 * dynamic array iterator
 *
 * @pre
 * d_iter is not NULL
 *
 * @pre
 * *d_iter is not NULL
 *
 * @returns the next item from the dynamic array iterator if it has one, NULL otherwise
 *
 * @note runtime O(1)
 */
void *darray_iter_next(darray_iter *d_iter);

/**
 * create a new dynamic array 
 *
 * @returns newly created dynamic array if successful, NULL otherwise
 *
 * @note runtime O(1)
 */
darray* darray_create();

/**
 * delete dynamic array
 *
 * @param d 
 * dynamic array
 *
 * @pre
 * d is not NULL
 *
 * @pre
 * *d is not NULL
 *
 * @returns true if successful, false otherwise
 *
 * @note runtime O(1)
 */
bool darray_delete(darray **d);

/**
 * get size of dynamic array
 *
 * @param d
 * dynamic array
 *
 * @pre
 * d is not NULL
 *
 * @returns size of dynamic array
 *
 * @note runtime O(1)
 */
size_t darray_get_size(darray *d);

/**
 * get capacity of dynamic array
 *
 * @param d
 * dynamic array
 *
 * @pre
 * d is not NULL
 *
 * @returns capacity of dynamic array
 *
 * @note runtime O(1)
 */
size_t darray_get_capacity(darray *d);

/**
 * check if dynamic array is empty
 *
 * @param d
 * dynamic array
 *
 * @pre
 * d is not NULL
 *
 * @returns true if dynamic array is empty, false otherwise
 *
 * @note runtime O(1)
 */
bool darray_is_empty(darray *d);

/**
 * add element to front of dynamic array
 *
 * @param d
 * dynamic array
 *
 * @param element 
 * element
 *
 * @pre
 * d is not NULL
 *
 * @pre
 * element is not NULL
 *
 * @returns true if successful, false otherwise
 *
 * @note runtime O(n)
 */
bool darray_prepend_element(darray *d, void *element);

/**
 * add element to end of dynamic array
 *
 * @param d
 * dynamic array
 *
 * @param element
 * element
 *
 * @pre
 * d is not NULL
 *
 * @pre
 * element is not NULL
 *
 * @returns true if successful, false otherwise
 *
 * @note runtime O(1)
 */
bool darray_append_element(darray *d, void *element);

/**
 * removes first element of dynamic array
 *
 * @param d
 * dynamic array
 *
 * @pre
 * d is not NULL
 *
 * @pre
 * d is not empty
 *
 * @returns removed element if successful, NULL otherwise
 *
 * @note runtime O(n)
 */
void *darray_delete_front(darray *d);

/**
 * remove last element of dynamic array
 *
 * @param d
 * dynamic array
 *
 * @pre
 * d is not NULL
 *
 * @pre
 * d is not empty
 *
 * @returns removed element if successful, NULL otherwise
 *
 * @note runtime O(1)
 */
void *darray_delete_rear(darray *d);

/**
 * add element to dynamic array at specified index
 *
 * @param d 
 * dynamic array
 *
 * @param element 
 * element
 *
 * @param index 
 * index
 *
 * @pre
 * d is not NULL
 *
 * @pre
 * element is not NULL
 *
 * @pre 
 * if dynamic array size > 0 then index <= dynamic array size
 *
 * @returns true if successful, false otherwise
 *
 * @note runtime O(n)
 */
bool darray_insert_element_at_index(darray *d, void *element, size_t index);

/**
 * remove element from dynamic array at specified index
 *
 * @param d
 * dynamic array
 * 
 * @param index
 * index
 *
 * @pre
 * d is not NULL
 *
 * @pre
 * d is not empty
 *
 * @pre
 * index >= 0 and index <= dynamic array size - 1
 *
 * @returns removed element if successful, NULL otherwise
 *
 * @note runtime O(n)
 */
void *darray_delete_element_at_index(darray *d, size_t index);

/**
 * get element from dynamic array at specified index
 *
 * @param d
 * dynamic array
 *
 * @param index
 * index
 *
 * @pre
 * d is not NULL
 *
 * @pre
 * d is not empty
 *
 * @returns element at index of dynamic array if successful, NULL otherwise
 *
 * @note runtime O(1)
 */
void *darray_get_element_at_index(darray *d, size_t index);

/**
 * set element of dynamic array at specified index
 *
 * @param d 
 * dynamic array
 *
 * @param element
 * element
 *
 * @param index 
 * index
 *
 * @pre
 * d is not NULL
 *
 * @pre
 * d is not empty
 *
 * @pre
 * element is not NULL
 *
 * @pre
 * index >= 0 and index <= dynamic array size - 1
 *
 * @returns true if successful, false otherwise
 *
 * @note runtime O(1)
 */
bool darray_set_element_at_index(darray *d, void* element, size_t index);

/**
 * get number of elements in dynamic array which satisfy specified condition
 *
 * @param d
 * dynamic array
 *
 * @param other
 * argument to pass to condition function
 *
 * @param condition 
 * condition (function pointer)
 *
 * @pre
 * d is not NULL
 *
 * @pre
 * d is not empty
 *
 * @pre
 * condition is not NULL
 *
 * @returns number of elements found
 *
 * @note runtime O(n)
 */
size_t darray_count_elements(darray *d, void *other, bool (*condition)(void *element, void *other), bool hmap);

/**
 * get elements in dynamic array which satisfy specified condition
 *
 * @param d 
 * dynamic array
 *
 * @param other
 * argument to pass to condition function 
 *
 * @param condition 
 * condition (function pointer)
 *
 * @pre
 * d is not NULL
 *
 * @pre
 * d is not empty
 *
 * @pre
 * condition is not NULL
 *
 * @returns a dynamic array filled with the found elements if successful, NULL otherwise
 *
 * @note runtime O(n)
 */
darray *darray_get_elements(darray *d, void *other, bool (*condition)(void *element, void *other));

/**
 * remove elements in dynamic array which satisfy specified condition
 *
 * @param d 
 * dynamic array
 *
 * @param other
 * argument to pass to condition function 
 *
 * @param condition 
 * condition (function pointer)
 *
 * @pre
 * d is not NULL
 *
 * @pre
 * d is not empty
 *
 * @pre
 * condition is not NULL
 *
 * @returns a dynamic array filled with the removed elements if successful, NULL otherwise
 *
 * @note runtime O(n^2)
 */
darray *darray_delete_elements(darray *d, void *other, bool (*condition)(void *element, void *other));

/**
 * reverse dynamic array element-wise
 *
 * @param d 
 * dynamic array
 *
 * @pre
 * d is not NULL
 *
 * @pre
 * d is not empty
 *
 * @returns true if successful, false otherwise
 *
 * @note runtime O(n)
 */
bool darray_reverse(darray *d);

#endif
