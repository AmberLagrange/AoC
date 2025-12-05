#include <stdio.h>
#include <string.h>

#include <helper.h>

int main(int argc, char **argv) {
	
	char *input;
	if (init_aoc(argc, argv, &input)) {
		
		return EXIT_FAIL;
	}
	
	int  val   = 0;
	char dir   = '0';
	int  dial  = 50;
	int  count = 0;
	size_t len = strlen(input);
	
	for (size_t index = 0; index < len; ++index) {
		
		char c = input[index];
		
		if (c == '\n') {
			
			if (dir == 'L') {
				dial -= val;
				dial += 100;	
			} else if (dir == 'R') {
				dial += val;
			}
			dial = dial % 100;
			
			if (dial == 0) {
				++count;
			}
			
			val = 0;
		} else if (c == 'L' || c == 'R') {
			dir = c;
		} else {
			val *= 10;
			val += (c - '0');
		}
		
	}
	
	clean_aoc(count, input);
	return EXIT_SUCESS;
}

