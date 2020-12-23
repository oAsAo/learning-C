#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define FULLPATH "/home/sergey/raster_test.tga"
#define WIDTH 1920
#define HEIGHT 1080

struct color {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};
struct image {
	unsigned short width;
	unsigned short height;
	FILE* file_pointer;
	struct color* array;
};
struct quaternion {
	float r;
	float i;
	float j;
	float k;
};
struct polygon {
	struct color colour;
	float x1;
	float y1;
	float z1;
	float x2;
	float y2;
	float z2;
	float x3;
	float y3;
	float z3;
};
// struct camera {
// 	float x;
//	float y;
//	float z;
//	struct quaternion heading;
// };

struct image new_image(char* full_path, unsigned short width, unsigned short height);
void close_image(struct image pic);
void draw_point(struct image pic, struct color colour, int x, int y);
void draw_line(struct image pic, struct color colour, int x1, int y1, int x2, int y2);
void fill_triangle(struct image pic, struct color colour, int x1, int y1, int x2, int y2, int x3, int y3);
void render_polygon(struct image pic, struct polygon* poly);
struct quaternion quaternion_product(struct quaternion a, struct quaternion b);

static void iterate_over_line(struct image pic, struct color colour, char mode, int x1, int y1, int x2, int y2, int x3, int y3);


int main(int argc, char **argv) {
	int i, j;
	
	struct color black;
	//struct color white;
	//struct color red;
	struct color green;
	struct color blue;
	black.r =   0; black.g =   0; black.b =   0;
	//white.r = 255; white.g = 255; white.b = 255;
	//red.r =   255;   red.g =   0;   red.b =   0;
	green.r =   0; green.g = 255; green.b =   0;
	blue.r =    0;  blue.g =   0;  blue.b = 255;
	struct polygon p1;
	p1.x1 = 3.0; p1.y1 = 0.0; p1.z1 = 1.0;
	p1.x2 = 3.0; p1.y2 = 1.0; p1.z2 = 1.0;
	p1.x3 = 3.0; p1.y3 = 1.0; p1.z3 = 0.0;
	p1.colour = green;
	struct polygon p2;
	p2.x1 = 3.0; p2.y1 = 0.0; p2.z1 = 1.0;
	p2.x2 = 2.0; p2.y2 = 0.0; p2.z2 = 0.0;
	p2.x3 = 3.0; p2.y3 = 1.0; p2.z3 = 0.0;
	p2.colour = blue;
	
	struct image pic = new_image(FULLPATH, WIDTH, HEIGHT);
	
	// fill screen black
	for (i=0; i<1920; i++) {
		for (j=0; j<1080; j++) {
			pic.array[i + 1920*j] = black;
		}
	}
	// draw_line(pic, green, 300, 300, 300, 800);
	// draw_line(pic, green, 300, 300, 800, 300);
	// draw_line(pic, green, 800, 800, 800, 300);
	// draw_line(pic, green, 800, 800, 300, 800);
	
	// fill_triangle(pic, green, 800, 300, 800, 350, 1300, 800);
	render_polygon(pic, &p2);
	render_polygon(pic, &p1);
	
	close_image(pic);
	return 0;
}

struct image new_image(char* full_path, unsigned short width, unsigned short height){
	#define HEADERLEN 18
	
	int i;
	char header[HEADERLEN] = {
		0, // id field length(absent)
		0, // colormap type(not used)
		2, // image type(TrueColor, no compression)
		0, 0, 0, 0, 0, // colormap specs(zeroed)
		
		0, 0, // position X
		0, 0, // position Y
		0, 0, // width (those are little endian)
		0, 0, // height
		24, // bits per pixel
		32
	};
	
	// allocating memory for metadata (struct image)
	struct image pic;
	pic.width = width;
	pic.height = height;
	pic.file_pointer = NULL;
	/* allocating memory for pixel array
	   image itself only stores a pointer to it, so it can be passed by value*/
	pic.array = malloc(3*width*height*sizeof(char));
	
	/* TODO: zero the array?
	   in my case it is already zeroed for some reason */
	
	// writes the correct width&height to the .tga header:
	header[12] = width & 255;
	header[13] = (width >> 8) & 255;
	header[14] = height & 255;
	header[15] = (height >> 8) & 255;
	
	// create/open file
	pic.file_pointer = fopen(full_path, "w");
	if(!pic.file_pointer) {
        fprintf(stderr,"error opening file...exiting\n");
        exit(1);
	}
	
	// writing header
	for (i = 0; i < HEADERLEN; i++) {
		fputc(header[i], pic.file_pointer);
	}
	
	return pic;
	
	#undef HEADERLEN
}

