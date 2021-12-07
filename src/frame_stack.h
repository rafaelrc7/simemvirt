#ifndef _FRAME_STACK_H
#define _FRAME_STACK_H

#include <stdint.h>

typedef struct free_frame_node Free_frame;

Free_frame *free_frame_stack_create(unsigned long int num_mem_frames, unsigned long int page_size);
Free_frame *free_frame_stack_push(Free_frame *stack, uint32_t addr);
Free_frame *free_frame_stack_pop(Free_frame *stack, uint32_t *addr);
void free_frame_stack_destroy(Free_frame *stack);

#endif

