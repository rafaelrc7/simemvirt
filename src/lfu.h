#ifndef _LFU_H
#define _LFU_H

#include <sys/types.h>

#include "mem-simu.h"

void lfu(uint32_t page_id, Memory_page *page_table, Memory_frame *physical_mem, size_t num_mem_frames, Free_frame **free_frame_stack);

#endif

