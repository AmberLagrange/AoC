#include <unistd.h>
#include <fcntl.h>
#include <syscall.h>

#define BUF_MAX_SIZE 8192

void putc(char c) {
	
	__syscall_3(SYS_WRITE, 0, (u64)(&c), 1);
}

void puts(const char *str, int count) {
	
	__syscall_3(SYS_WRITE, 0, (u64)(str), count);
}

unsigned long strlen(const char *str) {
	
	unsigned long count = 0;
	while (*str++) {
		++count;
	}
	
	return count;
}

int main(int argc, char **argv) {
	
	int errno = 0;
	
	if (argc < 2) {
		const char *error_msg = "Please provide a filepath.\n";
		puts(error_msg, strlen(error_msg));
		errno = -1;
		goto quit;
	}
	
	int fd = open(argv[1], O_RDONLY, 0);
	if (fd < 0) {
		const char *error_msg = "Could not open the provided file.\n";
		puts(error_msg, strlen(error_msg));
		errno = -2;
		goto quit;
	}
	
	char buf[BUF_MAX_SIZE];
	int count = read(fd, buf, sizeof(buf));
	if (count < 0) {
		const char *error_msg = "Could not read from the file.\n";
		puts(error_msg, strlen(error_msg));
		errno = -3;
		goto close_file;
	}

	buf[count] = '0';
	puts(buf, count);
	
close_file:
	close(fd);
	
quit:
	return errno;
}

