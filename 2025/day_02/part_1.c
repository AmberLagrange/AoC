#include <fcntl.h>
#include <unistd.h>

#include "helper.h"

int is_valid(const char *str) {
	
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
			print_num(i);
			puts(" is invalid.\n", 13);
		}
	}

	return sum;
}

int main(int argc, char **argv) {
	
	int status = 0;
	
	if (argc < 2) {
		
		status = -1;
		goto quit;
	}
	
	int fd = open(argv[1], O_RDONLY, 0);
	if (fd < 0) {
		
		const char *err_msg = "Error: could not open the file.\n";
		puts(err_msg, strlen(err_msg));
		
		status = -2;
		goto quit;
	}
	
	char buf[1024];
	int count = read(fd, buf, sizeof(buf));
	if (count < 0) {
		
		const char *err_msg = "Error: could not read from the file.\n";
		puts(err_msg, strlen(err_msg));
		
		status = -3;
		goto close;
	}
	buf[count - 1] = '\0'; // Strip trailing newline
	
	u64 sum = 0;
	char *range = strtok(buf, ",");
	while (range != NULL) {
		
		sum += check_ranges(range);
		range = strtok(NULL, ",");
	}
	
	puts("The total sum is: ", 18);
	print_num(sum);
	putc('\n');
	
close:
	close(fd);
	
quit:
	return status;
}
