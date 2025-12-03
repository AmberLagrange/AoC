#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "helper.h"

#define INPUT_BUF_SIZE 32 * 1024

int find_max_joltage(const char *battery) {
	
	int joltage = 0;
	int max_joltage = 0;
	
	char front_value, back_value;
	
	for (const char *back_ptr = battery + 1; *back_ptr != '\0'; ++back_ptr) {
		
		back_value = *back_ptr;
		for (const char *front_ptr = battery; front_ptr != back_ptr; ++front_ptr) {
			
			front_value = *front_ptr;
			joltage = (int)(front_value - '0') * 10 + (int)(back_value - '0');
			
			max_joltage = (joltage > max_joltage ? joltage : max_joltage);
		}
	}

	return max_joltage;
}

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
	input_buf[read_count - 1] = '\0';
	
	const char *battery = strtok(input_buf, "\n");
	
	int total_joltage = 0;
	
	while(battery != NULL) {
		
		total_joltage += find_max_joltage(battery);
		battery = strtok(NULL, "\n");
	}
	
	puts("The answer is: ");
	print_num(total_joltage);
	putc('\n', stdout);
	
close:
	close(fd);
	
quit:
	return status;
}

