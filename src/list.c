#include <stdio.h>
#include "../include/log.h"
#include "../include/list.h"

list_iter *list_iter_create(list *l)
{
     LOG_ERROR(l != NULL, error, "list is NULL");

     list_iter *l_iter = malloc(sizeof(list_iter));
     LOG_ERROR(l_iter != NULL, error, "failed to malloc list_iter");

     l_iter->l = l;
     if (!list_is_empty(l)) {
	  l_iter->curr = list_get_front(l);
	  LOG_ERROR(l_iter->curr != NULL, error, "failed to get front of list");
     } else {
	  l_iter->curr = NULL;
     }

     return l_iter;

error:
     return NULL;
}

bool list_iter_delete(list_iter **l_iter)
{
     LOG_ERROR(l_iter != NULL, error, "pointer to list_iter is NULL");
     LOG_ERROR(*l_iter != NULL, error, "list_iter is NULL");

     free(*l_iter);
     *l_iter = NULL;

     return true;

error:
     return false;
}

bool list_iter_reset(list_iter *l_iter)
{
     LOG_ERROR(l_iter != NULL, error, "list_iter is NULL");

     list *l = l_iter->l;
     LOG_ERROR(l != NULL, error, "list is NULL");

     l_iter->curr = list_get_front(l);
     LOG_ERROR(l_iter->curr != NULL, error, "failed to get front of list");

     return true;

error:
     return false;
}

bool list_iter_has_next(list_iter *l_iter)
{
     LOG_ERROR(l_iter != NULL, error, "list_iter is NULL");

     node *curr = l_iter->curr;
     void *element = list_iter_next(l_iter);

     l_iter->curr = curr;

     return element != NULL;

error:
     return false;
}

void *list_iter_next(list_iter *l_iter)
{
     LOG_ERROR(l_iter != NULL, error, "list_iter is NULL");

     node *curr = l_iter->curr;

     list *l = l_iter->l;
     LOG_ERROR(l != NULL, error, "list is NULL");

     if (curr != NULL) {
	  void *data = curr->data;
	  curr = curr->next; 
	  l_iter->curr = curr;
	  return data;
     }

error:
     return NULL;
}

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

list *list_create()
{
    node *header = node_create();
    LOG_ERROR(header != NULL, error, "failed to create node");
    node *trailer = node_create();
    LOG_ERROR(trailer != NULL, error, "failed to create node");

    list *l = malloc(sizeof(list));
    LOG_ERROR(l != NULL, error, "failed to malloc list");
    l->header = header;
    l->trailer = trailer;
    l->size = 0;

    return l;

error:
    return NULL;
}

bool list_delete(list **l)
{
    LOG_ERROR(l != NULL, error, "pointer to list is NULL");
    LOG_ERROR(*l != NULL, error, "list is NULL");

    if (!list_is_empty(*l)) {
	 node *curr = list_get_front(*l);

	 while (curr != NULL) {
	      node *temp = curr;
	      curr = curr->next;
	      free(temp);
	 }
    }

    free((*l)->header);
    free((*l)->trailer);
    free(*l);
    *l = NULL;

    return true;

error:
    return false;
}

size_t list_get_size(list *l)
{
    LOG_ERROR(l != NULL, error, "list is NULL");

    return l->size;

error:
    return 0;
}

bool list_is_empty(list *l)
{
    LOG_ERROR(l != NULL, error, "list is NULL");

    if (list_get_size(l) >= 1) {
        return false;
    }

error:
    return true;
}

node *list_get_front(list *l)
{
    LOG_ERROR(l != NULL, error, "list is NULL");
    LOG_ERROR(list_is_empty(l) == false, error, "list is empty");
    LOG_ERROR(l->header != NULL, error, "list->header is NULL");
    LOG_ERROR(l->header->next != NULL, error, "list->header->next is NULL");

    return l->header->next;

error:
    return NULL;
}

void *list_get_front_data(list *l)
{
    node *front = list_get_front(l);
    LOG_ERROR(front != NULL, error, "front is NULL");

    return front->data;

error:
    return NULL;
}

