#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/log.h"
#include "../include/logic.h"
#include "../include/darray.h"
#include "../include/hmap.h"

darray_iter *darray_iter_create(darray *d)
{
     LOG_ERROR(d != NULL, error, "darray is NULL");

     darray_iter *d_iter = malloc(sizeof(darray_iter));
     LOG_ERROR(d_iter != NULL, error, "failed to malloc darray_iter");
     d_iter->d = d;
     d_iter->i = 0;

     return d_iter;

error:
     return NULL;
}

bool darray_iter_delete(darray_iter **d_iter)
{
     LOG_ERROR(d_iter != NULL, error, "pointer to darray_iter is NULL");
     LOG_ERROR(*d_iter != NULL, error, "darray_iter is NULL");

     free(*d_iter);
     *d_iter = NULL;

     return true;

error:
     return false;
}

bool darray_iter_reset(darray_iter *d_iter)
{
     LOG_ERROR(d_iter != NULL, error, "darray_iter is NULL");
     d_iter->i = 0;

     return true;

error:
     return false;
}

bool darray_iter_has_next(darray_iter *d_iter)
{
     LOG_ERROR(d_iter != NULL, error, "darray_iter is NULL");

     size_t i = d_iter->i;
     void *element = darray_iter_next(d_iter);

     d_iter->i = i;

     return element != NULL;

error:
     return false;
}

void *darray_iter_next(darray_iter *d_iter)
{
     LOG_ERROR(d_iter != NULL, error, "darray_iter is NULL");
     size_t i = d_iter->i, size = d_iter->d->size;

     void *element = NULL;

     if (i >= 0 && i < size) {
	  element = darray_get_element_at_index(d_iter->d, i);
	  d_iter->i = i + 1;
     }

     return element;

error:
     return NULL;
}

darray* darray_create()
{
    darray *d = malloc(sizeof(darray));
    LOG_ERROR(d != NULL, error, "failed to malloc darray")

    d->size = 0;
    d->capacity = 0;
    d->size_of_data = sizeof(void *);
    d->data = NULL;

error:
    return d;
}

bool darray_delete(darray **d)
{
    LOG_ERROR(d != NULL, error, "pointer to darray is NULL");
    LOG_ERROR(*d != NULL, error, "darray is NULL");

    if ((*d)->data != NULL) {
        free((*d)->data);
        (*d)->data = NULL;
    }

    free(*d);
    *d = NULL;

    return true;

error:
    return false;
}

size_t darray_get_size(darray *d)
{
    LOG_ERROR(d != NULL, error, "darray is NULL");

    return d->size;

error:
    return 0;
}

size_t darray_get_capacity(darray *d)
{
    LOG_ERROR(d != NULL, error, "darray is NULL");

    return d->capacity;

error:
    return 0;
}

bool darray_is_empty(darray *d)
{
    LOG_ERROR(d != NULL, error, "darray is NULL");

    if (d->capacity >= 1 && d->size >= 1) {
        return false;
    } 

error:
    return true;
}

bool darray_prepend_element(darray *d, void *element)
{
    bool retval = darray_append_element(d, element);
    LOG_ERROR(retval == true, error, "failed to append element to darray");

    int i = 0;
    for (i = d->size - 1; i >= 1; i--) {
        d->data[i] = d->data[i - 1];
    }
    d->data[0] = element;

    return true;

error:
    return false;
}

bool darray_append_element(darray *d, void *element)
{
    LOG_ERROR(d != NULL, error, "darray is NULL");
    LOG_ERROR(element != NULL, error, "element is NULL");

    if (d->capacity == 0){
        d->size = 0;
        d->capacity = 1;
        d->data = malloc(d->size_of_data);
        LOG_ERROR(d->data != NULL, error, "failed to malloc darray->data");
    } else if (d->size >= d->capacity){
        d->capacity *= 2;
        void *raptr;
        raptr = realloc(d->data, d->size_of_data * d->capacity);
        LOG_ERROR(raptr != NULL, error, "failed to re-alloc darray->data");
        d->data = raptr;
    }
    d->data[d->size] = element;
    d->size++;

    return true;

error:
    return false;
}

bool darray_trim(darray *d)
{
    d->capacity = d->size;
    void *raptr = realloc(d->data, d->size_of_data * d->capacity);
    LOG_ERROR(raptr != NULL, error, "failed to re-alloc darray->data");
    d->data = raptr;

    return true;

error:
    return false;
}

void *darray_delete_front(darray *d)
{
    LOG_ERROR(d != NULL, error, "darray is NULL");
    LOG_ERROR(darray_is_empty(d) == false, error, "darray is empty");

    void *retval = d->data[0];
    if (d->capacity > 1) {
        int i = 0;
        for (i = 0; i < (d->size - 1); i++) {
            d->data[i] = d->data[i + 1];
        }
    }
    if (d->capacity >= 1) {
        bool rv = darray_delete_rear(d);
        LOG_ERROR(rv != false, error, "failed to delete rear of darray");
    }

    return retval;

error:
    return NULL;
}

