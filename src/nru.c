#include <stdint.h>
#include <sys/types.h>

#include "mem-simu.h"
#include "nru.h"

#define R_DUR 100

static long unsigned int turn = 0;

void nru(uint32_t page_id, Memory_page *page_table, Memory_frame *physical_mem, size_t num_mem_frames, Free_frame **free_frame_stack)
{
	unsigned int i;

	if (!page_table[page_id].is_loaded) {
		if (!*free_frame_stack) {
			uint8_t c1 = 0, c2 = 0, c3 = 0, c4 = 0;
			uint32_t c1_addr, c2_addr, c3_addr, c4_addr, pag;

			for (i = 0; i < num_mem_frames; ++i) {
				unsigned char M = physical_mem[i].M;
				unsigned char R = physical_mem[i].R;

				if (M && R) {
					if (!c4) c4_addr = i;
					c4 = 1;
				} else if (!M && R) {
					if (!c3) c3_addr = i;
					c3 = 1;
				} else if (M && !R) {
					if (!c2) c2_addr = i;
					c2 = 1;
				} else {
					if (!c1) c1_addr = i;
					c1 = 1;
					break;
				}
			}

			if (c1)
				pag = physical_mem[c1_addr].page_id;
			else if (c2)
				pag = physical_mem[c2_addr].page_id;
			else if (c3)
				pag = physical_mem[c3_addr].page_id;
			else
				pag = physical_mem[c4_addr].page_id;

			swapout(physical_mem, free_frame_stack, page_table, pag);
		}

		swapin(physical_mem, free_frame_stack, page_table, page_id);
		physical_mem[page_table[page_id].addr].R = 1;
	}

	if (++turn == R_DUR) {
		turn = 0;
		for (i = 0; i < num_mem_frames; ++i)
			physical_mem[i].R = 0;
	}
}

