#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "helper.h"

#define INPUT_BUF_SIZE 32 * 1024
#define JOLTAGE_DIGITS 12

long long find_max_joltage(const char *battery) {
	
	long long joltage = 0;
	
	char joltage_perm[JOLTAGE_DIGITS + 1];
	joltage_perm[JOLTAGE_DIGITS] = '\0';
	
	size_t perm_indicies[JOLTAGE_DIGITS];
	for (size_t index = 0; index < JOLTAGE_DIGITS; ++index) {
		
		perm_indicies[index] = 0;
	}
	
	size_t largest_index = 0;
	size_t bank_digits = strlen(battery);
	for (size_t digit_index = 0; digit_index < JOLTAGE_DIGITS; ++digit_index) {
		
		char largest_digit = '0';
		for (size_t starting_index = largest_index; starting_index < (bank_digits - JOLTAGE_DIGITS + digit_index + 1); ++starting_index) {
			if (battery[starting_index] > largest_digit) {
				
				largest_digit = battery[starting_index];
				largest_index = starting_index + 1;
			}
		}
		
		joltage *= 10;
		joltage += (largest_digit - '0');
	}
	
	return joltage;
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
	
	long long total_joltage = 0;
	
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

