#include <stdio.h>
#include "../include/log.h"
#include "../include/sllist.h"

node *node_create()
{
    node *n = malloc(sizeof(node));
    LOG_ERROR(n != NULL, error, "failed to malloc node");

    n->next = NULL;
    n->data = NULL;

error:
    return n;
}

bool node_delete(node **n)
{
    LOG_ERROR(n != NULL, error, "pointer to node is NULL");
    LOG_ERROR(*n != NULL, error, "node is NULL");

    free(*n);
    *n = NULL;

    return true;

error:
    return false;
}

sllist *sllist_create()
{
    node *header = node_create();
    LOG_ERROR(header != NULL, error, "failed to create node");
    node *trailer = node_create();
    LOG_ERROR(trailer != NULL, error, "failed to create node");

    sllist *l = malloc(sizeof(sllist));
    LOG_ERROR(l != NULL, error, "failed to malloc sllist");
    l->header = header;
    l->trailer = trailer;
    l->size = 0;

    return l;

error:
    return NULL;
}

bool sllist_delete(sllist **l)
{
    LOG_ERROR(l != NULL, error, "pointer to sllist is NULL");
    LOG_ERROR(*l != NULL, error, "sllist is NULL");

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
    LOG_ERROR(l != NULL, error, "sllist is NULL");

    return l->size;

error:
    return 0;
}

bool sllist_is_empty(sllist *l)
{
    LOG_ERROR(l != NULL, error, "sllist is NULL");

    if (sllist_get_size(l) >= 1) {
        return false;
    }

error:
    return true;
}

node *sllist_get_front(sllist *l)
{
    LOG_ERROR(l != NULL, error, "sllist is NULL");
    LOG_ERROR(sllist_is_empty(l) == false, error, "sllist is empty");
    LOG_ERROR(l->header != NULL, error, "sllist->header is NULL");
    LOG_ERROR(l->header->next != NULL, error, "sllist->header->next is NULL");

    return l->header->next;

error:
    return NULL;
}

void *sllist_get_front_data(sllist *l)
{
    node *front = sllist_get_front(l);
    LOG_ERROR(front != NULL, error, "front is NULL");

    return front->data;

error:
    return NULL;
}

node *sllist_get_rear(sllist *l)
{
    LOG_ERROR(l != NULL, error, "sllist is NULL");
    LOG_ERROR(sllist_is_empty(l) == false, error, "sllist is empty");
    LOG_ERROR(l->trailer != NULL, error, "sllist->trailer is NULL");
    LOG_ERROR(l->trailer->next != NULL, error, "sllist->trailer->next is NULL");

    return l->trailer->next;

error:
    return NULL;
}

void *sllist_get_rear_data(sllist *l)
{
    node *rear = sllist_get_rear(l);
    LOG_ERROR(rear != NULL, error, "rear is NULL");

    return rear->data;

error:
    return NULL;
}

