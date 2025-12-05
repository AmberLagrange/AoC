#include <stdint.h>
#include <string.h>

#define MAX_STR_LEN 1024

void swap(void *v1, void *v2);

char *reverse_str(char *str);

char *int_to_str(uint64_t num, char *buf);

void print_num(uint64_t num);

