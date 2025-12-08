#include <common.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define CONNECTIONS 1000
#define LINES 1000
#define MAX_LINE_LEN 32
#define LARGEST_N 3

typedef struct junction_t {
	
	uint32_t x, y, z;
	
	struct junction_t **connections;
	uint64_t num_connections;
} junction_t;

junction_t *junction_create(uint64_t x, uint64_t y, uint64_t z) {
	
	junction_t *box = malloc(sizeof(junction_t));
	
	box->x = x;
	box->y = y;
	box->z = z;
	
	box->connections = malloc(sizeof(junction_t *) * CONNECTIONS);
	for (size_t index = 0; index < CONNECTIONS; ++index) {
		
		box->connections[index] = NULL;
	}
	box->num_connections = 0;
	
	return box;
}

void junction_destroy(junction_t *box) {
	
	if (box) {
		
		free(box->connections);
	}
	
	free(box);
}

void junction_connect(junction_t *a, junction_t *b) {
	
	a->connections[a->num_connections++] = b;
	b->connections[b->num_connections++] = a;
}

int is_connected(junction_t *a, junction_t *b) {
	
	for (size_t index = 0; index < a->num_connections; ++index) {
		
		if (a->connections[index] == b) {
			
			return 1;
		}
	}
	
	return 0;
}

uint64_t calc_distance(junction_t *a, junction_t *b) {
	
	uint64_t dx = b->x - a->x;
	uint64_t dy = b->y - a->y;
	uint64_t dz = b->z - a->z;
	
	return (dx * dx) + (dy * dy) + (dz * dz);
}

void connect(junction_t **boxes) {
	
	uint64_t curr_min = UINT64_MAX;
	
	junction_t *box_1;
	junction_t *box_2;
	for (size_t i = 0; i < LINES - 1; ++i) {
		
		for (size_t j = i + 1; j < LINES; ++j) {
			
			uint64_t distance = calc_distance(boxes[i], boxes[j]);
			
			if (distance >= curr_min) {
				
				continue;
			}
			
			if (is_connected(boxes[i], boxes[j])) {
				
				continue;
			}
			
			curr_min = distance;
			box_1 = boxes[i];
			box_2 = boxes[j];
		}
	}
	
	junction_connect(box_1, box_2);
}

int is_visited(junction_t *junction, junction_t **visited, uint64_t num_visited) {
	
	for (size_t index = 0; index < num_visited; ++index) {
		
		if (visited[index] == junction) {
			
			return 1;
		}
	}
	
	return 0;
}

uint64_t calc_total_connected(junction_t *junction, junction_t **visited, uint64_t *num_visited) {
	
	if (is_visited(junction, visited, *num_visited)) {
		
		return 0;
	}
	
	uint64_t total_connected = 1;
	visited[(*num_visited)++] = junction;

	for (uint64_t index = 0; index < junction->num_connections; ++index) {
		
		total_connected += calc_total_connected(junction->connections[index], visited, num_visited);
	}
	
	return total_connected;
}

int main(int argc, char **argv) {
	
	char *input;
	if (init_aoc(argc, argv, &input)) {
		
		return EXIT_FAIL;
	}
	
	junction_t *boxes[LINES];
	size_t line_num = 0;
	
	char *line = strtok(input, "\n");
	char *state = malloc(MAX_LINE_LEN);
	
	while(line != NULL) {
		
		const char *nums = strtok_r(line, ",", &state);
		uint64_t x, y, z;
		x = atoll(nums);
		nums = strtok_r(NULL, ",", &state);
		y = atoll(nums);
		nums = strtok_r(NULL, ",", &state);
		z = atoll(nums);
		
		boxes[line_num++] = junction_create(x, y, z);
		
		line = strtok(NULL, "\n");
	}
	
	for (size_t index = 0; index < CONNECTIONS; ++index) {
		
		connect(boxes);
	}
	
	junction_t *visited[LINES];
	for (size_t index = 0; index < LINES; ++index) {
		
		visited[index] = NULL;
	}
	
	uint64_t num_visited = 0;
	uint64_t circuits[LINES];

	for (size_t index = 0; index < LINES; ++index) {
		
		circuits[index] = calc_total_connected(boxes[index], visited, &num_visited);
	}
	
	uint64_t largest_circuits[LARGEST_N];
	for (uint64_t index = 0; index < LARGEST_N; ++index) {
		
		largest_circuits[index] = 0;
	}
	
	for (size_t index = 0; index < LINES; ++index) {
		
		for (size_t largest_index = 0; largest_index < LARGEST_N; ++largest_index) {
			
			if (circuits[index] > largest_circuits[largest_index]) {
				
				for (size_t shift_index = LARGEST_N - 1; shift_index > largest_index; --shift_index) {
					
					largest_circuits[shift_index] = largest_circuits[shift_index - 1];
				}
				largest_circuits[largest_index] = circuits[index];
				break;
			}
		}
	}
	
	uint64_t prod = 1;
	for (size_t index = 0; index < LARGEST_N; ++index) {
		
		prod *= largest_circuits[index];
	}
	
	free(state);
	for(uint64_t index = 0; index < LINES; ++index) {
		
		junction_destroy(boxes[index]);
	}

	clean_aoc(prod, input);
	return EXIT_SUCCESS;
}

