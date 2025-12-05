#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <helper.h>

#define MAX_INPUT_LEN 16

int is_invalid(const char *str) {
	
	int result = 0;
	
	char **partitions = malloc(sizeof(char *) * MAX_INPUT_LEN);
	for (size_t index = 0; index < MAX_INPUT_LEN; ++index) {
		
		partitions[index] = malloc(MAX_STR_LEN / MAX_INPUT_LEN);
	}
	
	size_t len = strlen(str);
	for (size_t num_partitions = 2; num_partitions < MAX_INPUT_LEN; ++num_partitions) {
		
		if (len % num_partitions != 0) {
			
			continue;
		}
		
		size_t split_len = len / num_partitions;
		
		for (size_t partition = 0; partition < num_partitions; ++partition) {
			
			strncpy(partitions[partition], str + split_len * partition, split_len);
			partitions[partition][split_len] = '\0';
		}
		
		int invalid = 1;	
		for (size_t partition = 1; partition < num_partitions; ++partition) {
			
			if (strcmp(partitions[0], partitions[partition]) != 0) {
				
				invalid = 0;
				break;
			}
			
		}
		
		if (invalid) {
			
			result = 1;
			goto clean_mem;
		}
	}
	
clean_mem:
	
	for (size_t index = 0; index < MAX_INPUT_LEN; ++index) {
		
		free(partitions[index]);
	}
	free(partitions);
	return result;
}

void parse_range(const char *range, uint64_t *start, uint64_t *end) {
	
	*start = 0;
	*end   = 0;
	
	char c;
	
	while ((c = *range++) != '-') {
		*start *= 10;
		*start += (c - '0');
	}
	
	while((c = *range++) != '\0') {
		*end *= 10;
		*end += (c - '0');
	}
}

uint64_t check_ranges(const char *range) {
	
	uint64_t start, end;
	uint64_t sum = 0;
	parse_range(range, &start, &end);
	
	char buf[MAX_STR_LEN];
	
	for (uint64_t index = start; index <= end; ++index) {
		
		if (is_invalid(int_to_str(index, buf))) {
			
			sum += index;
		}
	}
	
	return sum;
}

int main(int argc, char **argv) {
	
	char *input;
	if (init_aoc(argc, argv, &input)) {
		
		return EXIT_FAIL;
	}
	
	uint64_t sum = 0;
	char *range = strtok(input, ",");
	while (range != NULL) {
		
		sum += check_ranges(range);
		range = strtok(NULL, ",");
	}
	
	clean_aoc(sum, input);
	return EXIT_SUCESS;
}
