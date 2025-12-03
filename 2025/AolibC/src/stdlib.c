#include <stdlib.h>

#include <syscall.h>

__attribute__((noreturn)) void exit(int status) {
	
	__syscall_1(SYS_EXIT, status);
	__builtin_unreachable();
}

