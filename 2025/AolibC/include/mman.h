#ifndef MMAN_H
#define MMAN_H

#ifndef SIZE_T
#define SIZE_T
typedef unsigned long size_t;
#endif

enum {
     PROT_NONE   = 0x00,
     PROT_READ   = 0x01,
     PROT_WRITE  = 0x02,
     PROT_EXEC   = 0x04
 };

 enum {
     MAP_SHARED      = 0x00000001,
     MAP_PRIVATE     = 0x00000002,
     MAP_FIXED       = 0x00000010,
     MAP_ANONYMOUS   = 0x00000020,
     MAP_ANON        = MAP_ANONYMOUS,
     MAP_STACK       = 0x00020000
 };

void *mmap(void *addr, size_t len, int prot, int flags, int fd, int offset);

int munmap(void *addr, size_t len);

#endif // MMAN_H

