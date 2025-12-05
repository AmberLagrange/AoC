#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <common.h>

int is_fresh(uint64_t ingredient, const uint64_t *ranges, size_t range_len) {
	
	for (size_t index = 0; index < range_len; ++index) {
		
		if (ranges[2 * index + 0] <= ingredient && ingredient <= ranges[2 * index + 1]) {
			
			return 1;
		}
	}
	
	return 0;
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
	size_t ingredient_len = 0;
	
	const char *line = strtok(input_copy, "\n");	
	while (strcmp("", line) != 0) {
		
		++range_len;
		line = strtok(NULL, "\n");
	}
	
	line = strtok(NULL, "\n");
	while (line != NULL) {
		
		++ingredient_len;
		line = strtok(NULL, "\n");
	}
	
	uint64_t *ranges = malloc(sizeof(uint64_t) * range_len * 2);
	size_t index = 0;
	
	line = strtok(input, "\n");
	while (strcmp("", line) != 0) {
		
		parse_range(line, &start, &end);
		ranges[2 * index + 0] = start;
		ranges[2 * index + 1] = end;
		++index;
		line = strtok(NULL, "\n");
	}
	
	uint64_t *ingredients = malloc(sizeof(uint64_t) * ingredient_len);
	index = 0;
	
	line = strtok(NULL, "\n");
	while (line != NULL) {
		
		ingredients[index++] = atoll(line);
		line = strtok(NULL, "\n");
	}
	
	uint64_t fresh_ingredients = 0;
	for (index = 0; index < ingredient_len; ++index) {
		
		fresh_ingredients += is_fresh(ingredients[index], ranges, range_len);
	}
	
	free(ingredients);
	free(ranges);
	free(input_copy);
	clean_aoc(fresh_ingredients, input);
	return EXIT_SUCCESS;
}

