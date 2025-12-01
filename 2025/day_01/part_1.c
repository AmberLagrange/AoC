#include "input.xxd"

#include "../AolibC/include/syscall.h"

void putc(char c) {
	
	__syscall_3(SYS_WRITE, 0, (u64)(&c), 1);
};

void print_str(char *str) {
	
	char c;
	while((c = *str++)) {
		putc(c);
	}
}

void print_num(int num) {

	if (num == 0) {
		print_str("0\n");
		return;
	}

	char buf[10];
	int i = 0;
	int digit;

	while (num && i < 10) {
		
		digit = num % 10;
		buf[i++] = '0' + digit;
		num -= digit;
		num /= 10;
	}
	
	while (i > 0) {
		putc(buf[--i]);
	}
	putc('\n');
}

int main() {
	
	int  val   = 0;
	char dir   = '0';
	int  dial  = 50;
	int  count = 0;
	
	char c;
	
	for (int i = 0; i < input_len; ++i) {
		
		c = input[i];
		
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
	
	print_num(count);
	return 0;
}

