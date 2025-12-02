#include "helper.h"

void putc(char c) {
	
	__syscall_3(SYS_WRITE, 0, (u64)(&c), 1);
}

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

