#include <stdio.h>
#include <unistd.h>

int main(void) {
	
	int *arr = sbrk(8);
	
	if (arr == (void *)(-1)) {
		
		puts("sbrk failed.\n");
		return -1;
	}
	
	for (size_t i = 0; i < 8; ++i) {
		
		arr[i] = i;
	}
	
	for (size_t i = 0; i < 8; ++i) {
		
		putc(arr[i] + '0', stdout);
		puts("\n");
	}
	
	sbrk(-8);
	
	return 0;
}

