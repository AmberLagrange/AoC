#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "helper.h"

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
	
	int  val   = 0;
	char dir   = '0';
	int  dial  = 50;
	int  count = 0;
	
	for (ssize_t i = 0; i < read_count; ++i) {
		
		char c = input_buf[i];
		
		if (c == '\n') {
			
			if (dir == 'L') {
				if (dial == 0) {
					--count;
				}
				dial -= val;
				while (dial < 0) {
					dial += 100;
					++count;
				}
				if (dial == 0) {
					++count;
				}
			} else if (dir == 'R') {
				dial += val;
				while (dial >= 100) {
					dial -= 100;
					++count;
				}
			}
			
			val = 0;
		} else if (c == 'L' || c == 'R') {
			dir = c;
		} else {
			val *= 10;
			val += (c - '0');
		}
		
	}
	
	puts("The password is: ");
	print_num(count);
	
close:
	close(fd);
	
quit:
	return status;
}

