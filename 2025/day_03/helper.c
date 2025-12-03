#include "helper.h"

#include <stdio.h>

void swap(void *v1, void *v2) {
	
	char tmp = *(char *)(v1);
	*(char *)(v1) = *(char *)(v2);
	*(char *)(v2) = tmp;
}

char *reverse_str(char *str) {
	
	int len = strlen(str);
	
	for (int i = 0; i < len / 2; ++i) {
		swap(str + i, str + len - i - 1);
	}
	
	return str;
}

char *int_to_str(u64 num, char *buf) {
	
	if (num == 0) {
		
		buf[0] = '0';
		buf[1] = '\0';
		return buf;
	}

	int i = 0;
	
	while (num) {
		buf[i++] = '0' + (num % 10);
		num /= 10;
	}
	buf[i] = '\0';
	
	reverse_str(buf);
	return buf;
}

void print_num(u64 num) {
	
	char buf[MAX_STR_LEN];
	int_to_str(num, buf);
	puts(buf);
}

