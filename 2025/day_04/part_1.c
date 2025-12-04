#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define INPUT_BUF_SIZE 32 * 1024

#include "helper.h"

#define WIDTH  140
#define HEIGHT 140

#define TOP_LEFT  0
#define TOP_MID   1
#define TOP_RIGHT 2
#define MID_LEFT  3
#define MID_RIGHT 4
#define BOT_LEFT  5
#define BOT_MID   6
#define BOT_RIGHT 7

#define EMPTY_SPACE '.'
#define PAPER_SPACE '@'

int is_free_square(char grid[HEIGHT][WIDTH], unsigned int row, unsigned int col) {

	if (grid[row][col] != PAPER_SPACE) {
		
		return 0;
	}
	
	int is_top = (row == 0);
	int is_bot = (row == HEIGHT - 1);
	
	int is_left  = (col == 0);
	int is_right = (col == WIDTH - 1);
	
	char nearby_squares[8];

	nearby_squares[TOP_LEFT ] = (is_top || is_left ) ? EMPTY_SPACE : grid[row - 1][col - 1];
	nearby_squares[TOP_MID  ] = (is_top            ) ? EMPTY_SPACE : grid[row - 1][col    ];
	nearby_squares[TOP_RIGHT] = (is_top || is_right) ? EMPTY_SPACE : grid[row - 1][col + 1];
	nearby_squares[MID_LEFT ] = (          is_left ) ? EMPTY_SPACE : grid[row    ][col - 1];
	nearby_squares[MID_RIGHT] = (          is_right) ? EMPTY_SPACE : grid[row    ][col + 1];
	nearby_squares[BOT_LEFT ] = (is_bot || is_left ) ? EMPTY_SPACE : grid[row + 1][col - 1];
	nearby_squares[BOT_MID  ] = (is_bot            ) ? EMPTY_SPACE : grid[row + 1][col    ];
	nearby_squares[BOT_RIGHT] = (is_bot || is_right) ? EMPTY_SPACE : grid[row + 1][col + 1];
	
	int nearby_paper = 0;
	
	for (int square_index = 0; square_index < 8; ++square_index) {
		
		if (nearby_squares[square_index] == PAPER_SPACE) {
			
			++nearby_paper;
		}
	}
	
	return (nearby_paper < 4);
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
	ssize_t read_count = read(fd, input_buf, sizeof(input_buf));
	if (read_count < 0) {
		
		puts("Error: could not read from the file.\n");
		status = -3;
		goto close;
	}
	
	char grid[HEIGHT][WIDTH];
	for (unsigned int row = 0; row < HEIGHT; ++row) {
		
		strncpy(grid[row], (input_buf + row * (HEIGHT + 1)), HEIGHT);
	}
	
	int accessable_rolls = 0;
	for (unsigned int row = 0; row < HEIGHT; ++row) {
		
		for (unsigned int col = 0; col < WIDTH; ++col) {
			
			if (is_free_square(grid, row, col)) {
				
				++accessable_rolls;
			}
		}
	}
	
	puts("The answer is: ");
	print_num(accessable_rolls);
	putc('\n', stdout);
	
close:
	close(fd);
	
quit:
	return status;
}

