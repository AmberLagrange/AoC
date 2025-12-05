#include <string.h>

#include <helper.h>

int main(int argc, char **argv) {
	
	char *input;
	if (init_aoc(argc, argv, &input)) {
		
		return EXIT_FAIL;
	}
	
	int  input_val = 0;
	char direction = '0';
	
	int curr_dial = 50;
	int dial_count = 0;
	
	size_t len = strlen(input);
	
	for (size_t index = 0; index < len; ++index) {
		
		char input_char = input[index];
		if (input_char == '\n') {
			
			if (direction == 'L') {
				
				if (curr_dial == 0) {
					
					--dial_count;
				}
				
				curr_dial -= input_val;
				while (curr_dial < 0) {
					
					curr_dial += 100;
					++dial_count;
				}
				
				if (curr_dial == 0) {
					
					++dial_count;
				}
			} else if (direction == 'R') {
				
				curr_dial += input_val;
				while (curr_dial >= 100) {
					
					curr_dial -= 100;
					++dial_count;
				}
			}
			
			input_val = 0;
			
		} else if (input_char == 'L' || input_char == 'R') {
			
			direction = input_char;
		} else {
			
			input_val *= 10;
			input_val += (input_char - '0');
		}
	}
	++dial_count;
	
	clean_aoc(dial_count, input);
	return EXIT_SUCCESS;
}

