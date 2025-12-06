#include <common.h>

#include <stdio.h>
#include <stdlib.h>

#define flatten_coords(row, col, width, height) ((row) * (width) + (col))

#define MAX_PROBLEMS 1024
#define MAX_LINES 4
#define MAX_NUM_LEN 4

uint64_t strip_atoll(char *str) {
	
	while (*str == ' ') {
		
		++str;
	}
	
	size_t len = strlen(str);
	for(size_t index = 0; index < len; ++index) {
		
		if (str[index] == ' ') {
			
			str[index] = '\0';
		}
	}
	
	return atoll(str);
}

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
	
	size_t line_num = 0;
	while (line_num < MAX_LINES) {
		
		line = strtok(NULL, "\n");
		++line_num;
	}
	
	size_t problem_lens[MAX_PROBLEMS];
	size_t problem_len;
	size_t num_problems = 0;
	++line; // since we start with an operation
	for (size_t problem_index = 0; problem_index < MAX_PROBLEMS; ++problem_index) {
		
		problem_len = 0;
		char c;
		while ((c = *line++)) {
			
			if (c == ' ') {
				
				++problem_len;
			} else {
				
				break;
			}
		}
			
		++num_problems;
		problem_lens[problem_index] = problem_len;
		if (c == '\0') {
			
			++problem_lens[problem_index];
			break;
		}
	}
	
	line = strtok(input, "\n");
	
	char problems[MAX_LINES][MAX_PROBLEMS][MAX_NUM_LEN + 1];
	char operations[MAX_PROBLEMS];
	size_t num_index = 0;
	line_num = 0;
	
	char *state = malloc(1024);
	for (size_t line_num = 0; line_num < MAX_LINES; ++line_num) {
		
		const char *number = line;
		for (size_t problem_index = 0; problem_index < num_problems; ++problem_index) {
			
			size_t curr_len = problem_lens[problem_index];
			memcpy(problems[line_num][problem_index], number, curr_len);
			problems[line_num][problem_index][curr_len] = '\0';
			
			number += (curr_len + 1);
		}
		
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
	
	char col_numbers[MAX_NUM_LEN][MAX_PROBLEMS][MAX_LINES + 1];
	
	for (size_t problem_index = 0; problem_index < num_problems; ++problem_index) {
		
		for (size_t line_num = 0; line_num < MAX_LINES; ++line_num) {
			
			for (size_t digit = 0; digit < MAX_NUM_LEN; ++digit) {
				
				col_numbers[line_num][problem_index][digit] = problems[digit][problem_index][line_num];
				col_numbers[line_num][problem_index][MAX_NUM_LEN] = '\0';
			}
		}
	}
	
	uint64_t grand_total = 0;
	uint64_t val;
	for (size_t problem_index = 0; problem_index < num_problems; ++problem_index) {
		
		if (operations[problem_index] == '*') {
			
			val = 1;
			for (size_t col_index = 0; col_index < MAX_NUM_LEN; ++col_index) {
				
				size_t curr_val = strip_atoll(col_numbers[col_index][problem_index]);
				if (curr_val != 0) {
					
					val *= curr_val;
				}
			}
		} else {
			
			val = 0;
			for (size_t col_index = 0; col_index < MAX_NUM_LEN; ++col_index) {
				
				val += strip_atoll(col_numbers[col_index][problem_index]);
			}
		}
		
		grand_total += val;
	}
	
	free(state);
	free(input_copy);
	clean_aoc(grand_total, input);
	return EXIT_SUCCESS;
}

