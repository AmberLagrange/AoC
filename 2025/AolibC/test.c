#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
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
	
	char *input_buf = malloc(INPUT_BUF_SIZE);
	if (input_buf == NULL) {
		
		puts("Error: could not allocate memory.\n");
		status = -3;
		goto quit;
	}
	
	ssize_t read_count = read(fd, input_buf, INPUT_BUF_SIZE);
	if (read_count < 0) {
		
		puts("Error: could not read from the file.\n");
		status = -3;
		goto close;
	}
	input_buf[read_count] = '\0';
	
	//puts(input_buf);
	free(input_buf);
	
close:
	close(fd);
	
quit:
	return status;
}

