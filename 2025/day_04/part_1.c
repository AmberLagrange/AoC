#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "helper.h"

#define INPUT_BUF_SIZE 32 * 1024
#define flatten_coords(row, col, width, height) ((row) * (width) + (col))

enum {
	
	WIDTH  = 140,
	HEIGHT = 140
};

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

void pretty_problem(const char cell, int is_quiet) {
	
	if (!is_quiet) {
		
		putc(cell, stdout);
	}
}

int main(int argc, char **argv) {
	
	int status = 0;
	int is_quiet = 1;
	
	if (argc < 2) {
		
		puts("Please provide a file.\n");
		status = -1;
		goto quit;
	}
	
	if (argc >= 3) {
		
		is_quiet = 0;
	}
	
	int fd = open(argv[1], O_RDONLY, 0);
	if (fd < 0) {
		
		puts("Error: could not open the file.\n");
		status = -2;
		goto quit;
	}
	
	char input_buf[INPUT_BUF_SIZE];
	ssize_t read_count = read(fd, input_buf, sizeof(input_buf));
	if (read_count < 0) {
		
		puts("Error: could not read from the file.\n");
		status = -3;
		goto close;
	}
	
	char input_buf_cpy[INPUT_BUF_SIZE];
	strncpy(input_buf_cpy, input_buf, INPUT_BUF_SIZE);
	
	char *line = strtok(input_buf_cpy, "\n");
	size_t width = strlen(line);
	size_t height = 0;
	
	for (;;) {
		
		if ((line = strtok(NULL, "\n")) == NULL) {
			
			break;
		}
		
		++height;
	}
	
	char *grid = malloc(width * height);
	if (grid == NULL) {
		
		puts("Error: could not allocate memory.");
		status = -4;
		goto close;
	}
	
	for (size_t row = 0; row < height; ++row) {
		
		strncpy(grid + row * width, (input_buf + row * (width + 1)), height);
	}
	
	int accessable_rolls = 0;
	for (size_t row = 0; row < height; ++row) {
		
		for (size_t col = 0; col < width; ++col) {
			
			if (is_free_square(grid, row, col, width, height)) {
				
				pretty_problem('x', is_quiet);
				++accessable_rolls;
			} else {
				
				pretty_problem(grid[flatten_coords(row, col, width, height)], is_quiet);
			}
		}
		
		pretty_problem('\n', is_quiet);
	}
	
	puts("The answer is: ");
	print_num(accessable_rolls);
	putc('\n', stdout);
	
	free(grid);
	
close:
	close(fd);
	
quit:
	return status;
}

