#include <stdio.h>

#include <stdlib.h>

#include <windows.h>

typedefstruct

{

unsigned char b;

unsigned char g;

unsigned char r;

} PIXEL;

PIXEL rastr[1000][1000]; // Присваиваниекаждомуэлементумассива "rastr" структуры PIXEL

BITMAPFILEHEADER h1;

BITMAPINFOHEADER h2;

intsz;

const char *infile = "1.bmp";

const char *outfile1 = "2.bmp";

const char *outfile2 = "3.bmp";

FILE *fr , *fw ;

intsz_padding; ; // инициализация переменной для значения размера "набивки"

char padding;

intread_file()

{

inti,j;

fr = fopen(infile , "r");// Чтение и запись открываемого файла в переменную fr

perror("openinfile");// Проверка открылся файл или нет

fread(&h1 , sizeof(h1) , 1 , fr); // Потоковое чтение и запись структуры BITMAPFILEHEADER открываемого файла в переменную h1

fread(&h2 , sizeof(h2) , 1 , fr); // Потоковое чтение и запись структуры BITMAPINFOHEADER открываемого файла в переменную h2

sz_padding = (h2.biSizeImage - h2.biHeight * h2.biWidth * 3)/h2.biHeight;// Из полного размера изображения вычитаем полезную информацию и делим результат на количество строк. Получаем сколько бесполезной информации в каждой строке.

for( i = 0 ; i < h2.biHeight ; i++ )

{

for ( j = 0 ; j < h2.biWidth ; j++ )

fread( &rastr[i][j] , 1 , 3 , fr );//Записьпикселей

fread(&padding , 1 , sz_padding , fr );

}

return 0;

}

intchange_head()

{

h2.biWidth=h2.biWidth/2; ; //Уменьшение ширины в два раза

return 0;

}

int write_file1()

{

inti,j;

fw = fopen(outfile1 , "w");

perror("open outfile1");

fwrite(&h1 , sizeof(h1) , 1 , fw);

fwrite(&h2 , sizeof(h2) , 1 , fw);

for ( i = 0 ; i < h2.biHeight ; i++ )

{

for ( j = 0 ; j < h2.biWidth ; j++ )

fwrite(&rastr[i][j] , 1 , 3 , fw );

fwrite(&padding , 1 , sz_padding , fw );

}

return 0;

}

int write_file2()

{

inti,j;

fw = fopen(outfile2 , "w");

perror("open outfile2");

fwrite(&h1 , sizeof(h1) , 1 , fw);

fwrite(&h2 , sizeof(h2) , 1 , fw);

for ( i = 0 ; i < h2.biHeight ; i++ )

{

for ( j = h2.biWidth ; j < h2.biWidth*2 ; j++ )

fwrite(&rastr[i][j] , 1 , 3 , fw );

fwrite(&padding , 1 , sz_padding , fw );

}

return 0;

}

int main()

{

read_file();

change_head();

write_file1();

write_file2();

return 0;

}
