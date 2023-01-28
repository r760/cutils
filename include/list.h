#ifndef SLLIST_H
#define SLLIST_H
#include <stdbool.h>
#include <stdlib.h>

struct node {
     struct node *next; 
     void *data; 
};

typedef struct node node;

typedef struct {
     node *header; 
     node *trailer; 
     size_t size; 
} list;

typedef struct
{
     list *l;
     node *curr;
} list_iter;

list_iter *list_iter_create(list *l);

bool list_iter_delete(list_iter **l_iter);

bool list_iter_reset(list_iter *l_iter);

bool list_iter_has_next(list_iter *l_iter);

void *list_iter_next(list_iter *l_iter);

node *node_create();

bool node_delete(node **n);

list *list_create();

bool list_delete(list **l);

size_t list_get_size(list *l);

bool list_is_empty(list *l);

node *list_get_front(list *l);

void *list_get_front_data(list *l);

node *list_get_rear(list *l);

void *list_get_rear_data(list *l);

bool list_prepend_element(list *l, void *element);

bool list_append_element(list *l, void *element);

void *list_delete_front(list *l);

void *list_delete_rear(list *l);

size_t list_count_elements(list *l, void *other, bool (*condition)(void *element, void *other));

list *list_get_elements(list *l, void *other, bool (*condition)(void *element, void *other));

list *list_delete_elements(list *l, void *other, bool (*condition)(void *element, void *other));

#endif
