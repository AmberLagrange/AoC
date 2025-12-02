#ifndef UNISTD_H
#define UNISTD_H

typedef unsigned int size_t;
typedef          int ssize_t;

ssize_t read(int file_descriptor, void *buf, size_t count);

ssize_t write(int file_descriptor, const void *buf, size_t count);

int close(int file_descriptor);

#endif
