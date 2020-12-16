#include <stdio.h>
// ok, no global variables anymore

int main(int argc, char **argv)
{
	signed int five_numbers[5];
	unsigned char i = 4;
	
	five_numbers[0] = 2;
	five_numbers[1] = -123;
	five_numbers[2] = 0;
	five_numbers[3] = 2;
	five_numbers[4] = 42;
	
	printf("%d\n", five_numbers[i]);
	return 0;
}
