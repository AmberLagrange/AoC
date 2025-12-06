#include <common.h>

#include <stdio.h>
#include <stdlib.h>

#define flatten_coords(row, col, width, height) ((row) * (width) + (col))

#define MAX_PROBLEMS 1024
#define MAX_LINES 4

int main(int argc, char **argv) {
	
	char *input;
	if (init_aoc(argc, argv, &input)) {
		
		return EXIT_FAIL;
	}
	
	size_t input_len = strlen(input);
	
	char *input_copy = malloc(input_len + 1);
	memcpy(input_copy, input, input_len);
	input_copy[input_len] = '\0';
	
	
	char *line = strtok(input_copy, "\n");
	
	int problems[MAX_LINES][MAX_PROBLEMS];
	char operations[MAX_PROBLEMS];
	size_t num_index = 0;
	size_t line_num = 0;
	
	char *state = malloc(1024);
	const char *number;
	size_t num_problems;
	while (line_num < MAX_LINES) {
		
		number = strtok_r(line, " ", &state);
		
		num_index = 0;
		while (number != NULL) {
			
			if (number[0] == '\0') {
				
				number = strtok_r(NULL, " ", &state);
				continue;
			}
			
			problems[line_num][num_index] = atoll(number);
			++num_index;
			number = strtok_r(NULL, " ", &state);
		}
		
		num_problems = num_index - 1;
		problems[line_num][num_index] = -1;
		++line_num;
		line = strtok(NULL, "\n");
	}
	
	num_index = 0;
	const char *operation = strtok_r(line, " ", &state);
	while (operation != NULL) {
		
		if (operation[0] == '\0') {
			
			operation = strtok_r(NULL, " ", &state);
			continue;
		}
		operations[num_index] = operation[0];
		++num_index;
		operation = strtok_r(NULL, " ", &state);
	}

	operations[num_index] = '\0';
	
	uint64_t grand_total = 0;
	uint64_t val;
	
	for (size_t index = 0; index <= num_problems; ++index) {
		
		if (problems[0][index] == -1) {
			
			break;
		}
		
		if (operations[index] == '*') {
			
			val = 1;
			for (size_t line_num = 0; line_num < MAX_LINES; ++line_num) {
				
				val *= problems[line_num][index];
			}
			
		} else {
			
			val = 0;
			for (size_t line_num = 0; line_num < MAX_LINES; ++line_num) {
				
				val += problems[line_num][index];
			}
		}
	
		print_num(val);
		puts("\n");
		grand_total += val;
		
	}
	
	free(state);
	free(input_copy);
	clean_aoc(grand_total, input);
	return EXIT_SUCCESS;
}

