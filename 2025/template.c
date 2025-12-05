#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define INPUT_BUF_SIZE 32 * 1024

int main(int argc, char **argv) {
	
	int status = 0;
	
	if (argc < 2) {
		
		puts("Please provide a file.\n");
		status = -1;
		goto quit;
	}
	
	int fd = open(argv[1], O_RDONLY, 0);
	if (fd < 0) {
		
		puts("Error: could not open the file.\n");
		status = -2;
		goto quit;
	}
	
	char input_buf[INPUT_BUF_SIZE];
	ssize_t read_count = read(fd, input_buf, sizeof(input_buf));
	if (read_count < 0) {
		
		puts("Error: could not read from the file.\n");
		status = -3;
		goto close;
	}
	
	puts("The answer is: ");
	putc('\n', stdout);
	puts("\n");
	
close:
	close(fd);
	
quit:
	return status;
}

