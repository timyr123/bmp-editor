#include "stdio.h"

#include "stdlib.h"

#include "string.h"

#define MAX_FILE_SIZE 2000

typedef unsigned char BYTE;

main()

{

int i, j,z;

char type1[2];

char type2[2];

int size1, size2;

int res1, res2;

int off1, off2;

int ssz1, ssz2;

int w,w1, w2;

int h, h1, h2;

int end1[7];

int end2[7];

int k;

FILE * fin1 = fopen("1.bmp", "r");

perror("Open file");

FILE * fin2 = fopen("2.bmp", "r");

perror("Open file");

FILE * fout = fopen("3.bmp", "w");

perror("Open file");

fread(&type1, 2, 1, fin1);

fread(&size1, 4, 1, fin1);

fread(&res1, 4, 1, fin1);

fread(&off1, 4, 1, fin1);

fread(&ssz1, 4, 1, fin1);

fread(&w1, 4, 1, fin1);

fread(&h1, 4, 1, fin1);

fread(end1, 4, 7, fin1);

printf("yes");

fread(&type2, 2, 1, fin2);

fread(&size2, 4, 1, fin2);

fread(&res2, 4, 1, fin2);

fread(&off2, 4, 1, fin2);

fread(&ssz2, 4, 1, fin2);

fread(&w2, 4, 1, fin2);

fread(&h2, 4, 1, fin2);

fread(end2, 4, 7, fin2);

//BYTE rastr1[MAX_FILE_SIZE][MAX_FILE_SIZE][3];

BYTE ***rastr1=(BYTE***)malloc(w1*sizeof(BYTE**));

for(i=0;i<w1;i++)

{

rastr1[i]=(BYTE**)malloc(h1*sizeof(BYTE*));

for(j=0;j<h1;j++)

rastr1[i][j] = (BYTE*)malloc(3*sizeof(BYTE));

}

int padding1 = (size1 - off1 - w1*h1 * 3) / w1;

BYTE pad1[20];

for (i = 0; i<w1; i++)

{

for (j = 0; j<h1; j++)

fread(rastr1[i][j], 3, 1, fin1);

fread(pad1, padding1, 1, fin1);

}

//BYTE rastr2[MAX_FILE_SIZE][MAX_FILE_SIZE][3];

BYTE ***rastr2=(BYTE***)malloc(w2*sizeof(BYTE**));

for(i=0;i<w2;i++)

{

rastr2[i]=(BYTE**)malloc(h2*sizeof(BYTE*));

for(j=0;j<h2;j++)

rastr2[i][j] = (BYTE*)malloc(3*sizeof(BYTE));

}

int padding2 = (size2 - off2 - w2*h2 * 3) / w2;

BYTE pad2[20];

for (i = 0; i < w2; i++)

{

for (j = 0; j < h2; j++)

fread(rastr2[i][j], 3, 1, fin2);

fread(pad2, padding2, 1, fin2);

}

h = h1 + h2;

//char rastr[MAX_FILE_SIZE][MAX_FILE_SIZE][3];

BYTE ***rastr=(BYTE***)malloc(w1*sizeof(BYTE**));

for(i=0;i<w1;i++)

{

rastr[i]=(BYTE**)malloc(h*sizeof(BYTE*));

for(j=0;j<h;j++)

rastr[i][j] = (BYTE*)malloc(3*sizeof(BYTE));

}

printf("1)Soedenit snizy 1->2");

printf("2)Soedenit sverhy 2->1");

scanf("%d",&k);

if (k == 1)

for (i = 0; i < w1; i++)

{

for (j = 0; j < h1; j++)

for (z=0; z<3; z++)

rastr[i][j][z] = rastr1[i][j][z];

for (j = h1 ; j < h; j++)

for (z=0; z<3; z++)

rastr[i][j][z] = rastr2[i][j-h1][z];

}

else

for (i = 0; i < w1; i++)

{

for (j = 0; j < h / 2; j++)

for (z=0; z<3; z++)

rastr[i][j][z] = rastr2[i][j][z];

for (j = h/2; j < h; j++)

for (z=0; z<3; z++)

rastr[i][j][z] = rastr1[i][j-h/2][z];

}

fwrite(&type1, 2, 1, fout);

fwrite(&size1, 4, 1, fout);

fwrite(&res1, 4, 1, fout);

fwrite(&off1, 4, 1, fout);

fwrite(&ssz1, 4, 1, fout);

fwrite(&w, 4, 1, fout);

fwrite(&h1, 4, 1, fout);

fwrite(end1, 4, 7, fout);

for (i = 0; i<w1; i++)

{

for (j = 0; j<h; j++)

fwrite(rastr[i][j], 3, 1, fout);

fwrite(pad1, padding1, 1, fout);

}

return 0;

}
