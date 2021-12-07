#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ARCH (32)
#define KB (1024)
#define MB (1024 * KB)

typedef struct memory_frame Memory_frame;
typedef struct memory_page Memory_page;
typedef struct free_frame_node Free_frame;

struct memory_frame {
	unsigned long int T;	/* ultimo acesso */
	uint32_t R;				/* addr da página referenciada */
	unsigned char P;		/* 1 se ter página referenciada */
	unsigned char M;		/* 1 se página estiver modificada */
};

struct memory_page {
	uint32_t addr;				/* endereço na memória física */
	unsigned char is_loaded;	/* 1 se estiver na memória física */
};

struct free_frame_node {
	uint32_t addr;	 	/* endereço de frame livre na memória física */
	Free_frame *next;	/* próximo nó */
};

Free_frame *free_frame_stack_create(unsigned long int num_mem_frames, unsigned long int page_size);
Free_frame *free_frame_stack_push(Free_frame *stack, uint32_t addr);
Free_frame *free_frame_stack_pop(Free_frame *stack, uint32_t *addr);
void free_frame_stack_destroy(Free_frame *stack);

void swapin(Memory_frame *physical_mem, Free_frame **free_stack, Memory_page *page_table, uint32_t page_addr);
void swapout(Memory_frame *physical_mem, Free_frame **free_stack, Memory_page *page_table, uint32_t page_addr);

int argtoul(const char *arg, unsigned long int *num);

int main(int argc, char **argv)
{
	Memory_page *page_table;
	Memory_frame *physical_mem;
	Free_frame *free_frames_stack;

	unsigned long int page_size, mem_size, num_mem_frames, num_pages, page_id_offset;
	const char *alg_name;
	const char *file_name;

	if (argc != 5) {
		fprintf(stderr, "USAGE: %s <algoritimo> <arquivo de enderecos>"
						" <tamanho de cada pagina> <tamanho da memoria>\n",
						argv[0]);
		exit(EXIT_FAILURE);
	}

	alg_name = argv[1];
	file_name = argv[2];
	if (!argtoul(argv[3], &page_size)) {
		fprintf(stderr, "Third argument is invalid.\n");
		exit(EXIT_FAILURE);
	}
	page_size *= KB;

	if (!argtoul(argv[4], &mem_size)) {
		fprintf(stderr, "Fourth argument is invalid.\n");
		exit(EXIT_FAILURE);
	}
	mem_size *= MB;

	num_mem_frames = mem_size / page_size;

	physical_mem = (Memory_frame *)calloc(num_mem_frames, sizeof(Memory_frame));
	if (!physical_mem) {
		fprintf(stderr, "calloc() failed.\n");
		exit(EXIT_FAILURE);
	}

	page_id_offset = log2(page_size);
	num_pages = pow(2, ARCH-page_id_offset);

	page_table = (Memory_page *)calloc(num_pages, sizeof(Memory_page));
	if (!page_table) {
		fprintf(stderr, "calloc() failed.\n");
		exit(EXIT_FAILURE);
	}

	free_frames_stack = free_frame_stack_create(num_mem_frames, page_size);


	free_frame_stack_destroy(free_frames_stack);
	free(page_table);
	free(physical_mem);

	return 0;
}

int argtoul(const char *arg, unsigned long int *num)
{
	char *endptr;

	if (*arg == 0)
		return 0;

	*num = strtoul(arg, &endptr, 10);
	if (*endptr != 0)
		return 0;

	return 1;
}

Free_frame *free_frame_stack_create(unsigned long int num_mem_frames, unsigned long int page_size)
{
	unsigned long int i;
	Free_frame *stack = NULL;

	for (i = 0; i < num_mem_frames; ++i) {
		stack = free_frame_stack_push(stack, i * page_size);
		printf("ADDR: %lx\n", i*page_size);
	}

	return stack;
}

Free_frame *free_frame_stack_push(Free_frame *stack, uint32_t addr)
{
	Free_frame *node = (Free_frame *)malloc(sizeof(Free_frame));
	if (!node) {
		fprintf(stderr, "malloc() fail.\n");
		exit(EXIT_FAILURE);
	}

	node->addr = addr;
	node->next = stack;

	return node;
}

Free_frame *free_frame_stack_pop(Free_frame *stack, uint32_t *addr)
{
	Free_frame *next = stack->next;

	if (addr)
		*addr = stack->addr;

	free(stack);

	return next;
}

void free_frame_stack_destroy(Free_frame *stack)
{
	while(stack)
		stack = free_frame_stack_pop(stack, NULL);
}

void swapin(Memory_frame *physical_mem, Free_frame **free_stack, Memory_page *page_table, uint32_t page_addr)
{
	uint32_t mem_addr;

	if (!*free_stack)
		return;

	*free_stack = free_frame_stack_pop(*free_stack, &mem_addr);
	page_table[page_addr].is_loaded = 1;
	page_table[page_addr].addr = mem_addr;

	physical_mem[mem_addr].M = 0;
	physical_mem[mem_addr].P = 1;
	physical_mem[mem_addr].T = 0;
	physical_mem[mem_addr].R = page_addr;

}

void swapout(Memory_frame *physical_mem, Free_frame **free_stack, Memory_page *page_table, uint32_t page_addr)
{
	uint32_t mem_addr = page_table[page_addr].addr;
	page_table[page_addr].is_loaded = 0;

	physical_mem[mem_addr].P = 0;
	if (physical_mem[mem_addr].M) {
		// TODO: escrita
	}

	*free_stack = free_frame_stack_push(*free_stack, mem_addr);
}

