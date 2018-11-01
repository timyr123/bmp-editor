#include "stdio.h"
#include "string.h"

file *openFile (char *fileName, char *openAction)
	/*
	Функция принимает строку, содержащую имя файла и 
	строку наименования действия, производимого над файлом
	(чтение("r")/запись("w"));
	
	Создает указатель на файл;
	Открывает файл;
	Возвращает указатель на файл;
	*/

openFile (char *fileName, char *openAction)
	{
	FILE * inputFile = fopen(fileName, openAction);
	return inputFile;
	}

readDescription(file *inputFile)
	/*
	Функция принимает указатель на файл и schitivayet
	данные о графическом файле v strukturu, kotoraya
	doljna soderjat' eti danniye s opisaniem
	*/
	{
	fread(&structDescription.type, 2, 1, inputFile);
	fread(&structDescription.size, 4, 1, inputFile);
	fread(&structDescription.res, 4, 1, inputFile);
	fread(&structDescription.off, 4, 1, inputFile);
	fread(&structDescription.ssz, 4, 1, inputFile);
	fread(&structDescription.w, 4, 1, inputFile);
	fread(&structDescription.h, 4, 1, inputFile);
	fread(structDescription.end, 4, 7, inputFile);
	return structDescription;
	}

int findPadding()
	/*
	Функция вычисляет пустой отступ в конце строки пикселей
	*/
	{
	int padding=(size-off-h*w*3)/h; 
	return padding;
	}
    
readPixels(file *inputFile, struct PIXEL ** rastr, struct bmp structDescription, int padding)
	/*
	Функция принимает указатель на файл и переписывает
	данные пикселей в массив struktur
	*/
	{
	int i,j;
	BYTE pad[20]
	for(i=0; i<structDescription.h ; i++)
	{
		for(j=0; j<structDescription.w ; j++)
			fread(&rastr[i][j], 3, 1, inputFile);
			fread(pad, padding, 1, inputFile);        
	}
	}

int inverse(struct PIXEL ** rastr, struct bmp structDescription)
	/*
	Prinimayet ukazatel na massiv
	Funkciya invertiruet znacheniya cvetov pikseley:
	
	*/
	{	
	for(i=0; i<structDescription.h ; i++)
		for(j=0; j<structDescription.w ; j++)
	{
			rastr[i][j].green = 255 - rastr[i][j].green;
			rastr[i][j].red = 255 - rastr[i][j].red;
			rastr[i][j].blue = 255 - rastr[i][j].blue;
	}
	}

writeFile (struct PIXEL ** rastr, struct bmp structDescription, FILE *outputFile)
	/*
	Funkciya zapisyvayet danniye massiva v vihodnoi file
	*/
	{
	fwrite(&structDescription.type, 2, 1, outputFile);
	fwrite(&structDescription.size, 4, 1, outputFile);
	fwrite(&structDescription.res, 4, 1, outputFile);
	fwrite(&structDescription.off, 4, 1, outputFile);
	fwrite(&structDescription.ssz, 4, 1, outputFile);
	fwrite(&structDescription.w, 4, 1, outputFile);
	fwrite(&structDescription.h, 4, 1, outputFile);
	fwrite(structDescription.end, 4, 7, outputFile);
	for(i=0; i<structDescription.h ; i++)
	{
		for(j=0; j<structDescription.w ; j++)
			fwrite(&rastr[i][j], 3, 1, outputFile);
		fwrite(pad, padding, 1, outputFile);        
	}
	}	
