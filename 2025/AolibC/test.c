#include <stdio.h>
#include <stdlib.h>

int main(void) {
	
	int *ptr = malloc(sizeof(int));
	*ptr = 4;
	putc(*ptr + '0', stdout);
	puts("\n");
	free(ptr);
	
	int *ptr_1 = malloc(sizeof(int));
	int *ptr_2 = malloc(sizeof(char));
	
	*ptr_1 = 5;
	*ptr_2 = 'A';
	
	putc(*ptr_1 + '0', stdout);
	puts("\n");
	
	putc(*ptr_2, stdout);
	puts("\n");
	
	free(ptr_2);
	free(ptr_1);
	
	int *large_ptr = malloc(100000);
	large_ptr[0] = 0;
	putc(large_ptr[0] + '0', stdout);
	puts("\n");
	free(large_ptr);
	
	return 0;
}

