#include <common.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define LINES 158
#define MAX_AFFECTED 16

enum {
	
	OFF = '.',
	ON  = '#'
};

typedef struct button_t {
	
	uint32_t affected_lights[MAX_AFFECTED];
	size_t num_affected;
} button_t;

typedef struct machine_t {
	
	char *lights;
	size_t num_lights;
	
	button_t *buttons;
	size_t num_buttons;
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
			
			print_num(machine->buttons[button_index].affected_lights[number_index]);
			puts(",");
		}
		
		print_num(machine->buttons[button_index].affected_lights[number_index]);
		puts(") ");
	}
	
	puts("\n");
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
			
			machine->buttons[button_index].affected_lights[num_index] = get_next_number(line, &index, ')');
			++num_index;
		}
		
		machine->buttons[button_index].num_affected = num_index;
		++button_index;
		++index;
	}
	
	return index + 1;
}

int is_all_off(char *lights, size_t num_lights) {
	
	for (size_t index = 0; index < num_lights; ++index) {
		
		if (lights[index] == ON) {
			
			return 0;
		}
	}
	
	return 1;
}

void toggle_lights(char *lights, uint32_t *affected_lights, size_t num_affected) {
	
	for (size_t index = 0; index < num_affected; ++index) {
		
		if (lights[affected_lights[index]] == ON) {
			
			lights[affected_lights[index]] = OFF;
		} else {
			
			lights[affected_lights[index]] = ON;
		}
	}
}

uint32_t get_min_toggles(machine_t *machine) {
	
	char *lights = malloc(machine->num_lights);
	
	uint32_t min_toggles = UINT32_MAX;
	
	for (int mask = 0; mask < (1 << machine->num_buttons); ++mask) {
		
		uint32_t num_toggles = 0;
		memcpy(lights, machine->lights, machine->num_lights);
		for (size_t index = 0; index < machine->num_buttons; ++index) {
			
			if (mask & (1 << index)) {
				
				toggle_lights(lights, machine->buttons[index].affected_lights, machine->buttons[index].num_affected);
				++num_toggles;
			}
		}
		
		if (is_all_off(lights, machine->num_lights)) {
			
			min_toggles = (num_toggles < min_toggles) ? num_toggles : min_toggles;
		}
	}
	
	free(lights);
	return min_toggles;
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
		
		line = strtok(NULL, "\n");
		++line_num;
	}
	
	uint32_t total_toggles = 0;
	for (size_t index = 0; index < LINES; ++index) {
		
		total_toggles += get_min_toggles(&(machines[index]));
	}
	
	for (size_t index = 0; index < LINES; ++index) {
		
		free(machines[index].buttons);
		free(machines[index].lights);
	}
	clean_aoc(total_toggles, input);
	return EXIT_SUCCESS;
}

