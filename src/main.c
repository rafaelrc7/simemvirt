#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "mem-simu.h"

#define ARCH (32)
#define KB (1024)
#define MB (1024 * KB)

int argtoul(const char *arg, unsigned long int *num);

int main(int argc, char **argv)
{
	Memory_page *page_table;
	Memory_frame *physical_mem;
	Free_frame *free_frames_stack;

	FILE *handle;
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
			if (op == 'R') {

			} else if (op == 'W') {

			} else {
				fprintf(stderr, "ERROR: Invalid operation '%c' inside log file.\n", op);
				fclose(handle);
				exit(EXIT_FAILURE);
			}
		}
	}

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

