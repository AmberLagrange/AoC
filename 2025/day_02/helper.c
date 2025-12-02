#include "helper.h"

int putc(const char c) {
	
	return __syscall_3(SYS_WRITE, 0, (u64)(&c), 1);
}

int puts(const char *str, int count) {
	
	if (str == NULL) {
		return 0;
	}
	
	return __syscall_3(SYS_WRITE, 0, (u64)(str), count);
}

unsigned long strlen(const char *str) {
	
	if (str == NULL) {
		return 0;
	}
	
	unsigned long count = 0;
	while (*str++) {
		++count;
	}
	
	return count;
}

int strcmp(const char *str_1, const char *str_2) {
	
	int str_1_len = strlen(str_1);
	int str_2_len = strlen(str_2);
	
	if (str_1_len < str_2_len) {
		return -1;
	} else if (str_1_len > str_2_len) {
		return 1;
	}

	for (int i = 0; i < str_1_len; ++i) {
		
		if (str_1[i] < str_2[i]) {
			return -1;
		} else if (str_1[i] > str_2[i]) {
			return 1;
		}
	}
	
	return 0;
}

char *strncpy(char *dst, const char *src, unsigned long count) {
	
	unsigned int i = 0;
	while (*src && i < count) {
		
		dst[i] = src[i];
		++i;
	}
	
	return dst;
}

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
	int len = strlen(buf);
	puts(buf, len);
}

char *__strtok_str;

char *strtok(char *str, const char *delims) {
	
	if (str != NULL) {
		__strtok_str = str;
	}
	
	int str_len = strlen(__strtok_str);
	int delim_len = strlen(delims);
	
	char *prev_str = __strtok_str;
	for (int i = 0; i < str_len; ++i) {
		
		for (int d = 0; d < delim_len; ++d) {
			
			if (__strtok_str[i] == delims[d]) {
				
				__strtok_str[i] = '\0';
				__strtok_str = __strtok_str + i + 1;
				return prev_str;
			}
		}
	}
	
	if (__strtok_str != NULL) {
		__strtok_str = NULL;
	}
	
	return prev_str;
}

