#include <common.h>

#include <stdio.h>
#include <string.h>

#define LINE_LEN 141

int main(int argc, char **argv) {
	
	char *input;
	if (init_aoc(argc, argv, &input)) {
		
		return EXIT_FAIL;
	}
	
	uint64_t splits = 0;

	const char *line = strtok(input, "\n");
	char curr_row[LINE_LEN + 1];
	char prev_row[LINE_LEN + 1];
	memcpy(curr_row, line, LINE_LEN + 1);
	
	while(line != NULL) {
		
		memcpy(prev_row, curr_row, LINE_LEN + 1);
		memcpy(curr_row, line, LINE_LEN + 1);
		
		for (size_t col = 0; col < LINE_LEN; ++col) {
			
			if (prev_row[col] == 'S' || prev_row[col] == '|') {
				
				if (curr_row[col] == '^') {
					
					++splits;
					curr_row[col - 1] = curr_row[col + 1] = '|';
				} else {
					
					curr_row[col] = '|';
				}
			}
			
		}
		
		line = strtok(NULL, "\n");
	}
	
	clean_aoc(splits, input);
	return EXIT_SUCCESS;
}

