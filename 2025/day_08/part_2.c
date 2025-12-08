#include <common.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define CONNECTIONS 1000
#define LINES 1000
#define MAX_LINE_LEN 32

static uint64_t precalced_distances[LINES][LINES];
static uint32_t global_id;

typedef struct junction_t {
	
	uint32_t x, y, z;
	uint32_t id;
	
	struct junction_t **connections;
	uint64_t num_connections;
	
	struct junction_t *parent;
	
	int visited;
} junction_t;

junction_t *junction_create(uint64_t x, uint64_t y, uint64_t z) {
	
	junction_t *box = malloc(sizeof(junction_t));
	
	box->x = x;
	box->y = y;
	box->z = z;
	
	box->id = global_id++;
	
	box->connections = malloc(sizeof(junction_t *) * CONNECTIONS);
	box->num_connections = 0;
	
	box->parent = box;
	
	box->visited = 0;
	
	return box;
}

void junction_destroy(junction_t *box) {
	
	if (box) {
		
		free(box->connections);
	}
	
	free(box);
}

junction_t *get_root(junction_t *junction) {
	
	while (junction != junction->parent) {
		
		junction = junction->parent;
	}
	
	return junction;
}

void junction_connect(junction_t *a, junction_t *b) {
	
	a->connections[a->num_connections++] = b;
	b->connections[b->num_connections++] = a;
	
	if (a->num_connections >= b->num_connections) {
		
		get_root(b)->parent = a;
	} else {
		
		get_root(a)->parent = b;
	}
}

int is_connected(junction_t *a, junction_t *b) {
	
	return (get_root(a) == get_root(b));
}

uint64_t calc_distance(junction_t *a, junction_t *b) {
	
	uint64_t dx = b->x - a->x;
	uint64_t dy = b->y - a->y;
	uint64_t dz = b->z - a->z;
	
	return (dx * dx) + (dy * dy) + (dz * dz);
}

void connect_next_smallest(junction_t **boxes, junction_t **box_1, junction_t **box_2) {
	
	uint64_t curr_min = UINT64_MAX;
	for (size_t i = 0; i < LINES - 1; ++i) {
		
		for (size_t j = i + 1; j < LINES; ++j) {
			
			uint64_t distance = precalced_distances[boxes[i]->id][boxes[j]->id];
			
			if (distance >= curr_min) {
				
				continue;
			}
			
			if (is_connected(boxes[i], boxes[j])) {
				
				continue;
			}
			
			curr_min = distance;
			*box_1 = boxes[i];
			*box_2 = boxes[j];
		}
	}
	
	junction_connect(*box_1, *box_2);
}

void clear_visited(junction_t *junction) {
	
	if (!junction->visited) {
		
		return;
	}
	
	junction->visited = 0;
	for (size_t index = 0; index < junction->num_connections; ++index) {
		
		clear_visited(junction->connections[index]);
	}
}

uint64_t calc_total_connected(junction_t *junction) {
	
	if (junction->visited) {
		
		return 0;
	}
	
	junction->visited = 1;
	
	uint64_t total_connected = 1;
	for (uint64_t index = 0; index < junction->num_connections; ++index) {
		
		total_connected += calc_total_connected(junction->connections[index]);
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
	
	for (size_t outer_index = 0; outer_index < LINES; ++outer_index) {
		
		for (size_t inner_index = outer_index + 1; inner_index < LINES; ++inner_index) {
			
			junction_t *box_1 = boxes[inner_index];
			junction_t *box_2 = boxes[outer_index];
			precalced_distances[box_1->id][box_2->id] = precalced_distances[box_2->id][box_1->id] = calc_distance(box_1, box_2);
		}
	}
	
	junction_t *last_1;
	junction_t *last_2;
	
	uint64_t total_connected = 0;
	while (total_connected < LINES) {
		
		connect_next_smallest(boxes, &last_1, &last_2);
		total_connected = calc_total_connected(boxes[0]);
		clear_visited(boxes[0]);
	}
	
	if (total_connected != LINES) {
		
		puts("Error: total_connected is bigger than the number of junction boxes.\n");
		clean_aoc(UINT64_MAX, input);
		return EXIT_FAIL;
	}
	
	uint64_t prod = last_1->x * last_2->x;
	
	free(state);
	for(uint64_t index = 0; index < LINES; ++index) {
		
		junction_destroy(boxes[index]);
	}
	
	clean_aoc(prod, input);
	return EXIT_SUCCESS;
}

