#include <common.h>

#include <stdio.h>
#include <string.h>

#define LINE_LEN 141

int main(int argc, char **argv) {
	
	char *input;
	if (init_aoc(argc, argv, &input)) {
		
		return EXIT_FAIL;
	}
	
	uint64_t paths = 0;

	const char *line = strtok(input, "\n");
	char curr_row[LINE_LEN + 1];
	char prev_row[LINE_LEN + 1];
	
	uint64_t curr_paths[LINE_LEN + 1];
	uint64_t prev_paths[LINE_LEN + 1];
	for (size_t index = 0; index < LINE_LEN; ++index) {
		
		curr_paths[index] = prev_paths[index] = 0;
	}

	memcpy(curr_row, line, LINE_LEN + 1);
	
	while(line != NULL) {
		
		memcpy(prev_row, curr_row, LINE_LEN + 1);
		memcpy(curr_row, line, LINE_LEN + 1);
		
		memcpy(prev_paths, curr_paths, sizeof(uint64_t) * (LINE_LEN + 1));
		
		for (size_t col = 0; col < LINE_LEN; ++col) {
			
			if (prev_row[col] == 'S' || prev_row[col] == '|') {
				
				if (prev_row[col] == 'S') {
					
					curr_paths[col] = 1;
				}
				
				if (curr_row[col] == '^') {
					
					curr_row[col - 1] = curr_row[col + 1] = '|';
					curr_paths[col - 1] += prev_paths[col];
					curr_paths[col + 1] += prev_paths[col];
					curr_paths[col] = 0;
					
				} else {
					
					curr_row[col] = '|';
				}
			}
		}
		
		line = strtok(NULL, "\n");
	}
	
	for (size_t col = 0; col < LINE_LEN; ++col) {
		paths += curr_paths[col];
	}
	
	clean_aoc(paths, input);
	return EXIT_SUCCESS;
}

