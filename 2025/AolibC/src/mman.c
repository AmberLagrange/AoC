#include <mman.h>

#include <syscall.h>

void *mmap(void *addr, size_t len, int prot, int flags, int fd, int offset) {
	
	return (void *)__syscall_6(SYS_MMAP, (u64)(addr), (u64)(len), (u64)(prot), (u64)(flags), (u64)(fd), (u64)(offset));
}

int munmap(void *addr, size_t len) {
	
	return __syscall_2(SYS_MUNMAP, (u64)(addr), (u64)(len));
}

