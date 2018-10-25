#include "stdio.h"
#include "string.h"
#define MAX_FILE_SIZE 1000
typedef unsigned char BYTE;
enum colors {blue, green, red};
typedef struct{BYTE blue ; BYTE green; BYTE red;} PIXEL;
main()
{
//Obyvlenie peremennux dly okrutiy izobrasheniy
    char type[2];  
    int size;
    int res;
    int off;
    int ssz;
    int w;
    int h;
    int end[7];


// Otkrutie 3x izobrasheniy. 1 dly chteniy. 2 dly zapisi
    FILE * fin = fopen("1.bmp", "r");
    perror("Open file");
    FILE * fout = fopen("2.bmp", "w");
    perror("Open file");
    FILE * fout2 = fopen("3.bmp", "w");
    perror("Open file");


//Chtenie informacii iz isxodnogo izobrashenia
    fread(&type, 2, 1, fin);
    fread(&size, 4, 1, fin);
    fread(&res, 4, 1, fin);
    fread(&off, 4, 1, fin);
    fread(&ssz, 4, 1, fin);
    fread(&w, 4, 1, fin);
    fread(&h, 4, 1, fin);
    fread(end, 4, 7, fin);
//Sozdanie Dvumernogo massiva   
PIXEL rastr[MAX_FILE_SIZE][MAX_FILE_SIZE];
//Lishnie pixeli
int padding=(size-off-h*w*3)/h;
//massiv dly lishnix pixleley
BYTE pad[20];   
//Schituvaem pixeli s isxodnogo isobrashenia
int i,j;
for(i=0; i<h ; i++)
{
	for(j=0; j<w ; j++)
		fread(&rastr[i][j], 3, 1, fin);
        fread(pad, padding, 1, fin);        
}	
//Zapisuvaem informaciu v 1oe konechnoe izobrashenie

    fwrite(&type, 2, 1, fout);
    fwrite(&size, 4, 1, fout);
    fwrite(&res, 4, 1, fout);
    fwrite(&off, 4, 1, fout);
    fwrite(&ssz, 4, 1, fout);
    fwrite(&w, 4, 1, fout);
    fwrite(&h, 4, 1, fout);
    fwrite(end, 4, 7, fout);

//Zapisuvaem informaciu v 2oe konechnoe izobrashenie

fwrite(&type, 2, 1, fout2);
    fwrite(&size, 4, 1, fout2);
    fwrite(&res, 4, 1, fout2);
    fwrite(&off, 4, 1, fout2);
    fwrite(&ssz, 4, 1, fout2);
    fwrite(&w, 4, 1, fout2);
    fwrite(&h, 4, 1, fout2);
    fwrite(end, 4, 7, fout2);
//Peremennue dly kashogo cveta pervogo pixely isxodnogo izobrahenia
int cvet1=rastr[0][0].blue;
int cvet2=rastr[0][0].green;
int cvet3=rastr[0][0].red;

//change1
//Proveryem kashduy cvet picley isxodnogo isobrashenia s ego posled cvetami. Esli on ne raven pervomu, to zapisuvae, ego v 1 konechnoe izobrasenie. Esli raven, to buden chernuy cvet. I zapisuvaem ego v konechnoe.
for(i=0;i<h;i++)
{
for(j=0;j<w;j++){
if(rastr[i][j].blue!=cvet1 && rastr[i][j].green!=cvet2 && rastr[i][j].red!=cvet3)
{
fwrite(&rastr[i][j],3,1,fout);
fwrite(pad,padding,1,fout);}
else
{rastr[i][j].blue=0; rastr[i][j].green=0; rastr[i][j].red=0;
fwrite(&rastr[i][j],3,1,fout);
fwrite(pad,padding,1,fout);
rastr[i][j].blue=cvet1; rastr[i][j].green=cvet2; rastr[i][j].red=cvet3;
}}}

//change2
//Zdec proveryem na drugoy cvet. Analogichno change1/
for(i=0;i<h;i++)
{
for(j=0;j<w;j++){
if(rastr[i][j].blue==cvet1 && rastr[i][j].green==cvet2 && rastr[i][j].red==cvet3)
{
fwrite(&rastr[i][j],3,1,fout2);
fwrite(pad,padding,1,fout2);}
else
{rastr[i][j].blue=0; rastr[i][j].green=0; rastr[i][j].red=0;
fwrite(&rastr[i][j],3,1,fout2);
fwrite(pad,padding,1,fout2);
rastr[i][j].blue=cvet1; rastr[i][j].green=cvet2; rastr[i][j].red=cvet3;}}}
return 0; 
}