bool sllist_prepend_element(sllist *l, void *element)
{
    LOG_ERROR(l != NULL, error, "sllist is NULL");
    LOG_ERROR(element != NULL, error, "element is NULL");

    node *n = node_create();
    LOG_ERROR(n != NULL, error, "failed to create node");
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
    LOG_ERROR(l != NULL, error, "sllist is NULL");
    LOG_ERROR(element != NULL, error, "element is NULL");

    node *n = node_create();
    LOG_ERROR(n != NULL, error, "failed to create node");
    n->data = element;

    if (sllist_is_empty(l)) {
        l->header->next = n;
        l->trailer->next = n;
    } else {
        node *rear = sllist_get_rear(l);
        LOG_ERROR(rear != NULL, error, "rear is NULL");
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
    LOG_ERROR(l != NULL, error, "sllist is NULL");
    LOG_ERROR(sllist_is_empty(l) == false, error, "sllist is empty");
    LOG_ERROR(l->header != NULL, error, "sllist->header is NULL");
    LOG_ERROR(l->header->next != NULL, error, "sllist->header->next is NULL");
    LOG_ERROR(l->trailer != NULL, error, "sllist->trailer is NULL");
    LOG_ERROR(l->trailer->next != NULL, error, "sllist->trailer->next is NULL");

    size_t size = sllist_get_size(l);
    node *first = sllist_get_front(l);
    void *retval = first->data;
    LOG_ERROR(retval != NULL, error, "first->data is NULL");

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
    LOG_ERROR(l != NULL, error, "sllist is NULL");
    LOG_ERROR(sllist_is_empty(l) == false, error, "sllist is empty");
    LOG_ERROR(l->header != NULL, error, "sllist->header is NULL");
    LOG_ERROR(l->header->next != NULL, error, "sllist->header->next is NULL");
    LOG_ERROR(l->trailer != NULL, error, "sllist->trailer is NULL");
    LOG_ERROR(l->trailer->next != NULL, error, "sllist->trailer->next is NULL");

    size_t size = sllist_get_size(l);
    node *rear = sllist_get_rear(l);
    void *retval = rear->data;
    LOG_ERROR(retval != NULL, error, "rear->data is NULL");

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

size_t sllist_count_elements(sllist *l, void *other, bool (*condition)(void *element, void *other))
{
     LOG_ERROR(l != NULL, error, "sllist is NULL");
     LOG_ERROR(sllist_is_empty(l) == false, error, "sllist is empty");
     LOG_ERROR(l->header != NULL, error, "sllist->header is NULL");
     LOG_ERROR(l->header->next != NULL, error, "sllist->header->next is NULL");
     LOG_ERROR(l->trailer != NULL, error, "sllist->trailer is NULL");
     LOG_ERROR(l->trailer->next != NULL, error, "sllist->trailer->next is NULL");

     size_t size = 0;

     SLLIST_FOR_EACH(curr, l) {
	  if (condition(curr->data, other)) {
	       size++;
	  }
     }

     return size;

error:
     return 0;
}

sllist *sllist_get_elements(sllist *l, void *other, bool (*condition)(void *element, void *other))
{
     LOG_ERROR(l != NULL, error, "sllist is NULL");
     LOG_ERROR(sllist_is_empty(l) == false, error, "sllist is empty");
     LOG_ERROR(l->header != NULL, error, "sllist->header is NULL");
     LOG_ERROR(l->header->next != NULL, error, "sllist->header->next is NULL");
     LOG_ERROR(l->trailer != NULL, error, "sllist->trailer is NULL");
     LOG_ERROR(l->trailer->next != NULL, error, "sllist->trailer->next is NULL");

     bool rv ;
     sllist *sub_list = sllist_create();
     LOG_ERROR(sub_list != NULL, error, "failed to create sllist");

     SLLIST_FOR_EACH(curr, l) {
	  if (condition(curr->data, other)) {
	       rv = sllist_append_element(sub_list, curr->data);
	       LOG_ERROR(rv != false, error, "failed to append element '%p' to sllist", curr->data);
	  }
     }

     if (sllist_is_empty(sub_list)) {
	  rv = sllist_delete(&sub_list);
	  LOG_ERROR(rv = true, error, "failed to free sllist");
	  return NULL;
     }

     return sub_list;

error:
     return NULL;
}

static void *sllist_delete_element(sllist *l, void *other, bool (*condition)(void *element, void *other))
{
    LOG_ERROR(l != NULL, error, "sllist is NULL");
    LOG_ERROR(sllist_is_empty(l) == false, error, "sllist is empty");
    LOG_ERROR(l->header != NULL, error, "sllist->header is NULL");
    LOG_ERROR(l->header->next != NULL, error, "sllist->header->next is NULL");
    LOG_ERROR(l->trailer != NULL, error, "sllist->trailer is NULL");
    LOG_ERROR(l->trailer->next != NULL, error, "sllist->trailer->next is NULL");

    void *retval = NULL;
    node *curr = sllist_get_front(l), *before = NULL;
    LOG_ERROR(curr != NULL, error, "failed to get front of sllist");

    if (condition(curr->data, other)) {
	 retval = sllist_delete_front(l);
	 LOG_ERROR(retval != NULL, error, "failed to delete front of sllist");
    } else {
	 before = curr;
	 curr = curr->next;

	 while (curr != NULL) {
	      if (condition(curr->data, other)) {
		   if (curr->next == NULL) {
			retval = sllist_delete_rear(l);
			LOG_ERROR(retval != NULL, error, "failed to delete rear of sllist");
		   } else {
			node *temp = curr;
			retval = curr->data;
			before->next = curr->next;
			node_delete(&temp);
			l->size--;
			LOG_ERROR(retval != NULL, error, "failed to free delete node of sllist");
		   }
		   break;
	      }

	      before = curr;
	      curr = curr->next;
	 }
    }

    return retval;

error:
    return NULL;
}

sllist *sllist_delete_elements(sllist *l, void *other, bool (*condition)(void *element, void *other))
{
     LOG_ERROR(l != NULL, error, "sllist is NULL");
     LOG_ERROR(sllist_is_empty(l) == false, error, "sllist is empty");
     LOG_ERROR(l->header != NULL, error, "sllist->header is NULL");
     LOG_ERROR(l->header->next != NULL, error, "sllist->header->next is NULL");
     LOG_ERROR(l->trailer != NULL, error, "sllist->trailer is NULL");
     LOG_ERROR(l->trailer->next != NULL, error, "sllist->trailer->next is NULL");

     bool rv ;
     sllist *sub_list = sllist_create();
     LOG_ERROR(sub_list != NULL, error, "failed to create sllist");

     while (!sllist_is_empty(l)) {
	  void *retval = sllist_delete_element(l, other, condition);
	  if (retval == NULL) {
	       break;
	  }
	  rv = sllist_append_element(sub_list, retval);
	  LOG_ERROR(rv != false, error, "failed to append element '%p' to sllist", retval);
     }

     if (sllist_is_empty(sub_list)) {
	  rv = sllist_delete(&sub_list);
	  LOG_ERROR(rv = true, error, "failed to free sllist");
	  return NULL;
     }

     return sub_list;

error:
     return NULL;
}
