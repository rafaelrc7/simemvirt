XX#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "mem-simu.h"
#include "frame_stack.h"

void lfu(int stackSize, Free_frame *stack,int num_mem_frames, Memory_frame *physical_mem, Free_frame **free_stack, Memory_page *page_table, uint32_t page_addr){


	for(int i = 0; i < num_mem_frames  ; i++){

		if(*free_stack){//stack is not full
			swapin(*physical_mem, **free_stack, *page_table, page_addr);
			free_frame_stack_push( *stack, addr)

		}
		else{
			//procurar frame menos utilizado
			//encontra o frame, e descarrega  (swapout e pop)
			//carrega o proximo por cima (swapin e push)


		}





}
