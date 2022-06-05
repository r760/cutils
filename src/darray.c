#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/log.h"
#include "../include/darray.h"

darray* darray_create()
{
    darray *d = malloc(sizeof(darray));
    LOG_ERROR(d != NULL, "failed to malloc darray")

    d->size = 0;
    d->capacity = 0;
    d->size_of_data = sizeof(void *);
    d->data = NULL;

error:
    return d;
}

bool darray_delete(darray **d)
{
    LOG_ERROR(d != NULL, "in: pointer to darray is NULL");
    LOG_ERROR(*d != NULL, "in: darray is NULL");

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

bool darray_is_empty(darray *d)
{
    LOG_ERROR(d != NULL, "in: darray is NULL");

    if (d->capacity >= 1 && d->size >= 1) {
        return false;
    } 

error:
    return true;
}

bool darray_append_element(darray *d, void *element)
{
    LOG_ERROR(d != NULL, "in: darray is NULL");
    LOG_ERROR(element != NULL, "in: element is NULL");

    if (d->capacity == 0){
        d->size = 0;
        d->capacity = 1;
        d->data = malloc(d->size_of_data);
        LOG_ERROR(d->data != NULL, "failed to malloc darray->data");
    } else if (d->size >= d->capacity){
        d->capacity *= 2;
        void *raptr;
        raptr = realloc(d->data, d->size_of_data * d->capacity);
        LOG_ERROR(raptr != NULL, "failed to re-alloc darray->data");
        d->data = raptr;
    }
    d->data[d->size] = element;
    d->size++;

    return true;

error:
    return false;
}

bool darray_prepend_element(darray *d, void *element)
{
    bool retval = darray_append_element(d, element);
    LOG_ERROR(retval == true, "failed to append element to darray");

    int i = 0;
    for (i = d->size - 1; i >= 1; i--) {
        d->data[i] = d->data[i - 1];
    }
    d->data[0] = element;

    return true;

error:
    return false;
}

bool trim(darray *d)
{
    d->capacity = d->size;
    void *raptr = realloc(d->data, d->size_of_data * d->capacity);
    LOG_ERROR(raptr != NULL, "failed to re-alloc darray->data");
    d->data = raptr;

    return true;

error:
    return false;
}

void *darray_delete_rear(darray *d)
{
    LOG_ERROR(d != NULL, "in: darray is NULL");
    LOG_ERROR(darray_is_empty(d) == false, "darray is empty");

    void *retval = d->data[d->size - 1];
    if (d->capacity > 1) {
        d->size--;

        if (d->size >= 2 && (d->size * 2 == d->capacity)) {
            bool is_success = trim(d);
            LOG_ERROR(is_success, "failed to trim darray");
        } else if (d->size == 0) {
            free(d->data);
            d->data = NULL;
            d->capacity = 0;
        }
    } else if (d->capacity == 1) {
        d->capacity = 0;
        d->size = 0;
        d->data = NULL;
    }

    return retval;

error:
    return NULL;
}

void *darray_delete_front(darray *d)
{
    LOG_ERROR(d != NULL, "in: darray is NULL");
    LOG_ERROR(darray_is_empty(d) == false, "darray is empty");

    void *retval = d->data[0];
    if (d->capacity > 1) {
        int i = 0;
        for (i = 0; i < (d->size - 1); i++) {
            d->data[i] = d->data[i + 1];
        }
    }
    if (d->capacity >= 1) {
        bool rv = darray_delete_rear(d);
        LOG_ERROR(rv != false, "failed to delete rear of darray");
    }

    return retval;

error:
    return NULL;
}

bool darray_insert_element_at_index(darray *d, void *element, size_t index)
{
    LOG_ERROR(d != NULL, "in: darray is NULL");
    LOG_ERROR(element != NULL, "in: element is NULL");
    LOG_ERROR(darray_is_empty(d) == false, "darray is empty");
    LOG_ERROR(index >= 0 && index <= d->size - 1, "in: index is out of range [0, %lu]", d->size - 1);

    bool retval;

    if (index == 0) {
        retval = darray_prepend_element(d, element);
        LOG_ERROR(retval != false, "failed to prepend element '%p' to darray", element);
    } else if (index == d->size) {
        retval = darray_append_element(d, element);
        LOG_ERROR(retval != false, "failed to append element '%p' to darray", element);
    } else {
        retval = darray_append_element(d, element);
        LOG_ERROR(retval != false, "failed to append element '%p' to darray", element);
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

void *darray_delete_at_index(darray *d, size_t index)
{
    LOG_ERROR(d != NULL, "in: darray is NULL");
    LOG_ERROR(darray_is_empty(d) == false, "darray is empty");
    LOG_ERROR(index >= 0 && index <= d->size - 1, "in: index is out of range [0, %lu]", d->size - 1);

    void *retval = NULL;
    if (index == 0) {
        retval = darray_delete_front(d);
        LOG_ERROR(retval != false, "failed to delete front of darray");
    } else if (index == d->size - 1) {
        retval = darray_delete_rear(d);
        LOG_ERROR(retval != false, "failed to delete rear of darray");
    } else {
        int i = 0;
        for (i = index; i < d->size - 1; i++) {
            d->data[i] = d->data[i + 1];
        }
        retval = darray_delete_rear(d);
        LOG_ERROR(retval != false, "failed to delete rear of darray");
    }

    return retval;

error:
    return NULL;
}

void *darray_get_element_at_index(darray *d, size_t index)
{
    LOG_ERROR(d != NULL, "in: darray is NULL");
    LOG_ERROR(darray_is_empty(d) == false, "darray is empty");
    LOG_ERROR(index >= 0 && index <= d->size - 1, "in: index is out of range [0, %lu]", d->size - 1);

    return d->data[index];

error:
    return NULL;
}

bool darray_set_element_at_index(darray *d, void* element, size_t index)
{
    LOG_ERROR(d != NULL, "index: darray is NULL");
    LOG_ERROR(element != NULL, "in: element is NULL");
    LOG_ERROR(darray_is_empty(d) == false, "darray is empty");
    LOG_ERROR(index >= 0 && index <= d->size - 1, "in: index is out of range [0, %lu]", d->size - 1);

    d->data[index] = element;

    return true;

error:
    return false;
}

bool darray_reverse(darray *d)
{
    LOG_ERROR(d != NULL, "index: darray is NULL");
    LOG_ERROR(darray_is_empty(d) == false, "darray is empty");

    size_t i = 0, j = d->size - 1;
    while (i < j) {
        // eai -> element at i, eaj -> element at j
        void *eai = darray_get_element_at_index(d, i);
        void *eaj = darray_get_element_at_index(d, j);
        bool retval0, retval1;
        retval0 = darray_set_element_at_index(d, eai, j);
        retval1 = darray_set_element_at_index(d, eaj, i);
        LOG_ERROR(retval0 != false && retval1 != false, "failed to swap '%p' and '%p' in darray", eai, eaj);
        i++;
        j--;
    }

    return true;

error:
    return false;
}

size_t darray_get_size(darray *d)
{
    LOG_ERROR(d != NULL, "in: darray is NULL");
error:
    return d->size;
}

size_t darray_get_capacity(darray *d)
{
    LOG_ERROR(d != NULL, "in: darray is NULL");
error:
    return d->capacity;
}
