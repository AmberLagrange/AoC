#include <string.h>

#include <helper.h>

int is_valid(const char *str) {
	
	if (str == NULL) {
		
		return 0;
	}
	
	size_t len = strlen(str);
	
	if (len % 2 == 1) {
		return 1;
	}
	
	size_t half_len = len / 2;
	
	char first_half[MAX_STR_LEN];
	char second_half[MAX_STR_LEN];
	
	strncpy(first_half,  str,            half_len);
	strncpy(second_half, str + half_len, half_len);

	first_half[half_len]  = '\0';
	second_half[half_len] = '\0';
	
	return (strcmp(first_half, second_half) != 0);
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

uint64_t check_ranges(const char *range) {
	
	uint64_t start, end;
	uint64_t sum = 0;
	parse_range(range, &start, &end);
	
	char buf[MAX_STR_LEN];
	
	for (uint64_t index = start; index <= end; ++index) {
		
		if (!is_valid(int_to_str(index, buf))) {
			
			sum += index;
		}
	}
	
	return sum;
}

int main(int argc, char **argv) {
	
	char *input;
	int32_t read_count = init_aoc(argc, argv, &input);
	
	if (read_count < 0) {
		
		return EXIT_FAIL;
	}
	input[read_count - 1] = '\0';
	
	uint64_t sum = 0;
	char *range = strtok(input, ",");
	while (range != NULL) {
		
		sum += check_ranges(range);
		range = strtok(NULL, ",");
	}
	
	clean_aoc(sum, input);
	return EXIT_SUCCESS;
}
