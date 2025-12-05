#ifndef HASH_SET_H
#define HASH_SET_H

#include <string.h>
#include <stdint.h>

typedef struct {
	
	uint64_t *values;
	size_t bucket_size;
	size_t bucket_reserved;
} bucket_t;

typedef struct {
	
	bucket_t **buckets;
	size_t num_buckets;
	size_t num_elements;
} set_t;

#endif // HASH_SET_H

