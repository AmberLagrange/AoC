#include <string.h>
#include <syscall.h>

#define MAX_STR_LEN 1024

void swap(void *v1, void *v2);

char *reverse_str(char *str);

char *int_to_str(u64 num, char *buf);

int atoi(const char *str);
long long atoll(const char *str);

void print_num(u64 num);