node *list_get_rear(list *l)
{
    LOG_ERROR(l != NULL, error, "list is NULL");
    LOG_ERROR(list_is_empty(l) == false, error, "list is empty");
    LOG_ERROR(l->trailer != NULL, error, "list->trailer is NULL");
    LOG_ERROR(l->trailer->next != NULL, error, "list->trailer->next is NULL");

    return l->trailer->next;

error:
    return NULL;
}

void *list_get_rear_data(list *l)
{
    node *rear = list_get_rear(l);
    LOG_ERROR(rear != NULL, error, "rear is NULL");

    return rear->data;

error:
    return NULL;
}

bool list_prepend_element(list *l, void *element)
{
    LOG_ERROR(l != NULL, error, "list is NULL");
    LOG_ERROR(element != NULL, error, "element is NULL");

    node *n = node_create();
    LOG_ERROR(n != NULL, error, "failed to create node");
    n->data = element;

    if (list_is_empty(l)) {
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

bool list_append_element(list *l, void *element)
{
    LOG_ERROR(l != NULL, error, "list is NULL");
    LOG_ERROR(element != NULL, error, "element is NULL");

    node *n = node_create();
    LOG_ERROR(n != NULL, error, "failed to create node");
    n->data = element;

    if (list_is_empty(l)) {
        l->header->next = n;
        l->trailer->next = n;
    } else {
        node *rear = list_get_rear(l);
        LOG_ERROR(rear != NULL, error, "rear is NULL");
        rear->next = n;
        l->trailer->next = n;
    }
    l->size += 1;

    return true;

error:
    return false;
}

void *list_delete_front(list *l)
{
    LOG_ERROR(l != NULL, error, "list is NULL");
    LOG_ERROR(list_is_empty(l) == false, error, "list is empty");
    LOG_ERROR(l->header != NULL, error, "list->header is NULL");
    LOG_ERROR(l->header->next != NULL, error, "list->header->next is NULL");
    LOG_ERROR(l->trailer != NULL, error, "list->trailer is NULL");
    LOG_ERROR(l->trailer->next != NULL, error, "list->trailer->next is NULL");

    size_t size = list_get_size(l);
    node *first = list_get_front(l);
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

void *list_delete_rear(list *l)
{
    LOG_ERROR(l != NULL, error, "list is NULL");
    LOG_ERROR(list_is_empty(l) == false, error, "list is empty");
    LOG_ERROR(l->header != NULL, error, "list->header is NULL");
    LOG_ERROR(l->header->next != NULL, error, "list->header->next is NULL");
    LOG_ERROR(l->trailer != NULL, error, "list->trailer is NULL");
    LOG_ERROR(l->trailer->next != NULL, error, "list->trailer->next is NULL");

    size_t size = list_get_size(l);
    node *rear = list_get_rear(l);
    void *retval = rear->data;
    LOG_ERROR(retval != NULL, error, "rear->data is NULL");

    if (size == 1) {
        free(rear);
        l->header->next = NULL;
        l->trailer->next = NULL;
    } else {
        node *curr = list_get_front(l);
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

size_t list_count_elements(list *l, void *other, bool (*condition)(void *element, void *other))
{
     LOG_ERROR(l != NULL, error, "list is NULL");
     LOG_ERROR(list_is_empty(l) == false, error, "list is empty");
     LOG_ERROR(l->header != NULL, error, "list->header is NULL");
     LOG_ERROR(l->header->next != NULL, error, "list->header->next is NULL");
     LOG_ERROR(l->trailer != NULL, error, "list->trailer is NULL");
     LOG_ERROR(l->trailer->next != NULL, error, "list->trailer->next is NULL");

     size_t size = 0;

     list_iter *l_iter = list_iter_create(l);
     LOG_ERROR(l_iter != NULL, error, "failed to create list_iter");

     while (list_iter_has_next(l_iter)) {
	  void *data = list_iter_next(l_iter);
	  LOG_ERROR(data != NULL, error, "data is NULL");
	  if (condition(data, other)) {
	       size++;
	  }

     }

     bool retval = list_iter_delete(&l_iter);
     LOG_ERROR(retval == true, error, "failed to delete list_iter");

     return size;

error:
     return 0;
}

list *list_get_elements(list *l, void *other, bool (*condition)(void *element, void *other))
{
     LOG_ERROR(l != NULL, error, "list is NULL");
     LOG_ERROR(list_is_empty(l) == false, error, "list is empty");
     LOG_ERROR(l->header != NULL, error, "list->header is NULL");
     LOG_ERROR(l->header->next != NULL, error, "list->header->next is NULL");
     LOG_ERROR(l->trailer != NULL, error, "list->trailer is NULL");
     LOG_ERROR(l->trailer->next != NULL, error, "list->trailer->next is NULL");

     bool rv ;
     list *sub_list = list_create();
     LOG_ERROR(sub_list != NULL, error, "failed to create list");

     list_iter *l_iter = list_iter_create(l);
     LOG_ERROR(l_iter != NULL, error, "failed to create list_iter");

     while (list_iter_has_next(l_iter)) {
	  void *data = list_iter_next(l_iter);
	  LOG_ERROR(data != NULL, error, "data is NULL");
	  if (condition(data, other)) {
	       rv = list_append_element(sub_list, data);
	       LOG_ERROR(rv != false, error, "failed to append element '%p' to list", data);
	  }

     }

     bool retval = list_iter_delete(&l_iter);
     LOG_ERROR(retval == true, error, "failed to delete list_iter");

     if (list_is_empty(sub_list)) {
	  rv = list_delete(&sub_list);
	  LOG_ERROR(rv = true, error, "failed to free list");
	  return NULL;
     }

     return sub_list;

error:
     return NULL;
}

static void *list_delete_element(list *l, void *other, bool (*condition)(void *element, void *other))
{
    LOG_ERROR(l != NULL, error, "list is NULL");
    LOG_ERROR(list_is_empty(l) == false, error, "list is empty");
    LOG_ERROR(l->header != NULL, error, "list->header is NULL");
    LOG_ERROR(l->header->next != NULL, error, "list->header->next is NULL");
    LOG_ERROR(l->trailer != NULL, error, "list->trailer is NULL");
    LOG_ERROR(l->trailer->next != NULL, error, "list->trailer->next is NULL");

    void *retval = NULL;
    node *curr = list_get_front(l), *before = NULL;
    LOG_ERROR(curr != NULL, error, "failed to get front of list");

    if (condition(curr->data, other)) {
	 retval = list_delete_front(l);
	 LOG_ERROR(retval != NULL, error, "failed to delete front of list");
    } else {
	 before = curr;
	 curr = curr->next;

	 while (curr != NULL) {
	      if (condition(curr->data, other)) {
		   if (curr->next == NULL) {
			retval = list_delete_rear(l);
			LOG_ERROR(retval != NULL, error, "failed to delete rear of list");
		   } else {
			node *temp = curr;
			retval = curr->data;
			before->next = curr->next;
			node_delete(&temp);
			l->size--;
			LOG_ERROR(retval != NULL, error, "failed to free delete node of list");
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

list *list_delete_elements(list *l, void *other, bool (*condition)(void *element, void *other))
{
     LOG_ERROR(l != NULL, error, "list is NULL");
     LOG_ERROR(list_is_empty(l) == false, error, "list is empty");
     LOG_ERROR(l->header != NULL, error, "list->header is NULL");
     LOG_ERROR(l->header->next != NULL, error, "list->header->next is NULL");
     LOG_ERROR(l->trailer != NULL, error, "list->trailer is NULL");
     LOG_ERROR(l->trailer->next != NULL, error, "list->trailer->next is NULL");

     bool rv ;
     list *sub_list = list_create();
     LOG_ERROR(sub_list != NULL, error, "failed to create list");

     while (!list_is_empty(l)) {
	  void *retval = list_delete_element(l, other, condition);
	  if (retval == NULL) {
	       break;
	  }
	  rv = list_append_element(sub_list, retval);
	  LOG_ERROR(rv != false, error, "failed to append element '%p' to list", retval);
     }

     if (list_is_empty(sub_list)) {
	  rv = list_delete(&sub_list);
	  LOG_ERROR(rv = true, error, "failed to free list");
	  return NULL;
     }

     return sub_list;

error:
     return NULL;
}
