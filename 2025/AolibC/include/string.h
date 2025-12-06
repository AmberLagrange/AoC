#ifndef STRING_H
#define STRING_H

#ifndef SIZE_T
#define SIZE_T
typedef unsigned long size_t;
#endif

#ifndef NULL
#define NULL ((void *)(0))
#endif

void *memcpy(void *dst, const void *src, size_t count);

size_t strlen(const char *str);

int strcmp(const char *lhs, const char *rhs);

char *strncpy(char *dst, const char *str, size_t count);

char *strtok(char *str, const char *delims);
char *strtok_r(char *str, const char *delims, char **state);

#endif // STRING_H

