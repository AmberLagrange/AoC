#include <fcntl.h>
#include <syscall.h>

int open(const char *file_path, int flags, mode_t mode) {
	
	return __syscall_3(SYS_OPEN, (uint64_t)(file_path), flags, mode);
}

