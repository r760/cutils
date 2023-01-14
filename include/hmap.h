#ifndef HMAP_H
#define HMAP_H
#include <stdbool.h>
#include "darray.h"

/**
 * definition of a key-value pair
 */
typedef struct
{
     /**
      * key
      */
     void *key;
     /**
      * value
      */
     void *value;
} pair;

/**
 * definition of a hash map
 */
typedef struct
{
     /**
      * size of hash map, ie the number of elements currently contained in hash map
      */
     size_t size;
     /**
      * capacity of hash map, ie the number of elements that can be contained in hash map
      *
      * @note capacity of hash map is dynamically increased/decreased as needed according to load_factor
      */
     size_t capacity;
     /**
      * load_factor of hash map, when (size of hash map / capacity of hash map) >= load factor of hmap, then
      * hmap will be resized to new hash map capacity = (old hash map capactiy) * 2
      */
     double load_factor;
     /**
      * pointer to hash function used by hash map
      */
     unsigned long (*hash)(void *key); 
     /**
      * pointer to equals function for key used by hash map
      */
     bool (*equals_key)(void *this_obj, void *other_obj); 
     /**
      * pointer to equals function for value used by hash map
      */
     bool (*equals_value)(void *this_obj, void *other_obj); 
     /**
      * boolean flag, when true stops hash map from automatically resizing
      */
     bool lock_resize;
     /**
      * size of data in hash map, this is set to the size of void *
      */
     size_t size_of_data;
     /**
      * data held in hash map
      */
     darray **data;
} hmap;

/**
 * definition of a hash map iterator
 */
typedef struct
{
     /**
      * hash map 
      */
     hmap *h;
     /**
      * index of the current bucket of hash map
      */
     size_t i;
     /**
      * index of the current entry in ith bucket of hash map
      */
     size_t j;
} hmap_iter;

/**
 * create a new hash map iterator
 *
 * @param h
 * hash map
 *
 * @pre
 * h is not NULL
 *
 * @returns newly created hash map iterator if successful, NULL otherwise
 *
 */
hmap_iter *hmap_iter_create(hmap *h);

/**
 * delete hash map iterator
 *
 * @param h_iter
 * hash map iterator
 *
 * @pre
 * h_iter is not NULL
 *
 * @pre
 * *h_iter is not NULL
 *
 * @returns true if successful, false otherwise
 *
 */
bool hmap_iter_delete(hmap_iter **h_iter);

/**
 * reset hash map iterator to its initial position
 *
 * @param h_iter
 * hash map iterator
 *
 * @pre
 * h_iter is not NULL
 *
 * @pre
 * *h_iter is not NULL
 *
 * @returns true if successful, false otherwise
 *
 */
bool hmap_iter_reset(hmap_iter *h_iter);

/**
 * check if hash map iterator has another item
 *
 * @param h_iter
 * hash map iterator
 *
 * @pre
 * h_iter is not NULL
 *
 * @pre
 * *h_iter is not NULL
 *
 * @returns true if hash map iterator has another item, false otherwise
 *
 */
bool hmap_iter_has_next(hmap_iter *h_iter);

/**
 * get the next item from the hash map iterator
 *
 * @param h_iter
 * hash map iterator
 *
 * @pre
 * h_iter is not NULL
 *
 * @pre
 * *h_iter is not NULL
 *
 * @returns the next item from the hash map iterator if it has one, NULL otherwise
 *
 */
pair *hmap_iter_next(hmap_iter *h_iter);

/**
 * create a new key-value pair
 *
 * @param key
 * key
 *
 * @param value
 * value
 *
 * @pre
 * key is not NULL
 *
 * @pre
 * value is not NULL
 *
 * @returns newly created key-value pair if successful, NULL otherwise
 *
 */
pair *pair_create(void *key, void *value);

/**
 * delete key-value pair
 *
 * @param p
 * key-value pair
 *
 * @pre
 * p is not NULL
 *
 * @pre
 * *p is not NULL
 *
 * @returns returns true if successful, NULL otherwise
 *
 */
bool pair_delete(pair **p);

/**
 * create a new hash map
 *
 * @returns newly created hash map if successful, NULL otherwise
 *
 * @param capacity
 * initial capacity of hash map
 *
 * @param load_factor
 * load factor of hash map (when hash map size / hash map capacity >= load factor of hash map, the hash map is resized)
 *
 * @param hash
 * hash (function pointer)
 *
 * @param equals_key
 * equals_key (function pointer)
 *
 * @param equals_value
 * equals_value (function pointer)
 *
 * @pre
 * capacity >= 1
 *
 * @pre
 * load_factor > 0 and load_factor <= 1.0
 *
 * @pre
 * hash (function pointer) is not NULL
 *
 * @pre
 * equals_key (function pointer) is not NULL
 *
 * @pre
 * equals_value (function pointer) is not NULL
 *
 */
