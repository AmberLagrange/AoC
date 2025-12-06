
extern void __cleanup_malloc(void);

void _cleanup(void) {
	
	__cleanup_malloc();
}

