#include <stdio.h>
#include <stdlib.h>

#include "second_chance.h"
#include "frame_stack.h"
#include "mem-simu.h"
#include "frame_stack.h"
#include "linked-list.h"

static List *fifo;

uint32_t fifo_second_chance(uint32_t page_id, Memory_page *page_table, Memory_frame *physical_mem, size_t num_mem_frames, Free_frame **free_frame_stack)
{
    if (!fifo){
        fifo = llist_create();
    }

    if (*free_frame_stack) //Memória ainda não está cheia
    {
        llist_add_tail(fifo, page_id);
        swapin(physical_mem, *free_frame_stack, page_table, page_id);
        return page_id;
    } else if (page_table[page_id].is_loaded) //Página está na lista e carregada
    {
        uint32_t mem_addr = page_table[page_id].addr;
        physical_mem[mem_addr].R = 1;
        return page_id;
    } else //Endereço deve ser adicionado à memória que está cheia
    {
        uint32_t tempAddr;
        Node * node = fifo->head; // Pega o primeiro elemento da fila
        while(1) {
            tempAddr = llist_remove_head(fifo);
            if (physical_mem[tempAddr].R){
                physical_mem[tempAddr].R = 0; //Zera o bit de referência.
                llist_add_tail(fifo, tempAddr); //Coloca o elemento novamente no final da fila.
            } else {
                swapout(physical_mem, *free_frame_stack, page_table, tempAddr);
                swapin(physical_mem, free_frame_stack, page_table, page_id);
                physical_mem[page_table[page_id].addr].R = 1;
                return page_id;
            }
        }
    }
}