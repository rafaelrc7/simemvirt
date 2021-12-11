#include <stdlib.h>
#include <stdio.h>
#include "frame_stack.h"

struct free_frame_node {
	uint32_t addr;	 	/* endereço de frame livre na memória física */
	Free_frame *next;	/* próximo nó */
};

Free_frame *free_frame_stack_create(unsigned long int num_mem_frames)
{
	unsigned long int i;
	Free_frame *stack = NULL;

	for (i = 0; i < num_mem_frames; ++i)
		stack = free_frame_stack_push(stack, i);

	return stack;
}

Free_frame *free_frame_stack_push(Free_frame *stack, uint32_t addr)
{
	Free_frame *node = (Free_frame *)malloc(sizeof(Free_frame));
	if (!node) {
		fprintf(stderr, "malloc() fail.\n");
		exit(EXIT_FAILURE);
	}

	node->addr = addr;
	node->next = stack;

	return node;
}

Free_frame *free_frame_stack_pop(Free_frame *stack, uint32_t *addr)
{
	Free_frame *next = stack->next;

	if (addr)
		*addr = stack->addr;

	free(stack);

	return next;
}

void free_frame_stack_destroy(Free_frame *stack)
{
	while(stack)
		stack = free_frame_stack_pop(stack, NULL);
}

