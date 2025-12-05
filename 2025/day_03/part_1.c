#include <string.h>

#include <helper.h>

#define INPUT_BUF_SIZE 32 * 1024

int find_max_joltage(const char *battery) {
	
	int joltage = 0;
	int max_joltage = 0;
	
	char front_value, back_value;
	
	for (const char *back_ptr = battery + 1; *back_ptr != '\0'; ++back_ptr) {
		
		back_value = *back_ptr;
		for (const char *front_ptr = battery; front_ptr != back_ptr; ++front_ptr) {
			
			front_value = *front_ptr;
			joltage = (int)(front_value - '0') * 10 + (int)(back_value - '0');
			
			max_joltage = (joltage > max_joltage ? joltage : max_joltage);
		}
	}

	return max_joltage;
}

int main(int argc, char **argv) {
	
	char *input;
	if (init_aoc(argc, argv, &input)) {
		
		return EXIT_FAIL;
	}
	
	const char *battery = strtok(input, "\n");
	
	int total_joltage = 0;
	while(battery != NULL) {
		
		total_joltage += find_max_joltage(battery);
		battery = strtok(NULL, "\n");
	}
	
	clean_aoc(total_joltage, input);
	return EXIT_SUCCESS;
}

