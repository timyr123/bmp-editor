#include "stdio.h" 
#include "stdlib.h" 
#include "string.h" 
typedef unsigned char BYTE; 
main() 
{ 
int i, j,z; 
char type1[2], type2[2]; 
int size1, size2; 
int res1, res2; 
int off1, off2; 
int ssz1, ssz2; 
int w,w1, w2; 
int h1, h2; 
int end1[7], end2[7]; 
int k; 
FILE * fin1 = fopen("1.bmp", "r"); //Открытие файла картинки на чтение
perror("Open file"); 
FILE * fin2 = fopen("2.bmp", "r"); //Открытие файла картинки на чтение
perror("Open file"); 
FILE * fout = fopen("3.bmp", "w"); //Открытие файла картинки на изменение
perror("Open file"); 
//Чтение файла картинки
fread(&type1, 2, 1, fin1); 
fread(&size1, 4, 1, fin1); 
fread(&res1, 4, 1, fin1); 
fread(&off1, 4, 1, fin1); 
fread(&ssz1, 4, 1, fin1); 
fread(&w1, 4, 1, fin1); 
fread(&h1, 4, 1, fin1); 
fread(end1, 4, 7, fin1); 
//Закрытие файла картинки 
fclose(fin1); 
//Чтение файла картинки
fread(&type2, 2, 1, fin2); 
fread(&size2, 4, 1, fin2); 
fread(&res2, 4, 1, fin2); 
fread(&off2, 4, 1, fin2); 
fread(&ssz2, 4, 1, fin2); 
fread(&w2, 4, 1, fin2); 
fread(&h2, 4, 1, fin2); 
fread(end2, 4, 7, fin2); 
//Закрытие файла картинки 
fclose(fin2); 
//Создание динамического трёхмерного массива с пикселями
BYTE ***rastr1=(BYTE***)malloc(h1*sizeof(BYTE**)); 
for(i=0;i<h1;i++) 
{ 
rastr1[i]=(BYTE**)malloc(w1*sizeof(BYTE*)); 
for(j=0;j<w1;j++) 
rastr1[i][j] = (BYTE*)malloc(3*sizeof(BYTE)); 
} 
int padding1 = (size1 - off1 - h1*w1 * 3) / h1; 
BYTE pad1[20]; 
for (i = 0; i<h1; i++) 
{ 
for (j = 0; j<w1; j++) 
fread(rastr1[i][j], 3, 1, fin1); 
fread(pad1, padding1, 1, fin1); 
} 
//Создание динамического трёхмерного массива с пикселями
BYTE ***rastr2=(BYTE***)malloc(h2*sizeof(BYTE**)); 
for(i=0;i<h2;i++) 
{ 
rastr2[i]=(BYTE**)malloc(w2*sizeof(BYTE*)); 
for(j=0;j<w2;j++) 
rastr2[i][j] = (BYTE*)malloc(3*sizeof(BYTE)); 
} 
int padding2 = (size2 - off2 - h2*w2 * 3) / h2; 
BYTE pad2[20]; 
for (i = 0; i < h2; i++) 
{ 
for (j = 0; j < w2; j++) 
fread(rastr2[i][j], 3, 1, fin2); 
fread(pad2, padding2, 1, fin2); 
} 
w = w1 + w2; 
//Создание динамического трёхмерного массива с пикселями
BYTE ***rastr=(BYTE***)malloc(h1*sizeof(BYTE**)); 
for(i=0;i<h1;i++) 
{ 
rastr[i]=(BYTE**)malloc(w*sizeof(BYTE*)); 
for(j=0;j<w;j++) 
rastr[i][j] = (BYTE*)malloc(3*sizeof(BYTE)); 
} 
printf("1)Соеденить справа 1->2"); 
printf("2)Соеденить слева 2->1"); 
scanf("%d",&k); 
if (k == 1) 
//Соединение картинок справа
for (i = 0; i < h1; i++) 
{ 
for (j = 0; j < w1; j++) 
for (z=0; z<3; z++) 
rastr[i][j][z] = rastr1[i][j][z]; 
for (j = w1 ; j < w; j++) 
for (z=0; z<3; z++) 
rastr[i][j][z] = rastr2[i][j-w1][z]; 
} 
else 
//Соединение картинок слева
for (i = 0; i < h1; i++) 
{ 
for (j = 0; j < w / 2; j++) 
for (z=0; z<3; z++) 
rastr[i][j][z] = rastr2[i][j][z]; 
for (j = w/2; j < w; j++) 
for (z=0; z<3; z++) 
rastr[i][j][z] = rastr1[i][j-w/2][z]; 
} 
//Запись в файл получившейся картинки
fwrite(&type1, 2, 1, fout); 
fwrite(&size1, 4, 1, fout); 
fwrite(&res1, 4, 1, fout); 
fwrite(&off1, 4, 1, fout); 
fwrite(&ssz1, 4, 1, fout); 
fwrite(&w, 4, 1, fout); 
fwrite(&h1, 4, 1, fout); 
fwrite(end1, 4, 7, fout); 
for (i = 0; i<h1; i++) 
{ 
for (j = 0; j<w; j++) 
fwrite(rastr[i][j], 3, 1, fout); 
fwrite(pad1, padding1, 1, fout); 
}
//Закрытие файла картинки  
fclose(fout); 
//Освобождение памяти динамического массива
for(i=0;i<h1;i++)
		{
			for(j=0;j<w1;j++)
			{
				free(rastr[i][j]);
			}
			free(rastr[j]);
		}
//Освобождение памяти динамического массива
for(i=0;i<h2;i++)
		{
			for(j=0;j<w2;j++)
			{
				free(rastr[i][j]);
			}
			free(rastr[j]);
		}
//Освобождение памяти динамического массива
for(i=0;i<h1;i++)
		{
			for(j=0;j<w;j++)
			{
				free(rastr[i][j]);
			}
			free(rastr[j]);
		}
return 0
}
