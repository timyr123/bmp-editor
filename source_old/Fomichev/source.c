#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define BMP_TYPE	0x4D42

struct bmp_header_s
{
	uint16_t type;
	uint32_t size;
	uint16_t __rsvd1;
	uint16_t __rsvd2;
	uint32_t offset;

	uint32_t version;
	uint32_t width;
	uint32_t height;
	uint16_t planes;
	uint16_t bitspp;
	uint16_t compress;
}
__attribute__((packed));

uint32_t get_color(const void *color, int bytespp)
{
	uint32_t c;

	switch ( bytespp )
	{
		case 1:
			c = *(uint8_t *)color;
			break;
		case 2:
			c = *(uint16_t *)color;
			break;
		case 4:
			c = *(uint32_t *)color;
			break;

		case 3:
		default:
			c = *(((uint8_t *)color + 2));
			c <<= 16;
			c |= *(uint16_t *)color;
			break;
	}

	return c;
}

int compar(const void *col1, const void *col2, void *bytespp)
{
	uint32_t a = get_color(col1, *(int *)bytespp);
	uint32_t b = get_color(col2, *(int *)bytespp);

	if ( a < b )
		return -1;
	if ( a > b )
		return 1;
	return 0;
}

void print_color(uint32_t color, int bytespp, double rate)
{
	printf((bytespp > 2 ? (bytespp > 3 ? "%08X: %f\n" : "%06X: %f\n") : (bytespp > 0 ? "%04X: %f\n" : "%02X: %f\n")), color, rate);
}

void print(uint8_t *img, size_t img_size, int bytespp, double rate)
{
	int c = 1;
	uint32_t curr;
	uint32_t next;

	curr = get_color(img, bytespp);
	for ( size_t i = 0; i < img_size; i += bytespp )
	{
		if ( i + bytespp <= img_size )
			next = get_color(img + i + bytespp, bytespp);
		else
			next = curr + 1;

		if ( next != curr )
		{
			print_color(curr, bytespp, (double)c * rate);
			curr = next;
			c = 0;
		}

		c++;
	}
}

int main(int argc, char *argv[])
{
	uint8_t *img;
	size_t img_size;
	int bytespp;

	char *filename;
	FILE *pf;

	double width, height;
	struct bmp_header_s hdr;

	if ( argc == 1 )
	{
		printf("Usage: %s filename width height\n", argv[0]);
		exit(EXIT_SUCCESS);
	}
	if ( argc < 4 )
	{
		fprintf(stderr, "Missing argument!\n");
		exit(EXIT_FAILURE);
	}

	filename = argv[1];
	width = atof(argv[2]);
	height = atof(argv[3]);

	if ( (width <= 0) || (height <= 0) )
	{
		fprintf(stderr, "Incorrect width (%f) or/and height (%f)\n", width, height);
		exit(EXIT_FAILURE);
	}

	if ( (pf = fopen(filename, "r")) == NULL )
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}

	if ( fread(&hdr, sizeof(hdr), 1, pf) != 1 )
	{
		perror("fread()");
		fclose(pf);
		exit(EXIT_FAILURE);
	}

	fclose(pf);

	if ( (hdr.type != BMP_TYPE) || (hdr.planes != 1) )
	{
		fprintf(stderr, "Not a BMP file!\n");
		exit(EXIT_FAILURE);
	}

	if ( (hdr.version != 40) && (hdr.version != 108) && (hdr.version != 124) )
	{
		fprintf(stderr, "Unsupported BMP version: %u\n", hdr.version);
		exit(EXIT_FAILURE);
	}

	if ( (hdr.bitspp != 8) && (hdr.bitspp != 16) && (hdr.bitspp != 24) && (hdr.bitspp != 32) )
	{
		fprintf(stderr, "Unsupported bits per pixel: %u\n", hdr.bitspp);
		exit(EXIT_FAILURE);
	}

	if ( hdr.compress != 0 )
	{
		fprintf(stderr, "Unsupported compression: %u\n", hdr.compress);
		exit(EXIT_FAILURE);
	}

	bytespp = hdr.bitspp / 8;
	img_size = hdr.width * hdr.height * bytespp;
	if ( (img = malloc(img_size)) == NULL )
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}

	if ( (pf = fopen(filename, "r")) == NULL )
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}

	if ( fseek(pf, hdr.offset, SEEK_SET) < 0 )
	{
		perror("fseek()");
		fclose(pf);
		exit(EXIT_FAILURE);
	}

	if ( fread(img, img_size, 1, pf) != 1 )
	{
		perror("fread()");
		fclose(pf);
		exit(EXIT_FAILURE);
	}

	fclose(pf);

	qsort_r(img, hdr.width * hdr.height, bytespp, compar, &bytespp);

	print(img, img_size, bytespp, width / (double)hdr.width * height / (double)hdr.height);

	free(img);

	return EXIT_SUCCESS;
}
