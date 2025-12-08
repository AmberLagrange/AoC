#include <stdio.h>

#include <string.h>
#include <syscall.h>

static FILE __stdin  = {0};
static FILE __stdout = {1};
static FILE __stderr = {2};

FILE *__files[FOPEN_MAX] = { &__stdin, &__stdout, &__stderr };

int putc(int c, FILE *file) {
	
	return __syscall_3(SYS_WRITE, (uint64_t)(file->fd), (uint64_t)(&c), 1ULL);
}

int puts(const char *str) {
	
	size_t len = strlen(str);
	return __syscall_3(SYS_WRITE, (uint64_t)(stdout->fd), (uint64_t)(str), (uint64_t)(len));
}

