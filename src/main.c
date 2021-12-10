#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mem-simu.h"
#include "nru.h"

#define ARCH (32)
#define KB (1024)
#define MB (1024 * KB)

#define NUM_ALGS 3
enum ALGORITHM { NRU = 0, FIFO2, LFU };

static enum ALGORITHM curr_alg;
static uint32_t (*paging_algo[NUM_ALGS]) (uint32_t page_id, Memory_page *page_table, Memory_frame *physical_mem, size_t num_mem_frames, Free_frame **free_frame_stack) = { &nru, NULL, NULL };

static unsigned long int time = 0;

static inline uint32_t get_page_id(uint32_t addr, unsigned long int page_id_offset);

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
			uint32_t page_id = get_page_id(addr, page_id_offset);
			if (op == 'R' || op == 'W') {
				paging_algo[curr_alg](page_id, page_table, physical_mem, num_mem_frames, &free_frames_stack);
				physical_mem[page_table[page_id].addr].T = time;

				if (op == 'W') {
					physical_mem[page_table[page_id].addr].M = 1;
				}
			} else {
				fprintf(stderr, "ERROR: Invalid operation '%c' inside log file.\n", op);
				fclose(handle);
				exit(EXIT_FAILURE);
			}

			++time;
		}
	}

	free_frame_stack_destroy(free_frames_stack);
	free(page_table);
	free(physical_mem);

	return 0;
}

static inline uint32_t get_page_id(uint32_t addr, unsigned long int page_id_offset)
{
	return addr >> page_id_offset;
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

