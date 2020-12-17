#include <stdio.h>

int main(int argc, char **argv)
{
	// declare variable
	int var1 = 42;
	
	/* declare NULL-pointer if value
	   is not yet known */
	int *var1_pointer = NULL;
	
	/* Creates new pointer that is
	   pointing to "Hello, World!"
	                ^              */
	char *string = "Hello, world!";
	printf("%d\n", string);
	printf("%c\n", *string);
	
	// point the pointer to var_1
	var1_pointer = &var1;
	
	// print pointer adress
	printf("%d\n", var1_pointer);
	
	// print value that the pointer is pointing to
	printf("%d\n", *var1_pointer);
	
	// check if var1_pointer is NULL-pointer
	if (var1_pointer) {
		printf("isn't a NULL\n");
	}else {
		printf("is a NULL\n");
	}
	
	// Increments string pointer by 1
	string++;
	printf("%c\n", *string);
	// Decrements string pointer by 1
	string--;
	printf("%c\n", *string);
	/* Increments string pointer by 7
	   which makes it point to "Hello, world!"
									   ^       */
	string = string + 7;
	printf("%c\n", *string);
	printf(string); // this does print the rest of it
	printf("\n");
	
	/* Notes:
	       One might create an array of pointers;
		   One might create chains of pointers;
		   One might pass pointer to a function to change
		       value of a variable;
		   One might return a pointer from a function. */

	return 0;
}
