#include <stdlib.h>

#include <syscall.h>

extern int main(int argc, char **argv);
extern void _init(void);

void __attribute__((naked)) _start(void) {
	
	__asm__ volatile (
		"movl (%rsp), %edi\n\t"
		"lea 8(%rsp), %rsi\n\t"
		"call __start_main\n\t"
	);
}

void __start_main(int argc, char **argv) {

	_init();
	exit(main(argc, argv));
}

