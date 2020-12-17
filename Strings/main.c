#include <stdio.h>
#include <string.h>

#define STRING4LENGTH 31

int main(int argc, char **argv) {
	char * string1 = "foo";
	char string2[] = "bar";
	char string3[7] = "foobar";
	char string4[STRING4LENGTH + 1] = "Longer strings, ";
	char string5[] = "that i wanna concatenate";
	
	
	// printing strings
	printf("%s\n", string1);
	printf("%s\n", string2);
	printf("%s\n", string3);
	
	/* getting size of the string, and printing it
	   here i also typecast cuz %d doesn't like
	   argument being unsigned long apparently */
	printf("%d\n", (int) strlen(string1));
	printf("%lu\n", strlen(string2));
	printf("%d\n", (char) strlen(string3));
	/* this returns actual string length, 
	   not buffer length or anything */
	printf("%lu\n", strlen(string4));
	
	/* Note to self: apparently strncmp is
	   recomended over strcmp where possible */
	if (strcmp(string1, string3) == 0) {
		printf("%s is the same as %s\n",
			   string1, string3);
	} else {
		printf("%s is not the same as %s\n",
			   string1, string3);
	}

	if (strncmp(string1, string3, 3) == 0) {
		printf("%s begins the same as %s\n",
			   string1, string3);
	} else {
		printf("%s does not begin the same as %s\n",
			   string1, string3);
	}
	
	/* string concatenation
	   strcat can be used when strings are
	   known to have null at the end (?) */
	strncat(string4, string5, STRING4LENGTH);
	printf("%s\n", string4);
	
	return 0;
}