void *darray_delete_rear(darray *d)
{
    LOG_ERROR(d != NULL, error, "darray is NULL");
    LOG_ERROR(darray_is_empty(d) == false, error, "darray is empty");

    void *retval = d->data[d->size - 1];
    if (d->capacity > 1) {
        d->size--;

        if (d->size >= 2 && (d->size * 2 == d->capacity)) {
            bool is_success = darray_trim(d);
            LOG_ERROR(is_success, error, "failed to trim darray");
        } else if (d->size == 0) {
            free(d->data);
            d->data = NULL;
            d->capacity = 0;
        }
    } else if (d->capacity == 1) {
        d->capacity = 0;
        d->size = 0;
	free(d->data); // FIX MEMORY LEAKS ?
        d->data = NULL;
    }

    return retval;

error:
    return NULL;
}

bool darray_insert_element_at_index(darray *d, void *element, size_t index)
{
    LOG_ERROR(d != NULL, error, "darray is NULL");
    LOG_ERROR(element != NULL, error, "element is NULL");
    LOG_ERROR(IMPLIES(d->size > 0, index <= d->size), error, "index is out of range [0, %lu]", d->size);

    bool retval;

    if (index == 0) {
        retval = darray_prepend_element(d, element);
        LOG_ERROR(retval != false, error, "failed to prepend element '%p' to darray", element);
    } else if (index == d->size) {
        retval = darray_append_element(d, element);
        LOG_ERROR(retval != false, error, "failed to append element '%p' to darray", element);
    } else {
        retval = darray_append_element(d, element);
        LOG_ERROR(retval != false, error, "failed to append element '%p' to darray", element);
        int i = 0;
        for (i = d->size - 1 ; i >= index + 1; i--) {
            d->data[i] = d->data[i - 1];
        }
        d->data[index] = element;
    }

    return retval;

error:
    return false;
}

void *darray_delete_element_at_index(darray *d, size_t index)
{
    LOG_ERROR(d != NULL, error, "darray is NULL");
    LOG_ERROR(darray_is_empty(d) == false, error, "darray is empty");
    LOG_ERROR(index >= 0 && index <= d->size - 1, error, "index is out of range [0, %lu]", d->size - 1);

    void *retval = NULL;
    if (index == 0) {
        retval = darray_delete_front(d);
        LOG_ERROR(retval != false, error, "failed to delete front of darray");
    } else if (index == d->size - 1) {
        retval = darray_delete_rear(d);
        LOG_ERROR(retval != false, error, "failed to delete rear of darray");
    } else {
        int i = 0;
        void *data = darray_get_element_at_index(d, index);
        LOG_ERROR(data != NULL, error, "failed to get element at index '%lu' of darray", index);
        for (i = index; i < d->size - 1; i++) {
            d->data[i] = d->data[i + 1];
        }
        bool rv;
        rv = darray_set_element_at_index(d, data, d->size - 1);
        LOG_ERROR(rv != false, error, "failed to set element '%p' at index '%lu' of darray", data, index);
        retval = darray_delete_rear(d);
        LOG_ERROR(retval != false, error, "failed to delete rear of darray");
    }

    return retval;

error:
    return NULL;
}

void *darray_get_element_at_index(darray *d, size_t index)
{
    LOG_ERROR(d != NULL, error, "darray is NULL");
    LOG_ERROR(darray_is_empty(d) == false, error, "darray is empty");
    LOG_ERROR(index >= 0 && index <= d->size - 1, error, "index is out of range [0, %lu]", d->size - 1);

    return d->data[index];

error:
    return NULL;
}

bool darray_set_element_at_index(darray *d, void* element, size_t index)
{
    LOG_ERROR(d != NULL, error, "darray is NULL");
    LOG_ERROR(element != NULL, error, "element is NULL");
    LOG_ERROR(darray_is_empty(d) == false, error, "darray is empty");
    LOG_ERROR(index >= 0 && index <= d->size - 1, error, "index is out of range [0, %lu]", d->size - 1);

    d->data[index] = element;

    return true;

error:
    return false;
}

