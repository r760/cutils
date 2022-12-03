#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "../include/darray.h"
#include "../include/hmap.h"
#include "../include/log.h"

hmap_iter *hmap_iter_create(hmap *h)
{
     LOG_ERROR(h != NULL, error, "hmap is NULL");

     hmap_iter *h_iter = malloc(sizeof(hmap_iter));
     LOG_ERROR(h_iter != NULL, error, "failed to malloc hmap_iter");
     h_iter->h = h;
     h_iter->i = 0;
     h_iter->j = 0;

     return h_iter;

error:
     return NULL;
}

bool hmap_iter_delete(hmap_iter **h_iter)
{
     LOG_ERROR(h_iter != NULL, error, "pointer to hmap_iter is NULL");
     LOG_ERROR(*h_iter != NULL, error, "hmap_iter is NULL");

     free(*h_iter);
     *h_iter = NULL;

     return true;

error:
     return false;
}

bool hmap_iter_reset(hmap_iter *h_iter)
{
     LOG_ERROR(h_iter != NULL, error, "hmap_iter is NULL");
     h_iter->i = 0;
     h_iter->j = 0;

     return true;

error:
     return false;
}

bool hmap_iter_has_next(hmap_iter *h_iter)
{
     LOG_ERROR(h_iter != NULL, error, "hmap_iter is NULL");

     size_t i = h_iter->i, j = h_iter->j;
     pair *p = hmap_iter_next(h_iter);

     h_iter->i = i;
     h_iter->j = j;

     return p != NULL;

error:
     return false;
}

pair *hmap_iter_next(hmap_iter *h_iter)
{
     LOG_ERROR(h_iter != NULL, error, "hmap_iter is NULL");

     hmap *h = h_iter->h;
     size_t i = h_iter->i, j = h_iter->j, capacity = h->capacity;

     for (; i >= 0 && i < capacity; i++) {
	  darray *d = h->data[i];
	  if (d != NULL && j >= 0 && j < d->size) {
	       pair *p = darray_get_element_at_index(d, j);
	       h_iter->i = i;
	       h_iter->j = j + 1;
	       return p;
	  } else {
	       j = 0; 
	  }
     }

error:
     return NULL;
}

pair *pair_create(void *key, void *value)
{
     LOG_ERROR(key != NULL, error, "key is NULL");
     LOG_ERROR(value != NULL, error, "value is NULL");

     pair *p = malloc(sizeof(pair));
     LOG_ERROR(p != NULL, error, "failed to malloc pair");
     p->key = key;
     p->value = value;

error:
     return p;
}

bool pair_delete(pair **p)
{
     LOG_ERROR(p != NULL, error, "pointer to pair is NULL");
     LOG_ERROR(*p != NULL, error, "pair is NULL");

     free(*p);
     *p = NULL;

     return true;

error:
     return false;
}

hmap *hmap_create(size_t capacity, double load_factor,
		  unsigned long (*hash)(void *key),
		  bool (*equals_key)(void *this_obj, void *other_obj),
		  bool (*equals_value)(void *this_obj, void *other_obj))
{
     LOG_ERROR(capacity >= 1, error, "capacity is less then one");
     LOG_ERROR(load_factor > 0 && load_factor <= 1, error, "load_factor out of range (0, 1]");
     LOG_ERROR(hash != NULL, error, "hash function pointer is NULL");
     LOG_ERROR(equals_key != NULL, error, "equals_key function pointer is NULL");
     LOG_ERROR(equals_value != NULL, error, "equals_value function pointer is NULL");

     hmap *h = malloc(sizeof(hmap));
     LOG_ERROR(h != NULL, error, "failed to malloc hmap");
     h->size = 0;
     h->capacity = capacity;
     h->load_factor = load_factor;
     h->hash = hash;
     h->equals_key = equals_key;
     h->equals_value = equals_value;
     h->lock_resize = false;
     h->size_of_data = sizeof(darray*);
     h->data = malloc(h->size_of_data * h->capacity);
     for (size_t i = 0; i < capacity; i++) {
	  h->data[i] = NULL;
     }
     LOG_ERROR(h->data != NULL, error, "failed to malloc hmap->data");
     return h;

error:
     return NULL;
}

