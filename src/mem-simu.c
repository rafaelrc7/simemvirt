#include <stdint.h>

#include "mem-simu.h"

static unsigned int writes = 0;
static unsigned int page_faults = 0;

void swapin(Memory_frame *physical_mem, Free_frame **free_stack, Memory_page *page_table, uint32_t page_addr)
{
	uint32_t mem_addr;

	if (!*free_stack)
		return;

	*free_stack = free_frame_stack_pop(*free_stack, &mem_addr);
	page_table[page_addr].is_loaded = 1;
	page_table[page_addr].addr = mem_addr;

	physical_mem[mem_addr].M = 0;
	physical_mem[mem_addr].A = 0;
	physical_mem[mem_addr].P = 1;
	physical_mem[mem_addr].page_id = page_addr;

	++page_faults;
}

void swapout(Memory_frame *physical_mem, Free_frame **free_stack, Memory_page *page_table, uint32_t page_addr)
{
	uint32_t mem_addr = page_table[page_addr].addr;
	page_table[page_addr].is_loaded = 0;

	physical_mem[mem_addr].P = 0;
	if (physical_mem[mem_addr].M) {
		++writes;
	}

	*free_stack = free_frame_stack_push(*free_stack, mem_addr);

}

unsigned int get_writes() {
	return writes;
}

unsigned int get_page_faults() {
	return page_faults;
}

