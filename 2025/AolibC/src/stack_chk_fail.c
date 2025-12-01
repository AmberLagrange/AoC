extern void exit(int status);

void __attribute__((noreturn)) __stack_chk_fail(void) {
	exit(-1);
}

