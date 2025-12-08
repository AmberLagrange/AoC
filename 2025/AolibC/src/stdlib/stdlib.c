#include <stdlib.h>

#include <mman.h>
#include <string.h>
#include <syscall.h>
#include <unistd.h>

#define NEXT_MULTIPLE(number, multiple) ((number) + (multiple) - 1) - (((number) + (multiple) - 1) % (multiple))

enum {
	
	SBRK_ALLOC_SIZE    = 0x00100,
	SBRK_MAX_HEAP_SIZE = 0x40000
};

enum {
	
	MALLOC_MODE_FREE = 0,
	MALLOC_MODE_SBRK = 1,
	MALLOC_MODE_MMAP = 2
};

typedef struct malloc_block_t {
	
	size_t memory_size;
	int malloc_mode;
	struct malloc_block_t *next_block;
} malloc_block_t;

enum {
	
	MIN_ALIGNMENT     = 16,
	MALLOC_BLOCK_SIZE = NEXT_MULTIPLE(sizeof(malloc_block_t), MIN_ALIGNMENT)
};

static malloc_block_t *__free_list_head;
static malloc_block_t *__free_list_tail;

static size_t __total_sbrk_allocated;

void __init_malloc(void) {
	
	__free_list_head = sbrk(SBRK_ALLOC_SIZE);
	__free_list_head->malloc_mode = MALLOC_MODE_FREE;
	__free_list_head->next_block = NULL;
	
	__free_list_tail = __free_list_head;
	
	__total_sbrk_allocated = SBRK_ALLOC_SIZE;
}

void __cleanup_malloc(void) {
	
	sbrk(-__total_sbrk_allocated);
}

malloc_block_t *__find_next_free(void) {
	
	malloc_block_t *curr_block = __free_list_head;
	while ((curr_block != NULL) && (curr_block->malloc_mode != MALLOC_MODE_FREE)) {
		
		curr_block = curr_block->next_block;
	}
	
	return curr_block;
}

void *malloc(size_t len) {
	
	if (len == 0) {
		
		return NULL;
	}
	
	unsigned char *base_addr;
	malloc_block_t *new_block;
	
	if ((len + MALLOC_BLOCK_SIZE <= SBRK_ALLOC_SIZE) && (__total_sbrk_allocated < SBRK_MAX_HEAP_SIZE)) {
		
		malloc_block_t *free_block = __find_next_free();
		
		if (free_block == NULL) {
			
			new_block = sbrk(SBRK_ALLOC_SIZE);
			new_block->next_block = NULL;
			
			__free_list_tail->next_block = new_block;
			__free_list_tail = new_block;
			
			__total_sbrk_allocated += SBRK_ALLOC_SIZE;
		} else {
				
			new_block = free_block;
		}
		
		new_block->memory_size = len;
		new_block->malloc_mode = MALLOC_MODE_SBRK;
	} else {
		
		new_block = mmap(NULL, len + MALLOC_BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		if ((unsigned long)(new_block) < 0) {
			
			return NULL;
		}
		
		new_block->memory_size = len;
		new_block->malloc_mode = MALLOC_MODE_MMAP;
		new_block->next_block = NULL;
	}
	
	base_addr = (unsigned char*)(new_block);
	*(malloc_block_t *)(base_addr) = *new_block;
	return (void *)(base_addr + MALLOC_BLOCK_SIZE);
}

void free(void *ptr_addr) {
	
	if (ptr_addr == NULL) {
		
		return;
	}
	
	unsigned char *base_addr = ((unsigned char *)(ptr_addr) - MALLOC_BLOCK_SIZE);
	malloc_block_t *block = (malloc_block_t *)(base_addr);
	
	if (block->malloc_mode == MALLOC_MODE_MMAP) {
			
		munmap(base_addr, block->memory_size + MALLOC_BLOCK_SIZE);
	} else {
		
		block->malloc_mode = MALLOC_MODE_FREE;
	}
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

