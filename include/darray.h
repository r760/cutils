#ifndef DARRAY_H
#define DARRAY_H
#include <stdbool.h>
#include <stdlib.h>

typedef struct
{
     size_t size;
     size_t capacity;
     size_t size_of_data;
     void **data;
} darray;

typedef struct
{
     darray *d;
     size_t i;
} darray_iter;

darray_iter *darray_iter_create(darray *d);

bool darray_iter_delete(darray_iter **d_iter);

bool darray_iter_reset(darray_iter *d_iter);

bool darray_iter_has_next(darray_iter *d_iter);

void *darray_iter_next(darray_iter *d_iter);

darray* darray_create();

bool darray_delete(darray **d);

size_t darray_get_size(darray *d);

size_t darray_get_capacity(darray *d);

bool darray_is_empty(darray *d);

bool darray_prepend_element(darray *d, void *element);

bool darray_append_element(darray *d, void *element);

void *darray_delete_front(darray *d);

void *darray_delete_rear(darray *d);

bool darray_insert_element_at_index(darray *d, void *element, size_t index);

void *darray_delete_element_at_index(darray *d, size_t index);

void *darray_get_element_at_index(darray *d, size_t index);

bool darray_set_element_at_index(darray *d, void* element, size_t index);

size_t darray_count_elements(darray *d, void *other, bool (*condition)(void *element, void *other), bool hmap);

darray *darray_get_elements(darray *d, void *other, bool (*condition)(void *element, void *other));

darray *darray_delete_elements(darray *d, void *other, bool (*condition)(void *element, void *other));

bool darray_reverse(darray *d);

#endif
