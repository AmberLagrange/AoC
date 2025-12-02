#include "input.xxd"

#include "helper.h"

int main(void) {
	
	int  val   = 0;
	char dir   = '0';
	int  dial  = 50;
	int  count = 0;
	
	char c;
	
	for (unsigned int i = 0; i < input_len; ++i) {
		
		c = input[i];
		
		if (c == '\n') {
			
			if (dir == 'L') {
				if (dial == 0) {
					--count;
				}
				dial -= val;
				while (dial < 0) {
					dial += 100;
					++count;
				}
				if (dial == 0) {
					++count;
				}
			} else if (dir == 'R') {
				dial += val;
				while (dial >= 100) {
					dial -= 100;
					++count;
				}
			}
			
			val = 0;
		} else if (c == 'L' || c == 'R') {
			dir = c;
		} else {
			val *= 10;
			val += (c - '0');
		}
		
	}
	
	print_num(count);
	return 0;
}

