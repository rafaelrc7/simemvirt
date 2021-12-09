#ifndef SECOND_CHANCE
#define SECOND_CHANCE

#include "mem-simu.h"

uint32_t fifo_second_chance(uint32_t page_id, Memory_page *page_table, Memory_frame *physical_mem, Free_frame **free_frame_stack);

#endif