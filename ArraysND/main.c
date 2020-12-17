#include <stdio.h>

int main(int argc, char **argv) {

	unsigned char array[2][3][4] = {
		{
			{1, 2, 3, 10},
			{4, 5, 6},
			{7, 8, 9}
		},
		{
			{11, 12, 13},
			{14, 15, 16},
			{17, 18, 19}
		}
	};
	printf("%d\n", array[1][0][2]);
	return 0;
}
