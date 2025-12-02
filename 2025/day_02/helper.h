#include "../AolibC/include/syscall.h"

#define NULL ((void *)(0))
#define MAX_STR_LEN 1024

int putc(const char c);

int puts(const char *str, int count);

unsigned long strlen(const char *str);

int strcmp(const char *str_1, const char *str_2);

char *strncpy(char *dst, const char *src, unsigned long count);

void swap(void *v1, void *v2);

char *reverse_str(char *str);

char *int_to_str(u64 num, char *buf);

void print_num(u64 num);

char *strtok(char *str, const char *delims);

