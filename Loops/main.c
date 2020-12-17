#include <stdio.h>

int main(int argc, char **argv)
{
	int  i, j;
	
	for (i = 0; i < 10; i++) {
		printf("this is %d iteration of 1st loop\n", i);
	}
	
	for (i = -1; i < 100; i = i * (-2)) {
		printf("this loop multiplies by -2 each time: %d\n", i);
	}
	
	/* Same as first loop, but using while instead */
	i = 0;
	while (i < 10) {
		printf("this is %d iteration of 3rd loop\n", i);
		i++;
	}
	
	/* Note: there are also break and continue,
	   but i know those out of python already */
	
	printf("Here comes the neseted loop with goto:\n");
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			printf("%d x %d\n", i, j);
			if (i == 3 && j == 7) {
				/* using goto to break out of nested loop
				   yes, i know everybody hates goto-s */
				goto end_of_the_nested_loop;
			}
		}
	}
	end_of_the_nested_loop:
	
	/* since i am given goto-s...
	   i always wanted to do this
	   same as first loop, but with goto-s */
	i = 0;
	begin_goto_loop:
	if (!(i < 10)) goto end_goto_loop;
		printf("this is %d iteration of the goto loop\n", i);
		i++;
	goto begin_goto_loop;
	end_goto_loop:
	// ok, sorry for that lol
	
	return 0;
}
