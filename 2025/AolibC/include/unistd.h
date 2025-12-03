#ifndef UNISTD_H
#define UNISTD_H

#ifndef SIZE_T
#define SIZE_T
typedef unsigned long size_t;
#endif

#ifndef SSIZE_T
#define SSIZE_T
typedef long ssize_t;
#endif

ssize_t read(int file_descriptor, void *buf, size_t count);

ssize_t write(int file_descriptor, const void *buf, size_t count);

int close(int file_descriptor);

#endif // UNISTD_H

