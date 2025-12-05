#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <common.h>

#define MAX_INPUT_LEN 16

int is_invalid(const char *str, char **partition_list, size_t max_partitions) {
	
	size_t len = strlen(str);
	for (size_t num_partitions = 2; num_partitions < max_partitions; ++num_partitions) {
		
		if (len % num_partitions != 0) {
			
			continue;
		}
		
		size_t split_len = len / num_partitions;
		
		for (size_t partition = 0; partition < num_partitions; ++partition) {
			
			strncpy(partition_list[partition], str + split_len * partition, split_len);
			partition_list[partition][split_len] = '\0';
		}
		
		int invalid = 1;	
		for (size_t partition = 1; partition < num_partitions; ++partition) {
			
			if (strcmp(partition_list[0], partition_list[partition]) != 0) {
				
				invalid = 0;
				break;
			}
			
		}
		
		if (invalid) {
			
			return 1;
		}
	}
	
	return 0;
}

uint64_t check_ranges(const char *range, char **partition_list, size_t size) {
	
	uint64_t start, end;
	uint64_t sum = 0;
	parse_range(range, &start, &end);
	
	char buf[MAX_STR_LEN];
	for (uint64_t index = start; index <= end; ++index) {
		
		if (is_invalid(int_to_str(index, buf), partition_list, size)) {
			
			sum += index;
		}
	}
	
	return sum;
}

int main(int argc, char **argv) {
	
	int status = EXIT_SUCCESS;
	
	char *input;
	if (init_aoc(argc, argv, &input)) {
		
		return EXIT_FAIL;
	}
	
	uint64_t sum = 0;
	
	char **partition_list = malloc(MAX_INPUT_LEN);
	if (partition_list == NULL) {
		
		puts("Error: could not allocate memory for the partition list.\n");
		status = EXIT_FAIL;
		goto cleanup;
	}
	
	char *partitions = malloc(sizeof(uint64_t) * MAX_STR_LEN * MAX_INPUT_LEN);
	if (partitions == NULL) {
		
		puts("Error: could not allocate memory for the partitions.\n");
		status = EXIT_FAIL;
		goto partition_free;
	}
	
	for (size_t index = 0; index < MAX_INPUT_LEN; ++index) {
		
		partition_list[index] = (partitions + index * MAX_STR_LEN);
	}
	
	char *range = strtok(input, ",");
	while (range != NULL) {
		
		sum += check_ranges(range, partition_list, MAX_INPUT_LEN);
		range = strtok(NULL, ",");
	}
	
	free(partitions);
partition_free:
	free(partition_list);
	
cleanup:
	clean_aoc(sum, input);
	return status;
}

