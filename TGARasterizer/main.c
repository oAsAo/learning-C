#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define FULLPATH "/home/sergey/raster_test.tga"
#define WIDTH 1920
#define HEIGHT 1080

struct color{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};
struct image{
	unsigned short width;
	unsigned short height;
	FILE* file_pointer;
	struct color* array;
};

struct image new_image(char* full_path, unsigned short width, unsigned short height);
void close_image(struct image pic);
void draw_line(struct image pic, struct color colour, int x1, int y1, int x2, int y2);

int main(int argc, char **argv)
{
	int i, j;
	struct color black;
	//struct color white;
	//struct color red;
	struct color green;
	//struct color blue;
	black.r =   0; black.g =   0; black.b =   0;
	//white.r = 255; white.g = 255; white.b = 255;
	//red.r =   255;   red.g =   0;   red.b =   0;
	green.r =   0; green.g = 255; green.b =   0;
	//blue.r =    0;  blue.g =   0;  blue.b = 255;
	
	struct image pic = new_image(FULLPATH, WIDTH, HEIGHT);
	
	// fill screen black
	for (i=0; i<1920; i++) {
		for (j=0; j<1080; j++) {
			pic.array[i + 1920*j] = black;
		}
	}
	draw_line(pic, green, 300, 300, 300, 800);
	draw_line(pic, green, 300, 300, 800, 300);
	draw_line(pic, green, 800, 800, 800, 300);
	draw_line(pic, green, 800, 800, 300, 800);
	
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
			if ((i + c2*pic.width) >= pic.width*pic.height || (i + c2*pic.width) < 0) continue;
			pic.array[i + c2*pic.width] = colour;
		}
	} else {
		b = x1 - y1*(x1 - x2)/(y1 - y2);
		for (i = y1; i < y2; i++) {
			c2 = i*(x1 - x2)/(y1 - y2) + b;
			if ((c2 + i*pic.width) >= pic.width*pic.height || (c2 + i*pic.width) < 0) continue;
			pic.array[c2 + i*pic.width] = colour;
		}
	}
}

