#include <stdio.h>
#include "../include/log.h"
#include "../include/sllist.h"

node *node_create()
{
    node *n = malloc(sizeof(node));
    LOG_ERROR(n != NULL, "failed to malloc node");

    n->next = NULL;
    n->data = NULL;

error:
    return n;
}

bool node_delete(node **n)
{
    LOG_ERROR(n != NULL, "in: pointer to node is NULL");
    LOG_ERROR(*n != NULL, "in: node is NULL");

    free(*n);
    *n = NULL;

    return true;

error:
    return false;
}

sllist *sllist_create()
{
    node *header = node_create();
    LOG_ERROR(header != NULL, "failed to create node");
    node *trailer = node_create();
    LOG_ERROR(trailer != NULL, "failed to create node");

    sllist *l = malloc(sizeof(sllist));
    LOG_ERROR(l != NULL, "failed to malloc sllist");
    l->header = header;
    l->trailer = trailer;
    l->size = 0;

    return l;

error:
    return NULL;
}

bool sllist_delete(sllist **l)
{
    LOG_ERROR(l != NULL, "in: pointer to sllist is NULL");
    LOG_ERROR(*l != NULL, "in: sllist is NULL");

    free((*l)->header);
    free((*l)->trailer);
    free(*l);
    *l = NULL;

    return true;

error:
    return false;
}

size_t sllist_get_size(sllist *l)
{
    LOG_ERROR(l != NULL, "in: sllist is NULL");

    return l->size;

error:
    return 0;
}

bool sllist_is_empty(sllist *l)
{
    LOG_ERROR(l != NULL, "in: sllist is NULL");

    if (sllist_get_size(l) >= 1) {
        return false;
    }

error:
    return true;
}

node *sllist_get_front(sllist *l)
{
    LOG_ERROR(l != NULL, "in: sllist is NULL");
    LOG_ERROR(sllist_is_empty(l) == false, "sllist is empty");
    LOG_ERROR(l->header != NULL, "in: sllist->header is NULL");
    LOG_ERROR(l->header->next != NULL, "in: sllist->header->next is NULL");

    return l->header->next;

error:
    return NULL;
}

void *sllist_get_front_data(sllist *l)
{
    node *front = sllist_get_front(l);
    LOG_ERROR(front != NULL, "front is NULL");

    return front->data;

error:
    return NULL;
}

node *sllist_get_rear(sllist *l)
{
    LOG_ERROR(l != NULL, "in: sllist is NULL");
    LOG_ERROR(sllist_is_empty(l) == false, "sllist is empty");
    LOG_ERROR(l->trailer != NULL, "in: sllist->trailer is NULL");
    LOG_ERROR(l->trailer->next != NULL, "in: sllist->trailer->next is NULL");

    return l->trailer->next;

error:
    return NULL;
}

void *sllist_get_rear_data(sllist *l)
{
    node *rear = sllist_get_rear(l);
    LOG_ERROR(rear != NULL, "rear is NULL");

    return rear->data;

error:
    return NULL;
}

bool sllist_prepend_element(sllist *l, void *element)
{
    LOG_ERROR(l != NULL, "in: sllist is NULL");
    LOG_ERROR(element != NULL, "in: element is NULL");

    node *n = node_create();
    LOG_ERROR(n != NULL, "failed to create node");
    n->data = element;

    if (sllist_is_empty(l)) {
        l->header->next = n;
        l->trailer->next = n;
    } else {
        n->next = l->header->next;
        l->header->next = n;
    }
    l->size += 1;

    return true;

error:
    return false;
}

bool sllist_append_element(sllist *l, void *element)
{
    LOG_ERROR(l != NULL, "in: sllist is NULL");
    LOG_ERROR(element != NULL, "in: element is NULL");

    node *n = node_create();
    LOG_ERROR(n != NULL, "failed to create node");
    n->data = element;

    if (sllist_is_empty(l)) {
        l->header->next = n;
        l->trailer->next = n;
    } else {
        node *rear = sllist_get_rear(l);
        LOG_ERROR(rear != NULL, "rear is NULL");
        rear->next = n;
        l->trailer->next = n;
    }
    l->size += 1;

    return true;

error:
    return false;
}

void *sllist_delete_front(sllist *l)
{
    LOG_ERROR(l != NULL, "in: sllist is NULL");
    LOG_ERROR(sllist_is_empty(l) == false, "sllist is empty");
    LOG_ERROR(l->header != NULL, "in: sllist->header is NULL");
    LOG_ERROR(l->header->next != NULL, "in: sllist->header->next is NULL");
    LOG_ERROR(l->trailer != NULL, "in: sllist->trailer is NULL");
    LOG_ERROR(l->trailer->next != NULL, "in: sllist->trailer->next is NULL");

    size_t size = sllist_get_size(l);
    node *first = sllist_get_front(l);
    void *retval = first->data;
    LOG_ERROR(retval != NULL, "first->data is NULL");

    if (size == 1) {
        free(first);
        l->header->next = NULL;
        l->trailer->next = NULL;
    } else {
        node *second = first->next;
        free(first);
        l->header->next = second;
    }
    l->size -= 1;

    return retval;

error:
    return NULL;
}

void *sllist_delete_rear(sllist *l)
{
    LOG_ERROR(l != NULL, "in: sllist is NULL");
    LOG_ERROR(sllist_is_empty(l) == false, "sllist is empty");
    LOG_ERROR(l->header != NULL, "in: sllist->header is NULL");
    LOG_ERROR(l->header->next != NULL, "in: sllist->header->next is NULL");
    LOG_ERROR(l->trailer != NULL, "in: sllist->trailer is NULL");
    LOG_ERROR(l->trailer->next != NULL, "in: sllist->trailer->next is NULL");

    size_t size = sllist_get_size(l);
    node *rear = sllist_get_rear(l);
    void *retval = rear->data;
    LOG_ERROR(retval != NULL, "rear->data is NULL");

    if (size == 1) {
        free(rear);
        l->header->next = NULL;
        l->trailer->next = NULL;
    } else {
        node *curr = sllist_get_front(l);
        while (curr->next != rear) {
            curr = curr->next;
        }
        l->trailer->next = curr;
        curr->next = NULL;
        free(rear);
    }
    l->size -= 1;

    return retval;

error:
    return NULL;
}
