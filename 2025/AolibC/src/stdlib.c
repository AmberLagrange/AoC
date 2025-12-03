#include <stdlib.h>

#include <syscall.h>

// Ignore negatives for now
int atoi(const char *str) {
	
	int value = 0;
	char c;
	while ((c = *str)) {
		
		value *= 10;
		value += (int)(c - '0');
		++str;
	}
	
	return value;
}

long atol(const char *str) {
	
	long value = 0;
	char c;
	while ((c = *str)) {
		
		value *= 10;
		value += (int)(c - '0');
		++str;
	}
	
	return value;
}

long long atoll(const char *str) {
	
	long long value = 0;
	char c;
	while ((c = *str)) {
		
		value *= 10;
		value += (long long)(c - '0');
		++str;
	}
	
	return value;
}

__attribute__((noreturn)) void exit(int status) {
	
	__syscall_1(SYS_EXIT, status);
	__builtin_unreachable();
}

