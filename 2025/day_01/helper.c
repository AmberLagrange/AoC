#include "helper.h"

#include <stdio.h>

void print_num(int num) {

	if (num == 0) {
		puts("0\n");
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
		putc(buf[--i], stdout);
	}
	putc('\n', stdout);
}

