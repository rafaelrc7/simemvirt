#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mem-simu.h"

#define ARCH (32)
#define KB (1024)
#define MB (1024 * KB)

#define NUM_ALGS 3
enum ALGORITHM { NRU = 0, FIFO2, LFU };

static enum ALGORITHM curr_alg;
static uint32_t (*alg[NUM_ALGS]) (Memory_frame *physical_mem, unsigned long int num_mem_frames);

static unsigned int writes = 0;
static unsigned int page_faults = 0;
static unsigned long int T = 0;

static inline uint32_t log2phy(uint32_t addr, unsigned long int page_id_offset);
static void pagwrite(uint32_t page, Memory_page *page_table, Memory_frame *physical_mem, Free_frame *free_frames_stack, unsigned long int mem_size);
static void pagread(uint32_t page, Memory_page *page_table, Memory_frame *physical_mem, Free_frame *free_frames_stack, unsigned long int mem_size);

static int argtoul(const char *arg, unsigned long int *num);

int main(int argc, char **argv)
{
	Memory_page *page_table;
	Memory_frame *physical_mem;
	Free_frame *free_frames_stack;
	unsigned long int page_size, mem_size, num_mem_frames, num_pages, page_id_offset;

	FILE *handle;
	const char *alg_name;
	const char *file_name;

	if (argc != 5) {
		fprintf(stderr, "USAGE: %s <algoritimo> <arquivo de enderecos>"
						" <tamanho de cada pagina> <tamanho da memoria>\n",
						argv[0]);
		exit(EXIT_FAILURE);
	}

	alg_name = argv[1];
	if (strcmp("NRU", alg_name) == 0) {
		curr_alg = NRU;
	} else if (strcmp("FIFO2", alg_name) == 0) {
		curr_alg = FIFO2;
	} else if (strcmp("LFU", alg_name) == 0) {
		curr_alg = LFU;
	} else {
		fprintf(stderr, "ERROR: Invalid algorithm '%s'\n", alg_name);
		exit(EXIT_FAILURE);
	}

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
		perror("calloc()");
		exit(EXIT_FAILURE);
	}

	page_id_offset = log2(page_size);
	num_pages = pow(2, ARCH-page_id_offset);

	page_table = (Memory_page *)calloc(num_pages, sizeof(Memory_page));
	if (!page_table) {
		perror("calloc()");
		exit(EXIT_FAILURE);
	}

	free_frames_stack = free_frame_stack_create(num_mem_frames, page_size);

	if (!(handle = fopen(file_name, "r"))) {
		perror("fopen()");
		exit(EXIT_FAILURE);
	}

	while (!feof(handle)) {
		uint32_t addr;
		char op;

		if (fscanf(handle, " %x %c", &addr, &op) == 2) {
			uint32_t pag = log2phy(addr, page_id_offset);
			if (op == 'R') pagread(pag, page_table, physical_mem, free_frames_stack, num_mem_frames);
			else if (op == 'W') pagwrite(pag, page_table, physical_mem, free_frames_stack, num_mem_frames);
			else {
				fprintf(stderr, "ERROR: Invalid operation '%c' inside log file.\n", op);
				fclose(handle);
				exit(EXIT_FAILURE);
			}

			++T;
		}
	}

	free_frame_stack_destroy(free_frames_stack);
	free(page_table);
	free(physical_mem);

	return 0;
}

static inline uint32_t log2phy(uint32_t addr, unsigned long int page_id_offset)
{
	return addr >> page_id_offset;
}

static void pagget(uint32_t page, Memory_page *page_table, Memory_frame *physical_mem, Free_frame *free_frames_stack, unsigned long int mem_size)
{
	if (!page_table[page].is_loaded) {
		++page_faults;
		if (!free_frames_stack) {
			uint32_t so_page = alg[curr_alg](physical_mem, mem_size);
			if (physical_mem[page_table[so_page].addr].M)
				++writes;
			swapout(physical_mem, &free_frames_stack, page_table, so_page);
		}
		swapin(physical_mem, &free_frames_stack, page_table, page);
	}

	physical_mem[page_table[page].addr].T = T;
}

static void pagwrite(uint32_t page, Memory_page *page_table, Memory_frame *physical_mem, Free_frame *free_frames_stack, unsigned long int mem_size)
{
	pagget(page, page_table, physical_mem, free_frames_stack, mem_size);
	physical_mem[page_table[page].addr].M = 1;
}

static void pagread(uint32_t page, Memory_page *page_table, Memory_frame *physical_mem, Free_frame *free_frames_stack, unsigned long int mem_size)
{
	pagget(page, page_table, physical_mem, free_frames_stack, mem_size);
}

static int argtoul(const char *arg, unsigned long int *num)
{
	char *endptr;

	if (*arg == 0)
		return 0;

	*num = strtoul(arg, &endptr, 10);
	if (*endptr != 0)
		return 0;

	return 1;
}

