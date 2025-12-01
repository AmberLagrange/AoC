extern int main(int argc, char **argv);
extern void exit(int status);

void __attribute((naked)) _start() {
	
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

