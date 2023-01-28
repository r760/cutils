#ifndef HMAP_H
#define HMAP_H
#include <stdbool.h>
#include "darray.h"

typedef struct
{
     void *key;
     void *value;
} pair;

typedef struct
{
     size_t size;
     size_t capacity;
     double load_factor;
     unsigned long (*hash)(void *key); 
     bool (*equals_key)(void *this_obj, void *other_obj); 
     bool (*equals_value)(void *this_obj, void *other_obj); 
     bool lock_resize;
     size_t size_of_data;
     darray **data;
} hmap;

typedef struct
{
     hmap *h;
     size_t i;
     size_t j;
} hmap_iter;

hmap_iter *hmap_iter_create(hmap *h);

bool hmap_iter_delete(hmap_iter **h_iter);

bool hmap_iter_reset(hmap_iter *h_iter);

bool hmap_iter_has_next(hmap_iter *h_iter);

pair *hmap_iter_next(hmap_iter *h_iter);

pair *pair_create(void *key, void *value);

bool pair_delete(pair **p);

hmap *hmap_create(size_t capacity, double load_factor,
		  unsigned long (*hash)(void *key),
		  bool (*equals_key)(void *this_obj, void *other_obj),
		  bool (*equals_value)(void *this_obj, void *other_obj));

bool hmap_delete(hmap **h);

bool hmap_resize(hmap **h, size_t new_capacity);

bool hmap_insert_key_value(hmap **h, void *key, void *value);

void *hmap_get_value_by_key(hmap *h, void *key);

pair *hmap_delete_key_value_by_key(hmap *h, void *key);

void *hmap_replace_value_for_key(hmap *h, void *key, void *value);

bool hmap_contains_key(hmap *h, void *key);

bool hmap_contains_value(hmap *h, void *value);

size_t hmap_get_size(hmap *h);

size_t hmap_get_capacity(hmap *h);

double hmap_get_current_load(hmap *h);

double hmap_get_load_factor(hmap *h);

bool hmap_is_empty(hmap *h);

unsigned long hmap_str_hash(void *key);

bool hmap_str_equals_key(void *this_obj, void *other_obj);

bool hmap_str_equals_value(void *this_obj, void *other_obj);

#endif
