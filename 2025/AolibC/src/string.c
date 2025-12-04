#include <string.h>

void *memcpy(void *dst, const void *src, size_t count) {
	
	size_t index = 0;
	while (*(((unsigned char *)(src)) + index) && index < count) {
		
		*(((unsigned char *)(dst)) + index) = *(((unsigned char *)(src)) + index);
		++index;
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

