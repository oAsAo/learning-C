#include <stdio.h> // printf
#include <stdint.h> // uint64_t

// Declare functions before main.
uint64_t factorial(short x);
static uint64_t factorial_with_acc(short x, uint64_t acc);

int main(int argc, char **argv)
{
	short i;
	for (i = 0; i < 21; i++) {
		printf("%d! = %lu\n", i, factorial(i));
	}
	return 0;
}

/* Define functions after main.

   "factorial" function is used here
   to... basicaly define the default value of
   acc (of 1) for the other function
   
   Also x shall be in range [0, 21) cuz uint64_t seems
   to overflow after that */
uint64_t factorial(short x) {
	return factorial_with_acc(x, 1);
}
static uint64_t factorial_with_acc(short x, uint64_t acc) {
	if (x <= 1) {
		return acc;
	}
	return factorial_with_acc(x-1, x*acc);
}