bool hmap_delete(hmap **h)
{
     LOG_ERROR(h != NULL, error, "pointer to hmap is NULL");
     LOG_ERROR(*h != NULL, error, "hmap is NULL");

     hmap_iter *h_iter = hmap_iter_create(*h);
     LOG_ERROR(h_iter != NULL, error, "failed to create hmap_iter");

     bool retval;
     
     while (hmap_iter_has_next(h_iter)) {
	  pair *curr_element = hmap_iter_next(h_iter);
	  LOG_ERROR(curr_element != NULL, error, "current element is NULL");

	  pair *p = curr_element;
	  retval = pair_delete(&p);
	  LOG_ERROR(retval == true, error, "failed to delete pair");
     }

     retval = hmap_iter_delete(&h_iter);
     LOG_ERROR(retval == true, error, "failed to delete hmap_iter");

     for (size_t i = 0; i < hmap_get_capacity(*h); i++) {
	  darray *d = (*h)->data[i];
	  if (d != NULL) {
	       retval = darray_delete(&d); 
	       LOG_ERROR(retval == true, error, "failed to delete darray");
	  }
     }

     if ((*h)->data != NULL) {
	  free((*h)->data);
	  (*h)->data = NULL;
     }

     free(*h);
     *h = NULL;

     return true;

error:
     return false;
}

bool hmap_resize(hmap **h, size_t new_capacity)
{
     LOG_ERROR(h != NULL, error, "pointer to hmap is NULL");
     LOG_ERROR(*h != NULL, error, "hmap is NULL");
     LOG_ERROR(new_capacity >= 1, error, "new_capacity out of range [1, Inf)");

     hmap *nh = hmap_create(new_capacity, (*h)->load_factor, (*h)->hash, (*h)->equals_key, (*h)->equals_value);
     LOG_ERROR(nh != NULL, error, "failed to create hmap");

     (*h)->lock_resize = true;
     nh->lock_resize = true;

     hmap_iter *h_iter = hmap_iter_create(*h);
     LOG_ERROR(h_iter != NULL, error, "failed to create hmap_iter");

     bool retval;
     
     while (hmap_iter_has_next(h_iter)) {
	  void *curr_element = hmap_iter_next(h_iter);
	  LOG_ERROR(curr_element != NULL, error, "current element is NULL");

	  pair *p = curr_element;
	  retval = hmap_insert_key_value(&nh, p->key, p->value);
	  LOG_ERROR(retval == true, error, "failed to insert key value into hmap");
     }

     (*h)->lock_resize = false;
     nh->lock_resize = false;

     retval = hmap_iter_delete(&h_iter);
     LOG_ERROR(retval == true, error, "failed to delete hmap_iter");

     retval = hmap_delete(h);
     LOG_ERROR(retval == true, error, "failed to delete hmap");

     *h = nh;

     return true;

error:
     return false;
}

