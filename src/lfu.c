#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "mem-simu.h"
#include "frame_stack.h"
#include "lfu.h"

int entrou = 0, entrou1 = 0, carregado = 0;

void lfu(uint32_t page_id, Memory_page *page_table, Memory_frame *physical_mem, size_t num_mem_frames, Free_frame **free_frame_stack){

	//uint32_t pag;
	unsigned long int i = 0;
	//int entrou, entrou1;
	if(!page_table[page_id].is_loaded){
		entrou++;
		//printf("entrou no if %d\n", entrou);
		if(*free_frame_stack){ //stack ainda tem espaço
			swapin(physical_mem, free_frame_stack, page_table, page_id); //carrega
			physical_mem[page_table[page_id].addr].A ++;
			//pag = physical_mem[c1_addr].page_id;
		}
		else{
			//procurar frame menos utilizado
			entrou1++;
			//printf("entrou no else %d\n", entrou1);
			 unsigned long int menor = 1;
			 int id_temp = 0;
			for (i = 0; i < num_mem_frames; ++i){

				if(page_table[i].is_loaded && (physical_mem[i].A < menor)){//frame esta carregado e M < menor
					menor = (int) physical_mem[i].A;
					id_temp = i;
				}
			}
			//encontra o frame, e descarrega(swapout)
			swapout(physical_mem, free_frame_stack, page_table, id_temp);
			physical_mem[id_temp].A = 0;

			//carrega o proximo por cima (swapin)
			swapin(physical_mem, free_frame_stack, page_table, page_id);

		}
	}
	else{
		//pag = physical_mem[c1_addr].page_id;
		carregado++;
		//printf("estava carregado %d\n", carregado);
		physical_mem[page_table[page_id].addr].A ++; //apenas adiciona na frequencia
	}
}
