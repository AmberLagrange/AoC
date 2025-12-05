#include <string.h>

#include <helper.h>

#define INPUT_BUF_SIZE 32 * 1024
#define JOLTAGE_DIGITS 12

long long find_max_joltage(const char *battery) {
	
	long long joltage = 0;
	
	size_t largest_index = 0;
	size_t bank_digits = strlen(battery);
	for (size_t digit_index = 0; digit_index < JOLTAGE_DIGITS; ++digit_index) {
		
		char largest_digit = '0';
		for (size_t starting_index = largest_index; starting_index < (bank_digits - JOLTAGE_DIGITS + digit_index + 1); ++starting_index) {
			if (battery[starting_index] > largest_digit) {
				
				largest_digit = battery[starting_index];
				largest_index = starting_index + 1;
			}
		}
		
		joltage *= 10;
		joltage += (largest_digit - '0');
	}
	
	return joltage;
}

int main(int argc, char **argv) {
	
	char *input;
	if (init_aoc(argc, argv, &input)) {
		
		return EXIT_FAIL;
	}

	const char *battery = strtok(input, "\n");
	
	long long total_joltage = 0;
	while(battery != NULL) {
		
		total_joltage += find_max_joltage(battery);
		battery = strtok(NULL, "\n");
	}
	
	clean_aoc(total_joltage, input);
	return EXIT_SUCCESS;
}