void close_image(struct image pic){
	unsigned long i;
	// writing from array into the file
	for (i = 0; i < pic.width*pic.height; i++) {
		fputc(pic.array[i].b, pic.file_pointer);
		fputc(pic.array[i].g, pic.file_pointer);
		fputc(pic.array[i].r, pic.file_pointer);
	}
	
	// writing footer
	for (i = 0; i < 8; i ++) fputc(0, pic.file_pointer);
	fprintf(pic.file_pointer, "TRUEVISION-XFILE.");
	fputc(0, pic.file_pointer);
	
	fclose(pic.file_pointer);
	
	free(pic.array);
}

void draw_line(struct image pic, struct color colour, int x1, int y1, int x2, int y2) {
	iterate_over_line(pic, colour, 0, x1, y1, x2, y2, 0, 0);
}

void fill_triangle(struct image pic, struct color colour, int x1, int y1, int x2, int y2, int x3, int y3){
	// this is not the best way of doing that, but i will refactor it later...
	iterate_over_line(pic, colour, 1, x1, y1, x2, y2, x3, y3);
}

static void iterate_over_line(struct image pic, struct color colour, char mode, int x1, int y1, int x2, int y2, int x3, int y3) {
	int i;
	int b;
	int c2;
	
	/* make sure point 1 has the smallest of x1, x2
	   (if iterating over x, else smallest of y-s)
	   by exchanging values if necessary */
	if (((x2 < x1) && (abs(x1 - x2) > abs(y1 - y2)))
			|| (y2 < y1)) {
		x1 = x1 + x2;
		x2 = x1 - x2;
		x1 = x1 - x2;
		y1 = y1 + y2;
		y2 = y1 - y2;
		y1 = y1 - y2;
	}
	
	/* if change of y is small, iterate over x,
	   else iterate over y */
	if (abs(x1 - x2) > abs(y1 - y2)) {
		b = y1 - x1*(y1 - y2)/(x1 - x2);
		for (i = x1; i < x2; i++) {
			c2 = i*(y1 - y2)/(x1 - x2) + b;
			if (mode == 0) {
				draw_point(pic, colour, i, c2);
			} else if (mode == 1) {
				draw_line(pic, colour, i, c2, x3, y3);
			}
		}
	} else {
		b = x1 - y1*(x1 - x2)/(y1 - y2);
		for (i = y1; i < y2; i++) {
			c2 = i*(x1 - x2)/(y1 - y2) + b;
			if (mode == 0) {
				draw_point(pic, colour, c2, i);
			} else if (mode == 1) {
				draw_line(pic, colour, c2, i, x3, y3);
			}
		}
	}
}

void draw_point(struct image pic, struct color colour, int x, int y) {
	if ((1 <= x) && (x+1 < pic.width)) {
		if ((1 <= y) && (y+1 < pic.height)) {
			pic.array[x + y*pic.width] = colour;
			
			pic.array[(x+1) + y*pic.width] = colour;
			pic.array[(x-1) + y*pic.width] = colour;
			pic.array[x + (y+1)*pic.width] = colour;
			pic.array[x + (y-1)*pic.width] = colour;
		}
	}
}

struct quaternion quaternion_product(struct quaternion a, struct quaternion b) {
	struct quaternion c;
	c.r = (a.r * b.r) - (a.i * b.i) - (a.j * b.j) - (a.k * a.k);
	c.i = (a.r * b.i) + (a.i * b.r) + (a.j * b.k) - (a.k * b.j);
	c.j = (a.r * b.j) - (a.i * b.k) + (a.j * b.r) + (a.k * b.i);
	c.k = (a.r * b.k) + (a.i * b.j) - (a.j * b.i) + (a.k * b.r);
	return c;
}

void render_polygon(struct image pic, struct polygon* poly) {
	int x1, y1, x2, y2, x3, y3;
	x1 = (int) ((pic.width >> 1)*(poly->y1)/(poly->x1) + (pic.width >> 1));
	y1 = (int) ((pic.width >> 1)*(poly->z1)/(poly->x1) + (pic.height >> 1));
	x2 = (int) ((pic.width >> 1)*(poly->y2)/(poly->x2) + (pic.width >> 1));
	y2 = (int) ((pic.width >> 1)*(poly->z2)/(poly->x2) + (pic.height >> 1));
	x3 = (int) ((pic.width >> 1)*(poly->y3)/(poly->x3) + (pic.width >> 1));
	y3 = (int) ((pic.width >> 1)*(poly->z3)/(poly->x3) + (pic.height >> 1));
	fill_triangle(pic, poly->colour, x1, y1, x2, y2, x3, y3);
}

