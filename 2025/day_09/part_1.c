#include <common.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINES 496
#define MAX_LINE_LEN 32

typedef struct coords_t {
	
	uint32_t x, y;
} coords_t;

uint32_t calc_area(const coords_t corner_1, const coords_t corner_2) {
	
	int32_t dx = (corner_2.x - corner_1.x);
	if (dx < 0) {
		
		dx = -dx;
	}
	++dx;
	
	int32_t dy = (corner_2.y - corner_1.y);
	if (dy < 0) {
		
		dy = -dy;
	}
	++dy;
	
	return (uint32_t)(dx * dy);
}

int main(int argc, char **argv) {
	
	char *input;
	if (init_aoc(argc, argv, &input)) {
		
		return EXIT_FAIL;
	}
	
	coords_t coords_list[LINES];
	char *state = malloc(MAX_LINE_LEN);
	size_t line_num = 0;
	
	char *line = strtok(input, "\n");
	while (line != NULL) {
		
		char *x_str = strtok_r(line, ",", &state);
		char *y_str = strtok_r(NULL, ",", &state);
		
		coords_list[line_num].x = atoi(x_str);
		coords_list[line_num].y = atoi(y_str);
		
		++line_num;
		line = strtok(NULL, "\n");
	}
	
	uint32_t max_area = 0;
	for (size_t inner_index = 0; inner_index < line_num; ++inner_index) {
		
		for (size_t outer_index = inner_index + 1; outer_index < line_num; ++outer_index) {
			
			uint32_t area = calc_area(coords_list[inner_index], coords_list[outer_index]);
			max_area = (area > max_area) ? area : max_area;
		}
	}
	
	free(state);
	clean_aoc(max_area, input);
	return EXIT_SUCCESS;
}

