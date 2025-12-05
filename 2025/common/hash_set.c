#include <hash_set.h>

#define BUCKET_RESERVED_INIT   1024
#define BUCKET_RESERVED_FACTOR 2

#define SET_BUCKETS 1024
#define HASH(x) ((x) % SET_BUCKETS)

// ---------------------------- BUCKET ---------------------------- //

void init_bucket(bucket_t *bucket) {
	
	bucket->bucket_size = 0;
	bucket->bucket_reserved = BUCKET_RESERVED_INIT;
	bucket->values = malloc(sizeof(uint64_t) * bucket->bucket_reserved);
}

void cleanup_bucket(bucket_t *bucket) {
	
	if (!bucket) {
		
		return;
	}
	
	free(bucket->values);
}

int bucket_contains(bucket_t *bucket, uint64_t value) {
	
	for (size_t index = 0; index < bucket->bucket_size; ++index) {
		
		if (bucket->values[index] == value) {
			
			return 1;
		}
	}
	
	return 0;
}

int bucket_push(bucket_t *bucket, uint64_t value) {
	
	if (bucket_contains(bucket, value)) {
		
		return 0;
	}
	
	if (bucket->bucket_size == bucket->bucket_reserved) {
		
		bucket->bucket_reserved *= BUCKET_RESERVED_FACTOR;
		uint64_t *new_values = malloc(sizeof(uint64_t) * bucket->bucket_reserved);
		
		for (size_t index = 0; index < bucket->bucket_size; ++index) {
			
			new_values[index] = bucket->values[index];
		}
		
		free(bucket->values);
		bucket->values = new_values;
	}
	
	bucket->values[bucket->bucket_size] = value;
	bucket->bucket_size++;
	return 1;
}

// ---------------------------- SET ---------------------------- //

void init_set(set_t *set) {
	
	set->num_buckets = SET_BUCKETS;
	set->num_elements = 0;

	set->buckets = malloc(sizeof(bucket_t) * set->num_buckets);
	
	for (size_t index = 0; index < set->num_buckets; ++index) {
		
		set->buckets[index] = malloc(sizeof(bucket_t));
		init_bucket(set->buckets[index]);
	}
}

void cleanup_set(set_t *set) {
	
	if (!set) {
		
		return;
	}
	
	for (size_t index = 0; index < set->num_buckets; ++index) {
		
		cleanup_bucket(set->buckets[index]);
		free(set->buckets[index]);
	}
	
	free(set->buckets);
}

int set_contains(set_t *set, uint64_t value) {
	
	return bucket_contains(set->buckets[HASH(value)], value);
}

int set_push(set_t *set, uint64_t value) {
	
	int pushed = bucket_push(set->buckets[HASH(value)], value);
	
	if (pushed) {
		
		set->num_elements++;
	}
	
	return pushed;
}

