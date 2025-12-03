#ifndef STDIO_H
#define STDIO_H

#define FOPEN_MAX 256

typedef struct {
	int fd;
} FILE;

int putc(int c, FILE *file);

int puts(const char *str);

extern FILE *__files[FOPEN_MAX];

#define stdin  __files[0]
#define stdout __files[1]
#define stderr __files[2]

#endif // STDIO_H

