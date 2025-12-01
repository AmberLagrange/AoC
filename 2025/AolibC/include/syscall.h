#ifndef SYSCALL_H
#define SYSCALL_H

#define SYS_READ	0
#define SYS_WRITE	1
#define SYS_EXIT	60

typedef unsigned long long u64;

unsigned long __syscall_0(u64 syscall);
unsigned long __syscall_1(u64 syscall, u64 rdi);
unsigned long __syscall_2(u64 syscall, u64 rdi, u64 rsi);
unsigned long __syscall_3(u64 syscall, u64 rdi, u64 rsi, u64 rdx);
unsigned long __syscall_4(u64 syscall, u64 rdi, u64 rsi, u64 rdx, u64 r10);
unsigned long __syscall_5(u64 syscall, u64 rdi, u64 rsi, u64 rdx, u64 r10, u64 r8);
unsigned long __syscall_6(u64 syscall, u64 rdi, u64 rsi, u64 rdx, u64 r10, u64 r8, u64 r9);

#endif

