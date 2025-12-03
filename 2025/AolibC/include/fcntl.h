#ifndef FCNTL_H
#define FCNTL_H

typedef int mode_t;

#define O_RDONLY		00
#define O_WRONLY		01
#define O_RDWR			02

int open(const char *filepath, int flags, mode_t mode);

#endif // FCNTL_H

