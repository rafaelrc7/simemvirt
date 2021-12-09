#include <stdio.h>
#include <stdlib.h>

#include "second_chance.h"
#include "frame_stack.h"
#include "mem-simu.h"
#include "frame_stack.h"


void fifo_second_chance(int stacksize, Free_frame* stack, int num_mem_frames, Memory_frame * physical_memory,
Memory_page * page_table, unsigned long int num_page)
{
    unsigned char *R_bit;
    unsigned int victim_frame = 0;

    R_bit = (unsigned char*) calloc(num_mem_frames, sizeof(unsigned char));
    // Cria os bits de referência

    if (!R_bit)
    {
        perror("calloc()");
        exit(EXIT_FAILURE);
    } 
    for (int i = 0; i < num_mem_frames; i++) 
        R_bit[i] = 0; //Setta todos os bits de referência para 0

    for (int i = 0; i < num_page; i++)
    {
        if (!page_in_memory(num_mem_frames, physical_memory, page_table[i].addr, R_bit, i))
        {
            for (int j = victim_frame; j < num_mem_frames + victim_frame; j++)
            {
                if (R_bit[j])
                {
                    R_bit[j] = 0;
                }
                else
                {
                    //realiza o swapin
                    victim_frame = ++j % num_mem_frames;  //Se for > que o número de frames, cicla
                    break;
                }
            }
        }
    }

}

int page_in_memory(int num_mem_frames, Memory_frame * physical_memory, uint32_t addr, unsigned char *R_bit, int frame_bit)
//Returns 0 or 1 based on wether the page is already in a memory frame
{
    for (int i = 0; i < num_mem_frames; i++)
    {
        if (!physical_memory[i].R) //Se a página não estiver referenciando ninguém, podemos retornar zero, pois o programa verifica em ordem
        {
            return 0;
        }

        if (physical_memory[i].R == addr)
        {
            R_bit[frame_bit] = 1; //Seta o bit de referência como 1
            return 1;
        }
    }
}