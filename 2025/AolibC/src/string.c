#include <string.h>

#define WORD_SIZE 8

#define MEMCPY_WORD(dst, src) do {	\
									\
	(dst)[0] = (src)[0];			\
	(dst)[1] = (src)[1];			\
	(dst)[2] = (src)[2];			\
	(dst)[3] = (src)[3];			\
	(dst)[4] = (src)[4];			\
	(dst)[5] = (src)[5];			\
	(dst)[6] = (src)[6];			\
	(dst)[7] = (src)[7];			\
} while (0)

#define MEMCPY_BYTE(dst, src) do {	\
									\
	(dst)[0] = (src)[0];			\
} while (0)

void *memcpy(void *dst, const void *src, size_t count) {
	
	size_t index = 0;
	while (count >= WORD_SIZE) {
		
		MEMCPY_WORD((unsigned char*)(dst) + index, (unsigned char *)(src) + index);
		index += WORD_SIZE;
		count -= WORD_SIZE;
	}
	
	while (count > 0) {
		
		MEMCPY_BYTE((unsigned char *)(dst) + index, (unsigned char *)(src) + index);
		index += 1;
		count -= 1;
	}
	
	return dst;
}

size_t strlen(const char *str) {
	
	unsigned long count = 0;
	while (*str++) {
		
		++count;
	}
	
	return count;
}

int strcmp(const char *lhs, const char *rhs) {
	
	int lhs_len = strlen(lhs);
	int rhs_len = strlen(rhs);
	
	if (lhs_len < rhs_len) {
		
		return -1;
	} else if (lhs_len > rhs_len) {
		
		return 1;
	}

	for (int i = 0; i < lhs_len; ++i) {
		
		if (lhs[i] < rhs[i]) {
			
			return -1;
		} else if (lhs[i] > rhs[i]) {
			
			return 1;
		}
	}
	
	return 0;
}

char *strncpy(char *dst, const char *src, size_t count) {
	
	return memcpy(dst, src, count);
}

char *__strtok_str;
char *strtok(char *str, const char *delims) {
	
	if (str != NULL) {
		
		__strtok_str = str;
	}
	
	if (__strtok_str == NULL) {
		
		return NULL;
	}

	int str_len = strlen(__strtok_str);
	int delim_len = strlen(delims);
	
	char *prev_str = __strtok_str;
	for (int i = 0; i < str_len; ++i) {
		
		for (int d = 0; d < delim_len; ++d) {
			
			if (__strtok_str[i] == delims[d]) {
				
				__strtok_str[i] = '\0';
				__strtok_str = __strtok_str + i + 1;
				return prev_str;
			}
		}
	}
	
	if (__strtok_str != NULL) {
		
		__strtok_str = NULL;
	}
	
	return prev_str;
}

