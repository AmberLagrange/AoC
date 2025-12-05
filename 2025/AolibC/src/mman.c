#include <mman.h>

#include <syscall.h>

void *mmap(void *addr, size_t len, int prot, int flags, int fd, int offset) {
	
	return (void *)__syscall_6(SYS_MMAP, (uint64_t)(addr), (uint64_t)(len), (uint64_t)(prot), (uint64_t)(flags), (uint64_t)(fd), (uint64_t)(offset));
}

int munmap(void *addr, size_t len) {
	
	return __syscall_2(SYS_MUNMAP, (uint64_t)(addr), (uint64_t)(len));
}

