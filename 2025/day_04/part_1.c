#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <common.h>

#define INPUT_BUF_SIZE 32 * 1024
#define flatten_coords(row, col, width, height) ((row) * (width) + (col))

enum {
	
	TOP_LEFT  = 0,
	TOP_MID   = 1,
	TOP_RIGHT = 2,
	MID_LEFT  = 3,
	MID_RIGHT = 4,
	BOT_LEFT  = 5,
	BOT_MID   = 6,
	BOT_RIGHT = 7
};

enum {
	
	EMPTY_SPACE    = '.',
	PAPER_SPACE    = '@',
	TOO_MANY_ROLLS = 4
};

int is_free_square(char *grid, unsigned int row, unsigned int col, size_t width, size_t height) {
	
	if (grid[flatten_coords(row, col, width, height)] != PAPER_SPACE) {
		
		return 0;
	}
	
	int is_top = (row == 0);
	int is_bot = (row == height - 1);
	
	int is_left  = (col == 0);
	int is_right = (col == width - 1);
	
	char nearby_squares[8];
	nearby_squares[TOP_LEFT ] = (is_top || is_left ) ? EMPTY_SPACE : grid[flatten_coords(row - 1, col - 1, width, height)];
	nearby_squares[TOP_MID  ] = (is_top            ) ? EMPTY_SPACE : grid[flatten_coords(row - 1, col    , width, height)];
	nearby_squares[TOP_RIGHT] = (is_top || is_right) ? EMPTY_SPACE : grid[flatten_coords(row - 1, col + 1, width, height)];
	nearby_squares[MID_LEFT ] = (          is_left ) ? EMPTY_SPACE : grid[flatten_coords(row    , col - 1, width, height)];
	nearby_squares[MID_RIGHT] = (          is_right) ? EMPTY_SPACE : grid[flatten_coords(row    , col + 1, width, height)];
	nearby_squares[BOT_LEFT ] = (is_bot || is_left ) ? EMPTY_SPACE : grid[flatten_coords(row + 1, col - 1, width, height)];
	nearby_squares[BOT_MID  ] = (is_bot            ) ? EMPTY_SPACE : grid[flatten_coords(row + 1, col    , width, height)];
	nearby_squares[BOT_RIGHT] = (is_bot || is_right) ? EMPTY_SPACE : grid[flatten_coords(row + 1, col + 1, width, height)];
	
	int nearby_paper = 0;	
	for (size_t square_index = 0; square_index < sizeof(nearby_squares); ++square_index) {
		
		if (nearby_squares[square_index] == PAPER_SPACE) {
			
			++nearby_paper;
		}
	}
	
	return (nearby_paper < TOO_MANY_ROLLS);
}

int main(int argc, char **argv) {
	
	int status = EXIT_SUCCESS;
	
	char *input;
	if (init_aoc(argc, argv, &input)) {
		
		return status;
	}
	
	int accessable_rolls = 0;
	
	size_t input_len = strlen(input);
	char *input_copy = malloc(input_len + 1);
	strncpy(input_copy, input, input_len);
	input_copy[input_len] = '\0';
	
	char *line = strtok(input_copy, "\n");
	size_t width = strlen(line);
	size_t height = 0;
	
	while (line != NULL) {
		
		++height;
		line = strtok(NULL, "\n");
	}
	
	char *grid = malloc(width * height);
	if (grid == NULL) {
		
		puts("Error: could not allocate memory for grid.");
		status = EXIT_FAIL;
		goto free_copy;
	}
	
	for (size_t row = 0; row < height; ++row) {
		
		strncpy(grid + row * width, (input + row * (width + 1)), height);
	}
	
	for (size_t row = 0; row < height; ++row) {
		
		for (size_t col = 0; col < width; ++col) {
			
			if (is_free_square(grid, row, col, width, height)) {
				
				++accessable_rolls;
			}
		}
	}
	
	free(grid);
free_copy:
	free(input_copy);
	clean_aoc(accessable_rolls, input);
	
	return EXIT_SUCCESS;
}

