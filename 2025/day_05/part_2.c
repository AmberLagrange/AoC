#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <common.h>

typedef struct {
	
	uint64_t start, end;
	int valid;
} range_t;

int range_fully_contains(range_t range_1, range_t range_2) {
	
	// range 2 does not start within range 1
	if (range_2.start < range_1.start) {
		
		return 0;
	}
	
	// range 2 does not end within range 1
	if (range_2.end > range_1.end) {
		
		return 0;
	}
	
	return 1;
}

int range_extends_start(range_t range_1, range_t range_2) {
	
	// range 2 does not start before range 1
	if (range_2.start >= range_1.start) {
		
		return 0;
	}
	
	// range 2 does not overlap with range 1
	if (range_2.end < range_1.start) {
		
		return 0;
	}
	
	// range 2 fully contains range 1
	if (range_2.end >= range_1.end) {
		
		return 0;
	}
	
	return 0;
}

int range_extends_end(range_t range_1, range_t range_2) {
	
	// range 2 does not end before range 1 
	if (range_2.end <= range_1.end) {
		
		return 0;
	}
	
	// range 2 does not overlap with range 1
	if (range_2.start > range_1.end) {
		
		return 0;
	}
	
	// range 2 fully contains range 1
	if (range_2.start <= range_1.start) {
		
		return 0;
	}
	
	return 1;
}

int main(int argc, char **argv) {
	
	char *input;
	if (init_aoc(argc, argv, &input)) {
		
		return EXIT_FAIL;
	}
	
	size_t input_len = strlen(input) + 1;
	char *input_copy = malloc(input_len);
	strncpy(input_copy, input, input_len);
	input_copy[input_len] = '\0';
	
	uint64_t start, end;
	size_t range_len = 0;
	
	const char *line = strtok(input_copy, "\n");	
	while (strcmp("", line) != 0) {
		
		++range_len;
		line = strtok(NULL, "\n");
	}
	
	range_t *ranges = malloc(sizeof(range_t) * range_len);
	size_t index = 0;

	line = strtok(input, "\n");
	while (strcmp("", line) != 0) {
		
		parse_range(line, &start, &end);
		
		ranges[index].start = start;
		ranges[index].end = end;
		ranges[index].valid = 1;
		++index;
		line = strtok(NULL, "\n");
	}
	
	int range_updated;
	do {
		
		range_updated = 0;
		for (size_t range_1_index = 0; range_1_index < range_len; ++range_1_index) {
			
			range_t *range_1 = &ranges[range_1_index];
			if (!range_1->valid) {
				
				continue;
			}
			
			for (size_t range_2_index = 0; range_2_index < range_len; ++range_2_index) {
				
				range_t *range_2 = &ranges[range_2_index];
				if (!range_2->valid || range_1 == range_2) {
					
					continue;
				}
				
				if (range_fully_contains(*range_1, *range_2)) {
					
					range_2->valid = 0;
					range_updated = 1;
				} else if (range_extends_start(*range_1, *range_2)) {
					
					range_1->start = range_2->start;
					range_2->valid = 0;
					range_updated = 1;
				} else if (range_extends_end(*range_1, *range_2)) {
					
					range_1->end   = range_2->end;
					range_2->valid = 0;
					range_updated = 1;
				}
			}
		}
	} while (range_updated);
	
	uint64_t valid_ids = 0;
	for (size_t index = 0; index < range_len; ++index) {
		
		range_t range = ranges[index];
		if (!range.valid) {
			
			continue;
		}
		valid_ids += (range.end - range.start + 1);
	}
	
	free(ranges);
	free(input_copy);
	clean_aoc(valid_ids, input);
	return EXIT_SUCCESS;
}

