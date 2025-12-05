#ifndef SYSCALL_H
#define SYSCALL_H

enum {
	SYS_READ   = 0,
	SYS_WRITE  = 1,
	SYS_OPEN   = 2,
	SYS_CLOSE  = 3,
	SYS_MMAP   = 9,
	SYS_MUNMAP = 11,
	SYS_EXIT   = 60
};

typedef unsigned long long uint64_t;

uint64_t __syscall_0(uint64_t syscall);
uint64_t __syscall_1(uint64_t syscall, uint64_t rdi);
uint64_t __syscall_2(uint64_t syscall, uint64_t rdi, uint64_t rsi);
uint64_t __syscall_3(uint64_t syscall, uint64_t rdi, uint64_t rsi, uint64_t rdx);
uint64_t __syscall_4(uint64_t syscall, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10);
uint64_t __syscall_5(uint64_t syscall, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8);
uint64_t __syscall_6(uint64_t syscall, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9);

#endif //SYSCALL_H

