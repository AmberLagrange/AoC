#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "helper.h"

#define INPUT_BUF_SIZE 32 * 1024

int is_valid(const char *str) {

	if (str == NULL) {
		
		return 0;
	}

	int len = strlen(str);
	
	if (len % 2 == 1) {
		return 1;
	}
	
	int half_len = len / 2;
	
	char first_half[MAX_STR_LEN];
	char second_half[MAX_STR_LEN];
	
	strncpy(first_half,  str,            half_len);
	strncpy(second_half, str + half_len, half_len);

	first_half[half_len]  = '\0';
	second_half[half_len] = '\0';
	
	return (strcmp(first_half, second_half) != 0);
}

void parse_range(const char *range, u64 *start, u64 *end) {

	*start = 0;
	*end   = 0;
	
	char c;

	while ((c = *range++) != '-') {
		*start *= 10;
		*start += (c - '0');
	}

	while((c = *range++) != '\0') {
		*end *= 10;
		*end += (c - '0');
	}
}

u64 check_ranges(const char *range) {
	
	u64 start, end;
	u64 sum = 0;
	parse_range(range, &start, &end);

	char buf[MAX_STR_LEN];

	for (u64 i = start; i <= end; ++i) {
		
		if (!is_valid(int_to_str(i, buf))) {
			
			sum += i;
		}
	}

	return sum;
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
	input_buf[read_count - 1] = '\0'; // Strip trailing newline
	
	u64 sum = 0;
	char *range = strtok(input_buf, ",");
	while (range != NULL) {
		
		sum += check_ranges(range);
		range = strtok(NULL, ",");
	}
	
	puts("The total sum is: ");
	print_num(sum);
	putc('\n', stdout);
	
close:
	close(fd);
	
quit:
	return status;
}
