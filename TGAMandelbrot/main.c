#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define FULLPATH "/home/sergey/test.tga"
#define HEADERLEN 18
#define QUARTERWIDTH 480
#define QUARTERHEIGHT 270

struct color{
	char R;
	char G;
	char B;
};

void append_pixel(FILE *pointer, struct color pixel);
struct color mandelbrot(float x, float y);
struct color pallette(int i, float abs_z);

int main(int argc, char **argv)
{
	int i, j;
	float x, y;
	struct color pixel;
	char header[HEADERLEN] = {
		0, // id field length(absent)
		0, // colormap type(not used)
		2, // image type(TrueColor, no compression)
		0, 0, 0, 0, 0, // colormap specs(zeroed)
		
		0, 0, // position X
		0, 0, // position Y
		128, 7, // width (those are little endian)
		56, 4, // height
		24, // bits per pixel
		24 // pixels up to down, left to right, no alpha
	};
	
	// create/open file
	FILE *file_pointer = NULL;
	file_pointer = fopen(FULLPATH, "w");
	if(!file_pointer) {
        fprintf(stderr,"error opening file...exiting\n");
        exit(1);
	}
	
	// writing header
	for (i = 0; i < HEADERLEN; i++) {
		fputc(header[i], file_pointer);
	}
	
	// filling in the image
	for (i = 0; i < (QUARTERHEIGHT*4); i++) {
		for (j = 0; j < (QUARTERWIDTH*4); j++) {
			x = ((QUARTERWIDTH*2) - (float) j)/QUARTERHEIGHT;
			y = ((float) i - (QUARTERHEIGHT*2))/QUARTERHEIGHT;
			pixel = mandelbrot(x, y);
			append_pixel(file_pointer, pixel);
		} 
	}
	
	// writing footer
	for (i = 0; i < 8; i ++) fputc(0, file_pointer);
	fprintf(file_pointer, "TRUEVISION-XFILE.");
	fputc(0, file_pointer);

	fclose(file_pointer);
	
	return 0;
}

void append_pixel(FILE *pointer, struct color pixel) {
	fputc(pixel.B, pointer); // B
	fputc(pixel.G, pointer); // G
	fputc(pixel.R, pointer); // R
}

struct color mandelbrot(float x, float y) {
	int i;
	float x2 = 0, y2 = 0, x2_old = 0, y2_old = 0;
	struct color pixel;

	for (i = 0; i < 100; i++) {
		x2_old = x2;
		y2_old = y2;
		x2 = x2_old*x2_old - y2_old*y2_old + x;
		y2 = 2*y2_old*x2_old + y;
		if (abs(x2) > 100 || abs(y2) > 100) {
			return pallette(i, x2*x2 + y2*y2);
		}
	}

	pixel.R = 0;
	pixel.G = 0;
	pixel.B = 0;
	return pixel;
}

struct color pallette(int i, float abs_z) {
	struct color pixel;
	float li;
	
	li = (float) (i + 1);
	li -= log(0.5 * log(abs_z)) / 0.69314718;
	li = fmod(li, 12) / 2;
	if (li > 3) li = 6 - li; // makes it pongs
	
	if (li < 1) {
		pixel.R = 0;
		pixel.G = (char) (255*fmod(li, 1));
		pixel.B = (char) (255 - 255*fmod(li, 1));
	} else if (li < 2) {
		pixel.R = (char) (255*fmod(li, 1));
		pixel.G = (char) (255 - 255*fmod(li, 1));
		pixel.B = 0;
	} else {
		pixel.R = (char) (255 - 255*fmod(li, 1));
		pixel.G = 0;
		pixel.B = (char) (255*fmod(li, 1));
	}
	
	return pixel;
}