hmap *hmap_create(size_t capacity, double load_factor,
		  unsigned long (*hash)(void *key),
		  bool (*equals_key)(void *this_obj, void *other_obj),
		  bool (*equals_value)(void *this_obj, void *other_obj));

/**
 * delete hash map
 *
 * @param h 
 * hash map
 *
 * @pre
 * h is not NULL
 *
 * @pre
 * *h is not NULL
 *
 * @returns true if successful, false otherwise
 *
 */
bool hmap_delete(hmap **h);

/**
 * resize hash map
 *
 * @param h 
 * hash map
 *
 * @param new_capacity
 * the new capacity of the hash map
 *
 * @pre
 * h is not NULL
 *
 * @pre
 * new_capacity >= 1
 *
 * @returns true if successful, false otherwise
 */
bool hmap_resize(hmap **h, size_t new_capacity);

/**
 * insert key value into hash map
 *
 * @param h 
 * hash map
 *
 * @param key
 * key
 *
 * @param value
 * the value to insert
 *
 * @pre
 * h is not NULL
 *
 * @pre
 * *h is not NULL
 *
 * @pre
 * key is not NULL
 *
 * @pre
 * value is not NULL
 *
 * @pre
 * hash map does not already contain the key and value pair
 *
 * @returns true if successful, false otherwise
 */
bool hmap_insert_key_value(hmap **h, void *key, void *value);

/**
 * get value corresponding to key in hash map
 *
 * @param h 
 * hash map
 *
 * @param key
 * key
 *
 * @pre
 * h is not NULL
 *
 * @pre
 * key is not NULL
 *
 * @pre
 * hash map contains key
 *
 * @returns value for key in hash map if successful, NULL otherwise
 */
void *hmap_get_value_by_key(hmap *h, void *key);

/**
 * delete key value (pair) by key in hash map
 *
 * @param h 
 * hash map
 *
 * @param key
 * key
 *
 * @pre
 * h is not NULL
 *
 * @pre
 * key is not NULL
 *
 * @pre
 * hash map contains key
 *
 * @returns the deleted key value pair for in hash map if successful, NULL otherwise
 */
pair *hmap_delete_key_value_by_key(hmap *h, void *key);

/**
 * replace value for corresponding key in hash map
 *
 * @param h 
 * hash map
 *
 * @param key
 * key
 *
 * @pre
 * h is not NULL
 *
 * @pre
 * key is not NULL
 *
 * @pre
 * hash map contains key
 *
 * @returns old value for key in hash map if successful, NULL otherwise
 */
void *hmap_replace_value_for_key(hmap *h, void *key, void *value);

/**
 * check if hash map contains key
 *
 * @param h 
 * hash map
 *
 * @param key
 * key
 *
 * @pre
 * h is not NULL
 *
 * @pre
 * key is not NULL
 *
 * @returns true if key is found with hash map, false otherwise
 */
bool hmap_contains_key(hmap *h, void *key);

/**
 * check if hash map contains value
 *
 * @param h 
 * hash map
 *
 * @param value
 * value
 *
 * @pre
 * h is not NULL
 *
 * @pre
 * value is not NULL
 *
 * @returns true if the value is found in the hash map, false otherwise
 */
bool hmap_contains_value(hmap *h, void *value);

/**
 * get size of hash map
 *
 * @param h 
 * hash map
 *
 * @pre
 * h is not NULL
 *
 * @returns the size of hash map if successful, 0 otherwise
 */
size_t hmap_get_size(hmap *h);

/**
 * get capacity of hash map
 *
 * @param h 
 * hash map
 *
 * @pre
 * h is not NULL
 *
 * @returns the capacity of hash map if successful, 0 otherwise
 */
size_t hmap_get_capacity(hmap *h);

/**
 * get current load of hash map
 *
 * @param h 
 * hash map
 *
 * @pre
 * h is not NULL
 *
 * @returns the current load of hash map if successful, 0.0 otherwise
 */
double hmap_get_current_load(hmap *h);

/**
 * get load factor of hash map
 *
 * @param h 
 * hash map
 *
 * @pre
 * h is not NULL
 *
 * @returns the load factor of hash map if successful, 0.0 otherwise
 */
double hmap_get_load_factor(hmap *h);

/**
 * check if hash map is empty
 *
 * @param h 
 * hash map
 *
 * @pre
 * h is not NULL
 *
 * @returns true if hash map is empty, false otherwise
 */
bool hmap_is_empty(hmap *h);

/**
 * hash map string hash function
 */
unsigned long hmap_str_hash(void *key);

/**
 * hash map string equals key function
 */
bool hmap_str_equals_key(void *this_obj, void *other_obj);

/**
 * hash map string equals value function
 */
bool hmap_str_equals_value(void *this_obj, void *other_obj);

#endif