size_t darray_count_elements(darray *d, void *other, bool (*condition)(void *element, void *other), bool hmap)
{
     LOG_ERROR(d != NULL, error, "darray is NULL");
     LOG_ERROR(darray_is_empty(d) == false, error, "darray is empty");
     LOG_ERROR(condition != NULL, error, "condition (function pointer) is NULL");

     size_t size = 0;

     darray_iter *d_iter = darray_iter_create(d);
     LOG_ERROR(d_iter != NULL, error, "failed to create darray_iter");

     while (darray_iter_has_next(d_iter)) {
	  void *curr_element = darray_iter_next(d_iter);
	  LOG_ERROR(curr_element != NULL, error, "current element is NULL");
	  if (hmap) {
	       if (condition(((pair *)curr_element)->value, other)) {
		    size++;
	       }
	  } else {
	       if (condition(curr_element, other)) {
		    size++;
	       }
	  }

     }

     bool retval = darray_iter_delete(&d_iter);
     LOG_ERROR(retval == true, error, "failed to delete darray_iter");

     return size;

error:
     return 0;
}

darray *darray_get_elements(darray *d, void *other, bool (*condition)(void *element, void *other))
{
     LOG_ERROR(d != NULL, error, "darray is NULL");
     LOG_ERROR(darray_is_empty(d) == false, error, "darray is empty");
     LOG_ERROR(condition != NULL, error, "condition (function pointer) is NULL");

     bool rv;

     darray *sub_array = darray_create();
     LOG_ERROR(sub_array != NULL, error, "failed to create darray");

     darray_iter *d_iter = darray_iter_create(d);
     LOG_ERROR(d_iter != NULL, error, "failed to create darray_iter");

     while (darray_iter_has_next(d_iter)) {
	  void *curr_element = darray_iter_next(d_iter);
	  LOG_ERROR(curr_element != NULL, error, "current element is NULL");
	  if (condition(curr_element, other)) {
	       rv = darray_append_element(sub_array, curr_element);
	       LOG_ERROR(rv != false, error, "failed to append element '%p' to darray", curr_element);
	  }
     }

     bool retval = darray_iter_delete(&d_iter);
     LOG_ERROR(retval == true, error, "failed to delete darray_iter");

     if (darray_is_empty(sub_array)) {
	  rv = darray_delete(&sub_array);
	  LOG_ERROR(rv = true, error, "failed to free darray");
	  return NULL;
     }

     return sub_array;

error:
     return NULL;
}

darray *darray_delete_elements(darray *d, void *other, bool (*condition)(void *element, void *other))
{
     LOG_ERROR(d != NULL, error, "darray is NULL");
     LOG_ERROR(darray_is_empty(d) == false, error, "darray is empty");
     LOG_ERROR(condition != NULL, error, "condition (function pointer) is NULL");

     void *retval = NULL;
     bool rv;
     bool found = false;
     size_t i = 0, index = 0;

     darray *sub_array = darray_create();
     LOG_ERROR(sub_array != NULL, error, "failed to create darray");

     darray_iter *d_iter = darray_iter_create(d);
     LOG_ERROR(d_iter != NULL, error, "failed to create darray_iter");

     while (!darray_is_empty(d)) {
	  i = 0;
	  index = 0;
	  rv = darray_iter_reset(d_iter);
	  LOG_ERROR(rv == true, error, "failed to reset darray_iter");

	  while (darray_iter_has_next(d_iter)) {
	       void *curr_element = darray_iter_next(d_iter);
	       LOG_ERROR(curr_element != NULL, error, "current element is NULL");
	       if (condition(curr_element, other)) {
		    found = true;
		    index = i;
		    break;
	       }
	       i++;
	  }

	  if (found) {
	       retval = darray_delete_element_at_index(d, index);
	       LOG_ERROR(retval != NULL, error, "failed to delete element at index '%lu' of darray", index);
	       rv = darray_append_element(sub_array, retval);
	       LOG_ERROR(rv != false, error, "failed to append element '%p' to darray", retval);
	       found = false;
	  } else {
	       break;
	  }
     }

     rv = darray_iter_delete(&d_iter);
     LOG_ERROR(rv == true, error, "failed to delete darray_iter");

     if (darray_is_empty(sub_array)) {
	  rv = darray_delete(&sub_array);
	  LOG_ERROR(rv = true, error, "failed to free darray");
	  return NULL;
     }

     return sub_array;

error:
     return NULL;
}

bool darray_reverse(darray *d)
{
    LOG_ERROR(d != NULL, error, "darray is NULL");
    LOG_ERROR(darray_is_empty(d) == false, error, "darray is empty");

    size_t i = 0, j = d->size - 1;
    while (i < j) {
        // eai -> element at i, eaj -> element at j
        void *eai = darray_get_element_at_index(d, i);
        void *eaj = darray_get_element_at_index(d, j);
        bool retval0, retval1;
        retval0 = darray_set_element_at_index(d, eai, j);
        retval1 = darray_set_element_at_index(d, eaj, i);
        LOG_ERROR(retval0 != false && retval1 != false, error, "failed to swap '%p' and '%p' in darray", eai, eaj);
        i++;
        j--;
    }

    return true;

error:
    return false;
}
