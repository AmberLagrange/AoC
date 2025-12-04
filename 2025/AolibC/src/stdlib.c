#include <stdlib.h>

#include <mman.h>
#include <string.h>
#include <syscall.h>

#define NEXT_MULTIPLE(number, multiple) ((number) + (multiple) - 1) - (((number) + (multiple) - 1) % (multiple))

typedef struct {
	
	size_t memory_size;
	int foo;
	int bar;
	int baz;
} malloc_block_t;

enum {
	
	MIN_ALIGNMENT = 16,
	ALIGNMENT_LEN = NEXT_MULTIPLE(sizeof(malloc_block_t), MIN_ALIGNMENT)
};

void *malloc(size_t len) {
	
	if (len == 0) {
		
		return NULL;
	}
	
	malloc_block_t block;
	block.memory_size = len + ALIGNMENT_LEN;

	unsigned char *ptr_addr = mmap(NULL, block.memory_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if ((unsigned long)(ptr_addr) < 0) {
		
		return NULL;
	}
	
	// Store the malloc block struct before the memory
	*(malloc_block_t *)(ptr_addr) = block;
	
	return (void *)(ptr_addr + ALIGNMENT_LEN);
}


void free(void *ptr_addr) {
	
	if (ptr_addr == NULL) {
		
		return;
	}
	
	malloc_block_t block = *((malloc_block_t *)((unsigned char *)(ptr_addr) - ALIGNMENT_LEN));
	munmap(ptr_addr, block.memory_size);
}

// Ignore negatives for now
int atoi(const char *str) {
	
	int value = 0;
	char c;
	while ((c = *str)) {
		
		value *= 10;
		value += (int)(c - '0');
		++str;
	}
	
	return value;
}

long atol(const char *str) {
	
	long value = 0;
	char c;
	while ((c = *str)) {
		
		value *= 10;
		value += (int)(c - '0');
		++str;
	}
	
	return value;
}

long long atoll(const char *str) {
	
	long long value = 0;
	char c;
	while ((c = *str)) {
		
		value *= 10;
		value += (long long)(c - '0');
		++str;
	}
	
	return value;
}

__attribute__((noreturn)) void exit(int status) {
	
	__syscall_1(SYS_EXIT, status);
	__builtin_unreachable();
}

