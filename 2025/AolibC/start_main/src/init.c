#include <syscall.h>

extern void *__curr_brk;

void _init(void) {
	
	__curr_brk = (void *)(__syscall_1(SYS_BRK, 0));
}