bool hmap_insert_key_value(hmap **h, void *key, void *value)
{
     LOG_ERROR(h != NULL, error, "pointer to hmap is NULL");
     LOG_ERROR(*h != NULL, error, "hmap is NULL");
     LOG_ERROR(key != NULL, error, "key is NULL");
     LOG_ERROR(value != NULL, error, "value is NULL");

     unsigned long hash = (*h)->hash(key);
     hash = hash % (*h)->capacity;

     bool retval;

     LOG_ERROR(hash >= 0 && hash <= (*h)->capacity - 1, error, "hash out of range [0, %lu]", (*h)->capacity - 1);

     if ((*h)->data[hash] == NULL) {
	  darray *d = darray_create();
	  LOG_ERROR(d != NULL, error, "failed to create darray");
	  (*h)->data[hash] = d;
     }

     darray *d = (*h)->data[hash];
     LOG_ERROR(d != NULL, error, "darray is NULL");

     pair *p = pair_create(key, value);
     LOG_ERROR(p != NULL, error, "pair is NULL");

     if (darray_is_empty(d)) {
	  retval = darray_append_element(d, p); 
	  LOG_ERROR(retval != false, error, "failed to append element '%p' to darray", p);
	  (*h)->size = (*h)->size + 1;
     } else {
	  bool rv = hmap_contains_key(*h, key);
	  LOG_ERROR(rv == false, error, "hmap already contains key '%p'", key);
	  retval = darray_append_element(d, p); 
	  LOG_ERROR(retval != false, error, "failed to append element '%p' to darray", p);
	  (*h)->size = (*h)->size + 1;
     }

     size_t size = hmap_get_size(*h);
     size_t capacity = hmap_get_capacity(*h);
     double load_factor = hmap_get_load_factor(*h);
     double current_load = (double) size / (double) capacity;

     if ((*h)->lock_resize == false && current_load >= load_factor) {
	  bool rv = hmap_resize(h, capacity * 2);
	  LOG_ERROR(rv == true, error, "failed to resize hmap");
     }

     return true;
     
error:
     return false;
}

void *hmap_get_value_by_key(hmap *h, void *key)
{
     LOG_ERROR(h != NULL, error, "hmap is NULL");
     LOG_ERROR(key != NULL, error, "key is NULL");

     unsigned long hash = h->hash(key);
     hash = hash % h->capacity;
     LOG_ERROR(hash >= 0 && hash <= h->capacity - 1, error, "hash out of range [0, %lu]", h->capacity - 1);

     if (h->data[hash] != NULL) {
	  darray *d = h->data[hash];

	  darray_iter *d_iter = darray_iter_create(d);
	  LOG_ERROR(d_iter != NULL, error, "failed to create darray_iter");

	  while (darray_iter_has_next(d_iter)) {
	       void *curr_element = darray_iter_next(d_iter);
	       LOG_ERROR(curr_element != NULL, error, "current element is NULL");

	       pair *p = curr_element;

	       if (h->equals_key(p->key, key)) {
		    bool retval = darray_iter_delete(&d_iter);
		    LOG_ERROR(retval == true, error, "failed to delete darray_iter");
		    return p->value;
	       }
	  }

	  bool retval = darray_iter_delete(&d_iter);
	  LOG_ERROR(retval == true, error, "failed to delete darray_iter");
     }

error:
     return NULL;
}

pair *hmap_delete_key_value_by_key(hmap *h, void *key)
{
     LOG_ERROR(h != NULL, error, "hmap is NULL");
     LOG_ERROR(key != NULL, error, "key is NULL");

     unsigned long hash = h->hash(key);
     hash = hash % h->capacity;
     LOG_ERROR(hash >= 0 && hash <= h->capacity - 1, error, "hash out of range [0, %lu]", h->capacity - 1);

     darray *d = h->data[hash];
     LOG_ERROR(d != NULL, error, "darray is NULL");

     bool is_empty = darray_is_empty(d);
     LOG_ERROR(is_empty == false, error, "darray is empty");
     
     size_t i = 0, index = 0;
     bool found = false;
     pair *p = NULL;

     darray_iter *d_iter = darray_iter_create(d);
     LOG_ERROR(d_iter != NULL, error, "failed to create darray_iter");

     while (darray_iter_has_next(d_iter)) {
	  void *curr_element = darray_iter_next(d_iter);
	  LOG_ERROR(curr_element != NULL, error, "current element is NULL");

	  p = curr_element;
	  if (h->equals_key(p->key, key)) {
	       index = i;
	       found = true;
	       break;
	  }
	  i++;
     }

     bool rv = darray_iter_delete(&d_iter);
     LOG_ERROR(rv == true, error, "failed to delete darray_iter");

     LOG_ERROR(found == true, error, "hmap does not contain key '%p'", key);
     p = darray_delete_element_at_index(d, index);
     LOG_ERROR(p != NULL, error, "failed to delete element at index '%lu' of darray", index);

     h->size = h->size - 1;
     return p;

error:
     return NULL;
}

