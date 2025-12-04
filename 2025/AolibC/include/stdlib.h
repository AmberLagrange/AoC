#ifndef STDLIB_H
#define STDLIB_H

#ifndef SIZE_T
#define SIZE_T
typedef unsigned long size_t;
#endif

#ifndef NULL
#define NULL ((void *)(0))
#endif

void *malloc(size_t len);
void  free(void *addr);

int atoi(const char *str);
long atol(const char *str);
long long atoll(const char *str);

__attribute__((noreturn)) void exit(int status);

#endif // STDLIB_H

