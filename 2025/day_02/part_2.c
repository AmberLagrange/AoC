#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "helper.h"

#define INPUT_BUF_SIZE 32 * 1024
#define MAX_INPUT_LEN 16

int is_invalid(const char *str) {
	
	char partition_00[MAX_STR_LEN / MAX_INPUT_LEN];
	char partition_01[MAX_STR_LEN / MAX_INPUT_LEN];
	char partition_02[MAX_STR_LEN / MAX_INPUT_LEN];
	char partition_03[MAX_STR_LEN / MAX_INPUT_LEN];
	char partition_04[MAX_STR_LEN / MAX_INPUT_LEN];
	char partition_05[MAX_STR_LEN / MAX_INPUT_LEN];
	char partition_06[MAX_STR_LEN / MAX_INPUT_LEN];
	char partition_07[MAX_STR_LEN / MAX_INPUT_LEN];
	char partition_08[MAX_STR_LEN / MAX_INPUT_LEN];
	char partition_09[MAX_STR_LEN / MAX_INPUT_LEN];
	char partition_10[MAX_STR_LEN / MAX_INPUT_LEN];
	char partition_11[MAX_STR_LEN / MAX_INPUT_LEN];
	char partition_12[MAX_STR_LEN / MAX_INPUT_LEN];
	char partition_13[MAX_STR_LEN / MAX_INPUT_LEN];
	char partition_14[MAX_STR_LEN / MAX_INPUT_LEN];
	char partition_15[MAX_STR_LEN / MAX_INPUT_LEN];

	char *partitions[MAX_INPUT_LEN] = {
		partition_00, partition_01, partition_02, partition_03,
		partition_04, partition_05, partition_06, partition_07,
		partition_08, partition_09, partition_10, partition_11,
		partition_12, partition_13, partition_14, partition_15
	};
	
	int len = strlen(str);
	for (int num_partitions = 2; num_partitions < MAX_INPUT_LEN; ++num_partitions) {
		
		if (len % num_partitions != 0) {
			
			continue;
		}
		
		int split_len = len / num_partitions;
		
		for (int partition = 0; partition < num_partitions; ++partition) {
			
			strncpy(partitions[partition], str + split_len * partition, split_len);
			partitions[partition][split_len] = '\0';
		}
		
		int invalid = 1;
		
		for (int partition = 1; partition < num_partitions; ++partition) {
			
			if (strcmp(partitions[0], partitions[partition]) != 0) {
				
				invalid = 0;
				break;
			}
			
		}

		if (invalid) {
			return 1;
		}
	}
	
	return 0;
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
		
		if (is_invalid(int_to_str(i, buf))) {
			
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
	ssize_t file_count = read(fd, input_buf, sizeof(input_buf));
	if (file_count < 0) {
		
		puts("Error: could not read from the file.\n");
		status = -3;
		goto close;
	}
	input_buf[file_count - 1] = '\0'; // Strip trailing newline
	
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
