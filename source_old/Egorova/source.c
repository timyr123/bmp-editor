#include <stdio.h>
#include <stdlib.h>

typedef unsigned char BYTE;
enum colors {blue, green, red};
typedef struct{BYTE blue ; BYTE green; BYTE red;} PIXEL;

int main()
{
	int x1, x2, y1, y2;

	printf("Enter x1	");
	scanf("%d", &x1);
	printf("Enter x2	");
	scanf("%d", &x2);
	printf("Enter y1	");
	scanf("%d", &y1);
	printf("Enter y2	");
	scanf("%d", &y2);

	x1 = x1 - 1;
	x2 = x2 + 1;
	y1 = y1 - 1;
	y2 = y2 + 1;
   
	int i, j, chet, size, res, off, ssz, w, h, h1, h2;
	char type[2];  
	int end[7]; 
	chet = 0;


	FILE * fr = fopen("infile.bmp", "r");
	perror("Open file input");

	fread(&type, 2, 1, fr);
	fread(&size, 4, 1, fr);
	fread(&res, 4, 1, fr);
	fread(&off, 4, 1, fr);
	fread(&ssz, 4, 1, fr);
	fread(&w, 4, 1, fr);
	fread(&h, 4, 1, fr);
	fread(end, 4, 7, fr);

	PIXEL rastr1[500][500];

	int padding1=(size-off-h*w*3)/h;
	BYTE pad1[20];   

	for(i=0; i<h ; i++){
		for(j=0; j<w ; j++){
			if (((i>x1)&&(i<x2))&&((j<y2)&&(j>y1))){
				fread(&rastr1[i][j], 3, 1, fr);
				h1=h1+1;
      				fread(pad1, padding1, 1, fr);  
			} 
   		}
	h2=h2+1;
	}


	w = h1;
	h = h2;


	FILE * fw = fopen("outfile.bmp", "w");
   	perror("Open file output");

	fwrite(&type, 2, 1, fw);
	fwrite(&size, 4, 1, fw);
	fwrite(&res, 4, 1, fw);
	fwrite(&off, 4, 1, fw);
	fwrite(&ssz, 4, 1, fw);
	fwrite(&w, 4, 1, fw);
	fwrite(&h, 4, 1, fw);
	fwrite(end, 4, 7, fw);

	for ( i = 0 ; i < h ; i++ ){
		for ( j = 0 ; j < w ; j++ ){
			fwrite( &rastr1[i][j] , 1 , 3 , fw );
			fwrite(pad1, padding1, 1, fw);  
		}
	}

	return 0;
}
