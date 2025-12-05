#include <common.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Helper functions not in libc

void swap(void *v1, void *v2) {
	
	char tmp = *(char *)(v1);
	*(char *)(v1) = *(char *)(v2);
	*(char *)(v2) = tmp;
}

char *reverse_str(char *str) {
	
	size_t len = strlen(str);	
	for (size_t index = 0; index < len / 2; ++index) {
		swap(str + index, str + len - index - 1);
	}
	
	return str;
}

char *int_to_str(uint64_t num, char *buf) {
	
	if (num == 0) {
		
		buf[0] = '0';
		buf[1] = '\0';
		return buf;
	}
	
	size_t index = 0;
	while (num) {
		buf[index++] = '0' + (num % 10);
		num /= 10;
	}
	buf[index] = '\0';
	
	reverse_str(buf);
	return buf;
}

void print_num(uint64_t num) {
	
	char buf[MAX_STR_LEN];
	int_to_str(num, buf);
	puts(buf);
}

void parse_range(const char *range, uint64_t *start, uint64_t *end) {
	
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

// Boilerplate

int32_t init_aoc(int argc, char **argv, char **input) {
	
	int32_t status = 0;
	if (argc < 2) {
		
		puts("Please provide a file.\n");
		status = -1;
		goto end;
	}
	
	int fd = open(argv[1], O_RDONLY, 0);
	if (fd < 0) {
		
		puts("Error: could not open the file.\n");
		status = -2;
		goto end;
	}
	
	*input = malloc(MAX_INPUT_BUFFER_LEN);
	if (*input == NULL) {
		
		puts("Error: could not allocate memory.\n");
		status = -3;
		goto close;
	}
	
	ssize_t read_count = read(fd, *input, MAX_INPUT_BUFFER_LEN);
	if (read_count < 0) {
		
		puts("Error: could not read from the file.\n");
		status = -4;
		goto clean_mem;
	}
	(*input)[read_count - 1] = '\0';
	
	goto close;
	
clean_mem:
	free(*input);
	
close:
	close(fd);
	
end:
	return status;
}

void clean_aoc(uint64_t answer, char *input) {
	
	puts("The answer is: ");
	print_num(answer);
	puts("\n");
	free(input);
}

