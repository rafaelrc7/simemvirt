#include <stdio.h>
#include <stdlib.h>

int argtoui(const char *arg, unsigned int *num);

int main(int argc, char **argv)
{
	unsigned int page_size, mem_size;
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
	if (!argtoui(argv[3], &page_size)) {
		fprintf(stderr, "Third argument is invalid.\n");
		exit(EXIT_FAILURE);
	}

	if (!argtoui(argv[4], &mem_size)) {
		fprintf(stderr, "Fourth argument is invalid.\n");
		exit(EXIT_FAILURE);
	}


	return 0;
}

int argtoui(const char *arg, unsigned int *num)
{
	char *endptr;

	if (*arg == 0)
		return 0;

	*num = (unsigned int)strtoul(arg, &endptr, 10);
	if (*endptr != 0)
		return 0;

	return 1;
}

