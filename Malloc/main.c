#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	// create a NULL pointer
	int *pointer = NULL;
	
	/* allocate 4 bytes of memory, and point
	   pointer to them */
	pointer = malloc(sizeof(int));
	
	// print out the adress where it points
	printf("%d\n", pointer);
	
	// write 42 into the newly-allocated memory
	*pointer = 42;
	
	// print 42 from where the pointer is pointing to
	printf("%d\n", *pointer);
	
	// abandon the memory
	free(pointer);
	
	/* pointer still points to the same place,
	   but apparently freed memory is zeroed
	   (implementation-specific?) */
	printf("%d\n", pointer);
	printf("%d\n", *pointer);
	
	// Note: realloc and calloc do exist
	
	return 0;
}
