#include <stdio.h>
#include <stdlib.h>

// defining point struct(class)
struct point{
	float x;
	float y;
};

int main(int argc, char **argv)
{
	struct point *pointer = 0;
	
	/* defining variable(object)
	   of type point - p*/
	struct point p;
	p.x = 3.14; p.y = 2.78;
	struct point p2;
	p2.x = 23.14; p2.y = 23.78;
	printf("%f\n", p.x);
	printf("%f\n", p2.x);
	
	// sizeof point
	printf("%ld\n", sizeof(struct point));
	printf("%ld\n", sizeof(p));
	
	// defining a single struct(object)
	struct{
		float x;
		float y;
		float z;
	} p3d;
	p3d.x = 1; p3d.y = 2; p3d.z = 3;
	printf("%f\n", p3d.y);
	
	// dynamically allocated struct
	pointer = malloc(sizeof(struct point));
	
	/* 2 ways to reference it's members
	   "->" is apparently recomended */
	(*pointer).x = 42.0;
	pointer -> y = 12.5;
	printf("%f\n", pointer->x);
	printf("%f\n", (*pointer).y);
	
	free(pointer);
	
	// Note: typedef, union, enum... also exist

	return 0;
}