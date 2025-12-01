#include "../include/syscall.h"

void exit(int status) {
	
	__syscall_1(SYS_EXIT, status);
	__builtin_unreachable();
}