void *hmap_replace_value_for_key(hmap *h, void *key, void *value)
{
     LOG_ERROR(h != NULL, error, "hmap is NULL");
     LOG_ERROR(key != NULL, error, "key is NULL");
     LOG_ERROR(value != NULL, error, "value is NULL");

     unsigned long hash = h->hash(key);
     hash = hash % h->capacity;
     LOG_ERROR(hash >= 0 && hash <= h->capacity - 1, error, "hash out of range [0, %lu]", h->capacity - 1);

     if (h->data[hash] != NULL) {
	  darray *d = h->data[hash];

	  darray_iter *d_iter = darray_iter_create(d);
	  LOG_ERROR(d_iter != NULL, error, "failed to create darray_iter");

	  while (darray_iter_has_next(d_iter)) {
	       void *curr_element = darray_iter_next(d_iter);
	       LOG_ERROR(curr_element != NULL, error, "current element is NULL");

	       pair *p = curr_element;
	       if (h->equals_key(p->key, key)) {
		    void *old_value = p->value;
		    LOG_ERROR(old_value != NULL, error, "failed to get value from pair");
		    p->value = value;
		    bool retval = darray_iter_delete(&d_iter);
		    LOG_ERROR(retval == true, error, "failed to delete darray_iter");
		    return old_value;
	       }
	  }

	  bool retval = darray_iter_delete(&d_iter);
	  LOG_ERROR(retval == true, error, "failed to delete darray_iter");
     }

     LOG_ERROR(1 == 2, error, "failed to find key '%p' in hmap", key);

error:
     return NULL;
}

bool hmap_contains_key(hmap *h, void *key)
{
     return hmap_get_value_by_key(h, key) != NULL;
}

bool hmap_contains_value(hmap *h, void *value)
{
     LOG_ERROR(h != NULL, error, "hmap is NULL");
     LOG_ERROR(value != NULL, error, "value is NULL");

     for (size_t i = 0; i < h->capacity; i++) {
	  darray *d = h->data[i];
	  if (d != NULL && !darray_is_empty(d)) {
	       size_t count = darray_count_elements(d, value, h->equals_value, true);
	       if (count >= 1) {
		    return true; 
	       }
	  }
     }

error:
     return false;
}

// get key set
// get value set

size_t hmap_get_size(hmap *h)
{
     LOG_ERROR(h != NULL, error, "hmap is NULL");
     return h->size;

error:
     return 0;
}

size_t hmap_get_capacity(hmap *h)
{
     LOG_ERROR(h != NULL, error, "hmap is NULL");
     return h->capacity;

error:
     return 0;
}

double hmap_get_load_factor(hmap *h)
{
     LOG_ERROR(h != NULL, error, "hmap is NULL");
     return h->load_factor;

error:
     return 0;
}

bool hmap_is_empty(hmap *h)
{
     LOG_ERROR(h != NULL, error, "hmap is NULL");

     if (h->capacity >= 1 && h->size >= 1) {
	  return false;
     } 

error:
     return true;
}

unsigned long hmap_str_hash(void *key)
{
     LOG_ERROR(key != NULL, error, "key is NULL");

     char *str = (char *) key;
     unsigned long hash = 5381;
     int c;

     while (c = *str++)
	  hash = ((hash << 5) + hash) + c;

     return hash;

error:
     return 0;
}

bool hmap_str_equals_key(void *this_obj, void *other_obj)
{
     LOG_ERROR(this_obj != NULL, error, "this_obj is NULL");
     LOG_ERROR(other_obj != NULL, error, "other_obj is NULL");

     return strcmp((char *)this_obj, (char *)other_obj) == 0;

error:
     return false;
}

bool hmap_str_equals_value(void *this_obj, void *other_obj)
{
     LOG_ERROR(this_obj != NULL, error, "this_obj is NULL");
     LOG_ERROR(other_obj != NULL, error, "other_obj is NULL");

     return strcmp((char *)this_obj, (char *)other_obj) == 0;

error:
     return false;
}
