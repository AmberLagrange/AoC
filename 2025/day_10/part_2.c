#include <common.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define LINES 3 //158
#define MAX_AFFECTED 16
#define MAX_REQUIREMENTS 16

enum {
	
	OFF = '.',
	ON  = '#'
};

typedef struct button_t {
	
	uint32_t affected[MAX_AFFECTED];
	size_t num_affected;
} button_t;

typedef struct machine_t {
	
	char *lights;
	size_t num_lights;
	
	button_t *buttons;
	size_t num_buttons;
	
	int32_t joltage_requirements[MAX_REQUIREMENTS];
	size_t num_requirements;
} machine_t;

void print_machine(machine_t *machine) {
	
	puts("[");
	for (size_t index = 0; index < machine->num_lights; ++index) {
		
		putc(machine->lights[index], stdout);
	}
	puts("] ");
	
	for (size_t button_index = 0; button_index < machine->num_buttons; ++button_index) {
		
		puts("(");
		size_t number_index = 0;
		for (; number_index < machine->buttons[button_index].num_affected - 1; ++number_index) {
			
			print_num(machine->buttons[button_index].affected[number_index]);
			puts(",");
		}
		
		print_num(machine->buttons[button_index].affected[number_index]);
		puts(") ");
	}
	
	puts("{");
	size_t requirement_index = 0;
	for (; requirement_index < machine->num_requirements - 1; ++requirement_index) {
		
		print_num(machine->joltage_requirements[requirement_index]);
		puts(",");
	}
	
	print_num(machine->joltage_requirements[requirement_index]);
	puts("}\n");
}

void print_machines(machine_t *machines, size_t machine_len) {
	
	for (size_t index = 0; index < machine_len; ++index) {
		
		print_machine(&(machines[index]));
	}
}

uint32_t get_next_number(const char *line, size_t *index, char delim) {
	
	if (line[*index] == ',') {
		
		++(*index);
	}
	uint32_t num = 0;
	while (line[*index] != ',' && line[*index] != delim) {
		
		num *= 10;
		num += line[*index] - '0';
		++(*index);
	}
	
	return num;
}

size_t init_lights(machine_t *machine, const char *line) {
	
	size_t index = 1;
	size_t num_lights = 0;
	while (line[index++] != ']') {
		
		++num_lights;
	}
	
	machine->lights = malloc(num_lights);
	machine->num_lights = num_lights;
	
	index = 1;
	while (line[index] != ']') {
		
		machine->lights[index - 1] = line[index];
		++index;
	}
	
	return index + 1;
}

size_t init_buttons(machine_t *machine, const char *line, size_t index) {
	
	size_t num_buttons = 0;
	size_t index_copy = index;
	
	while (line[index_copy] != '{') {
		
		if (line[index_copy] == ')') {
			
			++num_buttons;
		}
		
		++index_copy;
	}
	
	machine->buttons = malloc(sizeof(button_t) * num_buttons);
	machine->num_buttons = num_buttons;
	
	size_t button_index = 0;
	while (line[index] != '{') {
		
		if (line[index] == ' ' || line[index] == '(') {
			
			++index;
			continue;
		}
		
		size_t num_index = 0;
		while (line[index] != ')') {
			
			machine->buttons[button_index].affected[num_index] = get_next_number(line, &index, ')');
			++num_index;
		}
		
		machine->buttons[button_index].num_affected = num_index;
		++button_index;
		++index;
	}
	
	return index + 1;
}

size_t init_joltage_requirements(machine_t *machine, const char *line, size_t index) {
	
	size_t requirement_index = 0;
	while (line[index] != '}') {
		
		machine->joltage_requirements[requirement_index++] = get_next_number(line, &index, '}');
	}
	machine->num_requirements = requirement_index;
	
	return index + 1;
}

void press_button(int32_t *joltage_requirements, button_t *button, size_t num_presses) {
	
	for (size_t index = 0; index < button->num_affected; ++index) {
		
		joltage_requirements[button->affected[index]] -= num_presses;
	}
}

int is_valid_state(int32_t *requirements, size_t num_requirements) {
	
	for (size_t index = 0; index < num_requirements; ++index) {
		
		if (requirements[index] < 0) {
			
			return 0;
		}
	}
	
	return 1;
}

uint32_t get_min_presses(machine_t *machine) {
	
	uint32_t num_presses = 0;
	
	for (size_t requirement_index = 0; requirement_index < machine->num_requirements; ++requirement_index) {
		
		if (machine->joltage_requirements[requirement_index] == 0) {
			
			continue;
		}
		
		button_t *button;
		for (size_t button_index = 0; button_index < machine->num_buttons; ++button_index) {
			
			button = &(machine->buttons[button_index]);
			int affects_requirement = 0;
			for (size_t affected_index = 0; affected_index < button->num_affected; ++affected_index) {
				
				if (button->affected[affected_index] == requirement_index) {
					
					affects_requirement = 1;
					break;
				}
			}
			
			if (!affects_requirement) {
				
				continue;
			}
			
			int32_t requirement_copy[MAX_REQUIREMENTS];
			memcpy(requirement_copy, machine->joltage_requirements, sizeof(int32_t) * MAX_REQUIREMENTS);
			
			uint32_t times_pressed = machine->joltage_requirements[requirement_index];
			press_button(machine->joltage_requirements, button, times_pressed);
			
			if (!is_valid_state(machine->joltage_requirements, machine->num_requirements)) {
				
				memcpy(machine->joltage_requirements, requirement_copy, sizeof(int32_t) * MAX_REQUIREMENTS);
				continue;
			}
			
			num_presses += times_pressed;
			break;
		}
	}
	
	return num_presses;
}

int main(int argc, char **argv) {
	
	char *input;
	if (init_aoc(argc, argv, &input)) {
		
		return EXIT_FAIL;
	}
	
	machine_t machines[LINES];
	size_t line_num = 0;
	
	char *line = strtok(input, "\n");
	while (line != NULL) {
		
		size_t index;
		
		index = init_lights(&(machines[line_num]), line);
		index = init_buttons(&(machines[line_num]), line, index);
		index = init_joltage_requirements(&(machines[line_num]), line, index);
		
		line = strtok(NULL, "\n");
		++line_num;
	}
	
	uint32_t min_presses = 0;
	
	print_machines(machines, LINES);
	for (size_t index = 0; index < LINES; ++index) {
		
		min_presses += get_min_presses(&(machines[index]));
	}
	puts("\n");
	print_machines(machines, LINES);
	
	for (size_t index = 0; index < LINES; ++index) {
		
		free(machines[index].buttons);
		free(machines[index].lights);
	}
	clean_aoc(min_presses, input);
	return EXIT_SUCCESS;
}

