#include <common.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINES 496
#define MAX_LINE_LEN 32

enum {
	
	RED   = '#',
	GREEN = 'X',
	OTHER = '.'
};

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

void fill_interior(char **grid, uint32_t width, uint32_t height) {
	
	for (size_t row = 0; row < height; ++row) {
		
		int is_inside = 0;
		for (size_t col = 0; col < width; ++col) {
			
			if (grid[row][col] == RED) {
				
				continue;
			}
			
			if ((grid[row][col] == GREEN) &&
				(col != width - 1) &&
				(grid[row][col + 1] != GREEN)) {
				
				is_inside = !is_inside;
			}
			
			if (is_inside) {
				
				grid[row][col] = GREEN;
			}
		}
	}
}

void fill_between_coords(char **grid, coords_t coord_1, coords_t coord_2) {
	
	if (coord_1.x == coord_2.x) {
		
		uint32_t start_y = (coord_1.y < coord_2.y) ? coord_1.y : coord_2.y;
		uint32_t end_y   = (coord_1.y > coord_2.y) ? coord_1.y : coord_2.y;
		
		for (size_t index = start_y + 1; index < end_y; ++index) {
			
			grid[index - 1][coord_1.x - 1] = GREEN;
		}
	} else {
		
		uint32_t start_x = (coord_1.x < coord_2.x) ? coord_1.x : coord_2.x;
		uint32_t end_x   = (coord_1.x > coord_2.x) ? coord_1.x : coord_2.x;
		
		for (size_t index = start_x + 1; index < end_x; ++index) {
			
			grid[coord_1.y - 1][index - 1] = GREEN;
		}
	}
}

int is_valid(char **grid, coords_t coord_1, coords_t coord_2) {
	
	uint32_t min_x = (coord_1.x < coord_2.x) ? coord_1.x : coord_2.x;
	uint32_t max_x = (coord_1.x > coord_2.x) ? coord_1.x : coord_2.x;
	
	uint32_t min_y = (coord_1.y < coord_2.y) ? coord_1.y : coord_2.y;
	uint32_t max_y = (coord_1.y > coord_2.y) ? coord_1.y : coord_2.y;
	
	for (size_t row = min_y; row < max_y; ++row) {
		
		if (grid[row - 1][min_x - 1] == OTHER) {
			
			return 0;
		}
		
		if (grid[row - 1][max_x - 1] == OTHER) {
			
			return 0;
		}
	}
	
	for (size_t col = min_x; col < max_x; ++col) {
		
		if (grid[min_y - 1][col - 1] == OTHER) {
			
			return 0;
		}
		
		if (grid[max_y - 1][col - 1] == OTHER) {
			
			return 0;
		}
	}
	
	return 1;
}

void init_grid(char **grid, uint32_t width, uint32_t height, coords_t *coords_list, size_t coords_len) {
	
	for (size_t row = 0; row < height; ++row) {
		
		grid[row] = malloc(width + 1);
		for (size_t col = 0; col < width; ++col) {
			
			grid[row][col] = OTHER;
		}
		grid[row][width] = '\0';
	}
	
	coords_t tile, prev_tile;
	
	tile = coords_list[0];
	grid[tile.y - 1][tile.x - 1] = RED;

	prev_tile = coords_list[coords_len - 1];
	fill_between_coords(grid, tile, prev_tile);
	
	for (size_t index = 1; index < coords_len; ++index) {
		
		prev_tile = tile;
		tile = coords_list[index];
		grid[tile.y - 1][tile.x - 1] = RED;
		fill_between_coords(grid, tile, prev_tile);
	}
	
	fill_interior(grid, width, height);
}

void print_grid(char **grid, uint32_t height) {
	
	for (size_t index = 0; index < height; ++index) {
		
		puts(grid[index]);
		puts("\n");
	}
}

int main(int argc, char **argv) {
	
	char *input;
	if (init_aoc(argc, argv, &input)) {
		
		return EXIT_FAIL;
	}
	
	coords_t coords_list[LINES];
	size_t line_num = 0;
	uint32_t max_x = 0;
	uint32_t max_y = 0;
	
	char *state = malloc(MAX_LINE_LEN);
	char *line = strtok(input, "\n");
	while (line != NULL) {
		
		char *x_str = strtok_r(line, ",", &state);
		char *y_str = strtok_r(NULL, ",", &state);
		
		uint32_t in_x = atoi(x_str);
		uint32_t in_y = atoi(y_str);
		
		coords_list[line_num].x = in_x;
		coords_list[line_num].y = in_y;
		
		max_x = (in_x > max_x) ? in_x : max_x;
		max_y = (in_y > max_y) ? in_y : max_y;
		
		++line_num;
		line = strtok(NULL, "\n");
	}
	
	char **grid = malloc(sizeof(char *) * max_y);
	init_grid(grid, max_x, max_y, coords_list, LINES);
	//print_grid(grid, max_y);
	
	uint32_t max_area = 0;
	for (size_t outer_index = 0; outer_index < line_num; ++outer_index) {
		
		for (size_t inner_index = outer_index + 1; inner_index < line_num; ++inner_index) {
			
			coords_t coord_1 = coords_list[outer_index];
			coords_t coord_2 = coords_list[inner_index];
			
			if (!is_valid(grid, coord_1, coord_2)) {
				
				continue;
			}
			
			uint32_t area = calc_area(coord_1, coord_2);
			max_area = (area > max_area) ? area : max_area;
		}
	}
	
	for (size_t index = 0; index < max_y; ++index) {
		
		free(grid[index]);
	}
	free(grid);
	
	free(state);
	clean_aoc(max_area, input);
	return EXIT_SUCCESS;
}

