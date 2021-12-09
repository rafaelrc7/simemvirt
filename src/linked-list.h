#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <stdint.h>

typedef struct node Node;
typedef struct list List;

struct list {
	Node *head, *tail;
	unsigned long int size;
};

struct node {
	uint32_t val;
	Node *next;
};

List *llist_create();
void llist_destroy(List *list);
void llist_add_head(List *list, uint32_t val);
void llist_add_tail(List *list, uint32_t val);
uint32_t llist_remove_head(List *list);
uint32_t llist_remove_tail(List *list);

#endif

