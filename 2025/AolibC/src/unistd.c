#include <unistd.h>
#include <syscall.h>

ssize_t read(int file_descriptor, void *buf, size_t count) {
	
	return __syscall_3(SYS_READ, file_descriptor, (u64)(buf), count);
}

ssize_t write(int file_descriptor, const void *buf, size_t count) {
	
	return __syscall_3(SYS_WRITE, file_descriptor, (u64)(buf), count);
}

int close(int file_descriptor) {
	
	return __syscall_1(SYS_CLOSE, file_descriptor);
}

