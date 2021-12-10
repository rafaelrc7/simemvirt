#ifndef _MEM_SIMU_H
#define _MEM_SIMU_H

#include <stdint.h>

#include "frame_stack.h"

typedef struct memory_frame Memory_frame;
typedef struct memory_page Memory_page;

struct memory_frame {
	unsigned long int T;	/* ultimo acesso */
	unsigned char R;		/* R bit */
	unsigned char M;		/* Modified bit */
	unsigned char P;		/* 1 se ter página referenciada */
	uint32_t page_id;
};

struct memory_page {
	uint32_t addr;				/* endereço na memória física */
	unsigned char is_loaded;	/* 1 se estiver na memória física */
};

void swapin(Memory_frame *physical_mem, Free_frame **free_stack, Memory_page *page_table, uint32_t page_addr);
void swapout(Memory_frame *physical_mem, Free_frame **free_stack, Memory_page *page_table, uint32_t page_addr);

unsigned int get_writes();
unsigned int get_page_faults();

#endif

