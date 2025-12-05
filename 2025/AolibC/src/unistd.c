#include <unistd.h>
#include <syscall.h>

#define NULL ((void*)(0))

ssize_t read(int file_descriptor, void *buf, size_t count) {
	
	return __syscall_3(SYS_READ, (uint64_t)(file_descriptor), (uint64_t)(buf), (uint64_t)(count));
}

ssize_t write(int file_descriptor, const void *buf, size_t count) {
	
	return __syscall_3(SYS_WRITE, (uint64_t)(file_descriptor), (uint64_t)(buf), (uint64_t)(count));
}

int close(int file_descriptor) {
	
	return __syscall_1(SYS_CLOSE, (uint64_t)(file_descriptor));
}

void *__curr_brk = NULL;

int brk(void *addr) {
	
	if (__syscall_1(SYS_BRK, (uint64_t)(addr))) {
		
		return -1;
	}
	
	return 0;
}

void *sbrk(intptr_t inc) {
	
	if (inc == 0) {
		
		return __curr_brk;
	}
	
	void *prev_brk = __curr_brk;
	
	brk((unsigned char *)(__curr_brk) + inc);
	return prev_brk;
}

pid_t getpid(void) {
	
	return __syscall_0(SYS_GETPID);
}

