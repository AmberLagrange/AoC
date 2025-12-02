#include <stdio.h>

#include <string.h>
#include <syscall.h>

int putc(const char c) {
	
	return __syscall_3(SYS_WRITE, 0, (u64)(&c), 1);
}

int puts(const char *str) {
	
	size_t len = strlen(str);
	return __syscall_3(SYS_WRITE, 0, (u64)(str), len);
}

