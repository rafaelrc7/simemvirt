#include <stdio.h>
#include <stdlib.h>

#include "second_chance.h"
#include "frame_stack.h"
#include "mem-simu.h"
#include "frame_stack.h"
#include "linked-list.h"

static List *fifo;

uint32_t fifo_second_chance(uint32_t page_id, Memory_page *page_table, Memory_frame *physical_mem, Free_frame **free_frame_stack)
{
    if (!fifo){
        fifo = llist_create();
        // Add cada elemento presente na memória física, em ordem
    }

    if (page_table[page_id].is_loaded) //Página está na lista e carregada
    {
        uint32_t mem_addr = page_table[page_id].addr;
        physical_mem[mem_addr].R = 1;
    }
    else //Endereço deve ser adicionado
    {
        Node * node = fifo->head;
        uint32_t tempAddr;
        while(1) {
            if (physical_mem[node->val].R){
                //O bit é zerado e o elemento é colocado no começo da lista
                physical_mem[node->val].R = 0;
                tempAddr = llist_remove_head(fifo);
                llist_add_tail(fifo, tempAddr);
            } else {
                //realiza o swapout e o swapin
                //return ou break.
            }
        }
    }
}