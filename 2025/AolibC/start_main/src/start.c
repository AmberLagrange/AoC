#include <stdlib.h>

extern int main(int argc, char **argv);

void __attribute__((naked)) _start(void) {
	
	__asm__ volatile (
		"movl (%rsp), %edi\n\t"
		"lea 8(%rsp), %rsi\n\t"
		"call __start_main\n\t"
	);
}

void __start_main(int argc, char **argv) {
	
	int result;
	result = main(argc, argv);
	exit(result);
}

