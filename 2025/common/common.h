#include <stdint.h>
#include <string.h>

enum {
	
	MAX_STR_LEN 			= 1024,
	MAX_INPUT_BUFFER_LEN	= 32 * 1024
};

enum {
	
	EXIT_FAIL	= -1,
	EXIT_SUCCESS	= 0
};

// Helper functions not in libc

void swap(void *v1, void *v2);

char *reverse_str(char *str);

char *int_to_str(uint64_t num, char *buf);

void print_num(uint64_t num);

void parse_range(const char *range, uint64_t *start, uint64_t *end);

// Boilerplate for every day

int32_t init_aoc(int argc, char **argv, char **input);
void clean_aoc(uint64_t answer, char *input);
