#include <stdio.h>

int main(int argc, char **argv) {

	unsigned char i, flag_word;

	for (i = 1; i <= 100; i++) {

		/* Fizzing and Buzzing logic,
		   flag_word will be 0 if nothing was printed */
		flag_word = 0;
		if (i % 3 == 0) {
			printf("Fizz");
			flag_word = 1;
		}
		if (i % 5 == 0) {
			printf("Buzz");
			flag_word = 1;
		}

		/* if Fizz/Buzz/FizzBuzz wasn't printed,
		   then print the number itself */
		if (flag_word == 0) {
			printf("%d", i);
		}

		// add newline for the next time
		printf("\n");
	}
	return 0;
}
