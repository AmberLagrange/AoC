#include <unistd.h>
#include <fcntl.h>
#include <syscall.h>

void putc(char c) {
	
	__syscall_3(SYS_WRITE, 0, (u64)(&c), 1);
}

void puts(const char *str, int count) {
	
	__syscall_3(SYS_WRITE, 0, (u64)(str), count);
}

int main(void) {
	
	char buf[1024];
	
	int fd = open("foo.txt", O_RDONLY, 0);
	if (fd < 0) { return -1; }
	int count = read(fd, buf, sizeof(buf));
	if (count < 0) { return -2; }
	buf[count] = '0';
	puts(buf, count);
	close(fd);
	
	return 0;
}

