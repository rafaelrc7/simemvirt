#ifndef _MEM_SIMU_H
#define _MEM_SIMU_H

#include <stdint.h>

#include "frame_stack.h"

typedef struct memory_frame Memory_frame;
typedef struct memory_page Memory_page;

struct memory_frame {
	unsigned long int T;	/* ultimo acesso */
	uint32_t R;				/* addr da página referenciada */
	unsigned char P;		/* 1 se ter página referenciada */
	unsigned char M;		/* 1 se página estiver modificada */
	unsigned char fifo_r;	/* bit para o algoritimo fifo de 2a chance */
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

