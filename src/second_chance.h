#ifndef SECOND_CHANCE
#define SECOND_CHANCE

#include <sys/types.h>

#include "mem-simu.h"

void fifo_second_chance(uint32_t page_id, Memory_page *page_table, Memory_frame *physical_mem, size_t num_mem_frames, Free_frame **free_frame_stack);
void second_chance_setup();
void second_chance_clean();
#endif

