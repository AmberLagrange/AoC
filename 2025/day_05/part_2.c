#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <helper.h>

#define BUCKET_RESERVED_INIT   1024
#define BUCKET_RESERVED_FACTOR 2

#define SET_BUCKETS 1024
#define HASH(x) ((x) % SET_BUCKETS)

// ---------------------------- BUCKET ---------------------------- //

typedef struct {
	
	uint64_t *values;
	size_t bucket_size;
	size_t bucket_reserved;
} bucket_t;

void init_bucket(bucket_t *bucket) {
	
	bucket->bucket_size = 0;
	bucket->bucket_reserved = BUCKET_RESERVED_INIT;
	bucket->values = malloc(sizeof(uint64_t) * bucket->bucket_reserved);
}

void cleanup_bucket(bucket_t *bucket) {
	
	if (!bucket) {
		
		return;
	}
	
	free(bucket->values);
}

int bucket_contains(bucket_t *bucket, uint64_t value) {
	
	for (size_t index = 0; index < bucket->bucket_size; ++index) {
		
		if (bucket->values[index] == value) {
			
			return 1;
		}
	}
	
	return 0;
}

int bucket_push(bucket_t *bucket, uint64_t value) {
	
	if (bucket_contains(bucket, value)) {
		
		return 0;
	}
	
	if (bucket->bucket_size == bucket->bucket_reserved) {
		
		bucket->bucket_reserved *= BUCKET_RESERVED_FACTOR;
		uint64_t *new_values = malloc(sizeof(uint64_t) * bucket->bucket_reserved);
		
		for (size_t index = 0; index < bucket->bucket_size; ++index) {
			
			new_values[index] = bucket->values[index];
		}
		
		free(bucket->values);
		bucket->values = new_values;
	}
	
	bucket->values[bucket->bucket_size] = value;
	bucket->bucket_size++;
	return 1;
}

// ---------------------------- SET ---------------------------- //

typedef struct {
	
	bucket_t **buckets;
	size_t num_buckets;
	size_t num_elements;
} set_t;

void init_set(set_t *set) {
	
	set->num_buckets = SET_BUCKETS;
	set->num_elements = 0;

	set->buckets = malloc(sizeof(bucket_t) * set->num_buckets);
	
	for (size_t index = 0; index < set->num_buckets; ++index) {
		
		set->buckets[index] = malloc(sizeof(bucket_t));
		init_bucket(set->buckets[index]);
	}
}

void cleanup_set(set_t *set) {
	
	if (!set) {
		
		return;
	}
	
	for (size_t index = 0; index < set->num_buckets; ++index) {
		
		cleanup_bucket(set->buckets[index]);
		free(set->buckets[index]);
	}
	
	free(set->buckets);
}

int set_contains(set_t *set, uint64_t value) {
	
	return bucket_contains(set->buckets[HASH(value)], value);
}

int set_push(set_t *set, uint64_t value) {
	
	int pushed = bucket_push(set->buckets[HASH(value)], value);
	
	if (pushed) {
		
		set->num_elements++;
	}
	
	return pushed;
}

// ---------------------------- AOC ---------------------------- //

typedef struct {
	
	uint64_t start, end;
	int valid;
} range_t;

void print_range(range_t range) {
	
	print_num(range.start);
	puts("-");
	print_num(range.end);
	puts("\n");
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
	
	for (int i = 0; i < 10; ++i) {
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
			} else if (range_extends_start(*range_1, *range_2)) {
				
				range_1->start = range_2->start;
				range_2->valid = 0;
			} else if (range_extends_end(*range_1, *range_2)) {
				
				range_1->end   = range_2->end;
				range_2->valid = 0;
			}
		}
	}
	(void)(i);
	}
	
	uint64_t valid_ids = 0;
	for (size_t index = 0; index < range_len; ++index) {
		
		range_t range = ranges[index];
		if (!range.valid) {
			
			continue;
		}
		print_range(range);
		valid_ids += (range.end - range.start + 1);
	}
	
	free(ranges);
	free(input_copy);
	clean_aoc(valid_ids, input);
	return EXIT_SUCCESS;
}

