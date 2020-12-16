#include <stdio.h>
unsigned int foo = 2, bar = 2, foobar;

int main() {
	foobar = foo + bar;
	printf("%d + %d = %d\n", foo, bar, foobar);
	return 0;
}
