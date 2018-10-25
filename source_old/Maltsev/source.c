#include "stdio.h"
#include "string.h"
#define MAX_FILE_SIZE 1000
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
	
    FILE * fin = fopen("4.bmp", "r");
    perror("Open file");

    FILE * fout = fopen("5.bmp", "w");
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
// CHANGE PICTURE
	int lin;
	printf ("vvedite kol-vo liniy:");
	scanf("%d",&lin);
	int lw=w/(lin*2);
	int s=lw;
	int lh=h/(lin*2);
	int u=lh;
	int H=1;
//Vertikal'naya.
	for(i=0; i<h ; i++)
{
	
		if(rastr[H]==rastr[i])
{
			lw=s;
			H+=1;
}			
		for(j=0; j<w ; j++)
{
			if(rastr[lw+s]==rastr[j])
{				lw+=(2*s);
}		
			if (rastr[lw]>rastr[j])
		
{				rastr[i][j].green = 0;
				rastr[i][j].red = 0;
				rastr[i][j].blue = 0;
}
}
}
//Gorizontal'naya.    
	for(i=0; i<h ; i++)
{
		for(j=0; j<w ; j++)
{
			if(rastr[lh+u]==rastr[i])
{
				lh+=(2*u);
}		
			if (rastr[lh]>rastr[i])		
{
				rastr[i][j].green = 0;
				rastr[i][j].red = 0;
				rastr[i][j].blue = 0;
}
}
}    
//zapis'
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
	return 0; 
}
