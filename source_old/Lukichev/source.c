#include "stdio.h" 
#include "string.h" 
#define MAX_FILE_SIZE 1000
typedef unsigned char BYTE;
enum colors {blue, green, red}; 
typedef struct{BYTE blue ;
BYTE green; BYTE red;} 
PIXEL;
int main() 
{ 
printf("%d %d %d\n", blue , green, red);
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
FILE * fout = fopen("2.bmp", "w"); 
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
fread(pad, padding, 1, fin); }
for(i=0; i<h ; i++) 
for(j=0; j<w ; j++)

{
rastr[i][j].green = 255 - rastr[i][j].green;
rastr[i][j].red = 255 - rastr[i][j].red;
rastr[i][j].blue = 255 - rastr[i][j].blue; 
} 
fwrite(&type, 2, 1, fout);
fwrite(&size, 4, 1, fout);
fwrite(&res, 4, 1, fout); 
fwrite(&off, 4, 1, fout);
fwrite(&ssz, 4, 1, fout);
fwrite(&w, 4, 1, fout); 
fwrite(&h, 4, 1, fout); 
fwrite(end, 4, 7, fout);
for(i=0; i<h ; i++) 
{
for(j=0; j<w ; j++)
fwrite(&rastr[i][j], 3, 1, fout);
fwrite(pad, padding, 1, fout); 
} 
return (0);
}
