#include <unistd.h>
#include <syscall.h>

ssize_t read(int file_descriptor, void *buf, size_t count) {
	
	return __syscall_3(SYS_READ, (uint64_t)(file_descriptor), (uint64_t)(buf), (uint64_t)(count));
}

ssize_t write(int file_descriptor, const void *buf, size_t count) {
	
	return __syscall_3(SYS_WRITE, (uint64_t)(file_descriptor), (uint64_t)(buf), (uint64_t)(count));
}

int close(int file_descriptor) {
	
	return __syscall_1(SYS_CLOSE, (uint64_t)(file_descriptor));
}

