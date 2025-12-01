#include "../include/syscall.h"

unsigned long __syscall_0(u64 syscall) {
	
	unsigned long ret;
	__asm__ volatile (
		"movq %1, %%rax\n\t"
		"syscall	   \n\t"
		"mov %%rax, %0 \n\t"
		
		: "=r" (ret)
		: "r"  (syscall)
		: "%rax"
	);
	
	return ret;
}

unsigned long __syscall_1(u64 syscall, u64 rdi) {
	
	unsigned long ret;
	__asm__ volatile (
		"movq %1, %%rax\n\t"
		"movq %2, %%rdi\n\t"
		"syscall	   \n\t"
		"mov %%rax, %0 \n\t"
		
		: "=r" (ret)
		: "r"  (syscall),
		  "r"  (rdi)
		: "%rax", "%rdi"
	);
	
	return ret;
}

unsigned long __syscall_2(u64 syscall, u64 rdi, u64 rsi) {
	
	unsigned long ret;
	__asm__ volatile (
		"movq %1, %%rax\n\t"
		"movq %2, %%rdi\n\t"
		"movq %3, %%rsi\n\t"
		"syscall	   \n\t"
		"mov %%rax, %0 \n\t"
		
		: "=r" (ret)
		: "r"  (syscall),
		  "r"  (rdi),
		  "r"  (rsi)
		: "%rax", "%rdi", "%rsi"
		);
	
	return ret;
}

unsigned long __syscall_3(u64 syscall, u64 rdi, u64 rsi, u64 rdx) {
	
	unsigned long ret;
	__asm__ volatile (
		"movq %1, %%rax\n\t"
		"movq %2, %%rdi\n\t"
		"movq %3, %%rsi\n\t"
		"movq %4, %%rdx\n\t"
		"syscall	   \n\t"
		"mov %%rax, %0 \n\t"
		
		: "=r" (ret)
		: "r"  (syscall),
		  "r"  (rdi),
		  "r"  (rsi),
		  "r"  (rdx)
		: "rax", "rdi", "rsi", "rdx"
		);
	
	return ret;
}

