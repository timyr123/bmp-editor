#include "stdio.h"
#include "string.h"
#define MAX_FILE_SIZE 2000

typedef unsigned char BYTE;
enum colors {blue, green, red};

typedef struct{BYTE blue ; BYTE green; BYTE red;} PIXEL;

int main()
{
char type[2];
int size;
int res;
int off;
int ssz;
int w;
int h;
int end[7];
FILE * fin = fopen("1.bmp", "r");
perror("Open file");

fread(&type, 2, 1, fin);
fread(&size, 4, 1, fin);
fread(&res, 4, 1, fin);
fread(&off, 4, 1, fin);
fread(&ssz, 4, 1, fin);
fread(&w, 4, 1, fin);
fread(&h, 4, 1, fin);
fread(end, 4, 7, fin);

PIXEL rastr[MAX_FILE_SIZE][MAX_FILE_SIZE];

int padding=(size-off-h*w*3)/h;
BYTE pad[20];   
int i,j;
for(i=0; i<h ; i++)
{
	for(j=0; j<w ; j++)
		fread(&rastr[i][j], 3, 1, fin);
        fread(pad, padding, 1, fin);        
}

fclose(fin);

int min = 0;
int max = 0;
int med = 0;
int medium_row;
int counting = 0;
int first_pixel = 1;
int first_row;
int different_colors = 0;
int figure_h = 0;

for(i=0; i<h ; i++)
{
    for(j=0; j<w-1 ; j++)
    {
        if (rastr[i][j].blue != rastr[i][j+1].blue || rastr[i][j].red != rastr[i][j+1].red || rastr[i][j].green != rastr[i][j+1].green)
            different_colors+=1;
    }
    if (different_colors > 4)
    {
        printf("WARNING: WRONG FIGURE");
        break;
    }

    if (different_colors != 0)
        figure_h += 1;

  	for(j=0; j<w ; j++)
    {
        if (rastr[i][j].blue != 255 || rastr[i][j].red != 255 || rastr[i][j].green != 255)
		counting += 1;
    }
    if (first_pixel == 1)
    {
        max = counting;
        first_pixel = 0;
        first_row = i;
    }
    else
    {
        if (different_colors == 0 || different_colors == 1 || different_colors == 2)
        min = counting;
    }
        counting = 0;
        different_colors = 0;
}
if (figure_h %2 != 0)
    figure_h += 1;
medium_row = first_row + figure_h/2;

int med_first;
int med_last;
first_pixel = 1;

for(j=0; j<w ; j++)
    {
        if (rastr[i][j].blue != 255 || rastr[i][j].red != 255 || rastr[i][j].green != 255)
        {
            if (first_pixel = 1)
                med_first = j;
            else
                med_last = j;
        }
    }
med = med_last - med_first + 1;

int buffer;
if(min > max)
{
    buffer = max;
    max = min;
    min = buffer;
}

if (min == max && med == max)
    printf("SQUARE");
if (min == max && med > max)
    printf("CIRCLE");
if (min != max)
    printf("TRIANGLE");
return (0);
}
