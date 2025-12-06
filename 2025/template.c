#include <common.h>

int main(int argc, char **argv) {
	
	char *input;
	if (init_aoc(argc, argv, &input)) {
		
		return EXIT_FAIL;
	}
	
	clean_aoc(0, input);
	return EXIT_SUCCESS;
}

