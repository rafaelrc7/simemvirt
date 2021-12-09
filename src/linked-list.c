#include <stdio.h>
#include <stdlib.h>

#include "linked-list.h"

List *llist_create()
{
	return calloc(1, sizeof(List));
}

void llist_destroy(List *list)
{
	while (list->head)
		llist_remove_head(list);

	free(list);
}

void llist_add_head(List *list, uint32_t val)
{
	Node *node = (Node *)malloc(sizeof(Node));
	if (!node) {
		perror("malloc()");
		return;
	}

	node->next = list->head;
	node->val = val;

	list->head = node;

	if (!list->tail)
		list->tail = node;
}

void llist_add_tail(List *list, uint32_t val)
{
	Node *node = (Node *)malloc(sizeof(Node));
	if (!node) {
		perror("malloc()");
		return;
	}

	node->next = NULL;
	node->val = val;

	if (list->tail)
		list->tail->next = node;
	else
		list->head = node;

	list->tail = node;
}

uint32_t llist_remove_head(List *list)
{
	Node *head;
	uint32_t val = 0;

	if (!list->head)
		return 0;

	head = list->head;

	if (list->tail == head)
		list->tail = NULL;

	val = head->val;
	list->head = head->next;

	free(head);

	return val;
}

