#include <stdio.h>
#include <stdlib.h>

#include "second_chance.h"
#include "frame_stack.h"
#include "mem-simu.h"
#include "frame_stack.h"
#include "linked-list.h"

static List *fifo;

void fifo_second_chance(uint32_t page_id, Memory_page *page_table, Memory_frame *physical_mem, size_t num_mem_frames, Free_frame **free_frame_stack)
{
    /*
    if (!fifo){
        fifo = llist_create();
    }
    */

    if (!page_table[page_id].is_loaded)
    {
        if (*free_frame_stack) //Memória ainda não está cheia
        {
            llist_add_tail(fifo, page_id);
            swapin(physical_mem, free_frame_stack, page_table, page_id);
            return;
        } else //Endereço deve ser adicionado à memória que está cheia
        {
            uint32_t tempAddr;
            while(1) {
                tempAddr = llist_remove_head(fifo);
                if (physical_mem[page_table[tempAddr].addr].R){
                    physical_mem[page_table[tempAddr].addr].R = 0; //Zera o bit de referência.
                    llist_add_tail(fifo, tempAddr); //Coloca o elemento novamente no final da fila.
                    return;
                } else {
                    swapout(physical_mem, free_frame_stack, page_table, tempAddr);
                    swapin(physical_mem, free_frame_stack, page_table, page_id);
                    physical_mem[page_table[page_id].addr].R = 1;
                    llist_add_tail(fifo, page_id);  
                    return;
                }
            }
        }
    } else
    {
        physical_mem[page_table[page_id].addr].R = 1;
    }
}

void second_chance_setup()
{
    fifo = llist_create();
}

void second_chance_clean()
{
    llist_destroy(fifo);
}