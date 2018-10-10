#include <stdio.h>

#include <string.h>

#include <malloc.h>

#pragma pack(push, 1)

typedef struct tagBITMAPINFOHEADER {

unsigned long biSize;

long biWidth;

long biHeight; #

unsigned short biPlanes;

unsigned short biBitCount;

unsigned long biCompression;

unsigned long biSizeImage;

long biXPelsPerMeter;

long biYPelsPerMeter;

unsigned long biClrUsed;

unsigned long biClrImportant;

} BITMAPINFOHEADER;

typedef struct tagBITMAPFILEHEADER {

unsigned short bfType;

unsigned long bfSize;

unsigned short bfReserved1;

unsigned short bfReserved2;

unsigned long bfOffBits;

} BITMAPFILEHEADER;

#pragma pack(pop)

struct pixel

{

unsigned char b;

unsigned char g;

unsigned char r;

};

//funtcion that check params

int check_params(int width, int height, int offset_width, int offset_height , int real_width, int real_height)

{

if (width < 1 || height < 1)

return 0;

if (offset_width < 0 || offset_width >real_width - 2 || offset_height < 0 || offset_height > real_height - 2)

return 0;

width += offset_width;

height += offset_height;

if (width > real_width || height > real_height)

return 0;

return 1;

}

int main()

{

struct pixel ** img;

BITMAPFILEHEADER head_in;

BITMAPINFOHEADER info_in;

FILE *in, *out;

unsigned char a;

int round;

unsigned char *junk;

int offset_width, offset_height, height, width;

//reading headers of file

in = fopen("in.bmp", "rb");

fread(&head_in, sizeof(BITMAPFILEHEADER), 1, in);

if (head_in.bfType != 0x4d42)

{

printf("invalid type of file\n");

return 0;

}

fread(&info_in, sizeof(BITMAPINFOHEADER), 1, in);

round = (info_in.biSizeImage - info_in.biHeight * info_in.biWidth * 3) / info_in.biHeight;

printf("size in pixels %dx%d\n", info_in.biWidth, info_in.biHeight);

//allocating memory for pixels

img = (struct pixel**)(malloc(info_in.biHeight*sizeof(unsigned char *)));

for (int i = 0; i < info_in.biHeight; ++i)

{

img[i] = (struct pixel *)malloc(info_in.biWidth * 3);

}

//getting params

printf("input params in this format:\nwidth,height,offset_width,offset_height\n");

scanf("%d,%d,%d,%d", &width, &height, &offset_width, &offset_height);

//checking for correct params

if (!check_params(width, height, offset_width, offset_height, info_in.biWidth, info_in.biHeight))

{

printf("enter right params!\n");

for (int i = 0; i < info_in.biHeight; ++i)

{

free(img[i]);

}

free(img);

getchar();

return 0;

}

//color pixel readout

fseek(in, head_in.bfOffBits, SEEK_SET);

for (int i = 0; i < info_in.biHeight; ++i)

{

for (int j = 0; j < info_in.biWidth; ++j)

{

fread(&img[i][j], 1, 3, in);

}

fread(&junk, 1, round, in);

}

//drawing rectangle into massive

for (int i = 0; i < info_in.biHeight; ++i)

{

for (int j = 0; j < info_in.biWidth; ++j)

{

if (i >= offset_height && i <= offset_height + height && j >= offset_width && j <= offset_width + width)

{

img[i][j].r = 32;

img[i][j].g = 227;

img[i][j].b = 35;

}

}

}

//creating output file and filling it

out = fopen("out.bmp", "wb");

fseek(in, 0, SEEK_SET);

for (int i = 0; i < head_in.bfOffBits; ++i)

{

a = fgetc(in);

fwrite(&a,sizeof(char),1,out);

}

for (int i = 0; i < info_in.biHeight; ++i)

{

for (int j = 0; j < info_in.biWidth; ++j)

{

fwrite(&img[i][j].b, sizeof(char), 1, out);

fwrite(&img[i][j].g, sizeof(char), 1, out);

fwrite(&img[i][j].r, sizeof(char), 1, out);

}

fwrite(&junk, 1, round, out);

}

//free memory and closing files

fclose(in);

fclose(out);

for (int i = 0; i < info_in.biHeight; ++i)

{

free(img[i]);

}

free(img);

}
