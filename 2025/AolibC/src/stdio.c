#include <stdio.h>

#include <string.h>
#include <syscall.h>

static FILE __stdin  = {0};
static FILE __stdout = {1};
static FILE __stderr = {2};

FILE *__files[FOPEN_MAX] = { &__stdin, &__stdout, &__stderr };

int putc(int c, FILE *file) {
	
	return __syscall_3(SYS_WRITE, file->fd, (u64)(&c), 1);
}

int puts(const char *str) {
	
	size_t len = strlen(str);
	return __syscall_3(SYS_WRITE, 0, (u64)(str), len);
}

