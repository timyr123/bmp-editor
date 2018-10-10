#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char BYTE;

int main()
{
	struct bmp
	{
		char type[2];
		int size,reserved,head_end,header_size,weight,height;
		int end[7];
	};

	struct bmp image[10];
	FILE * file_input[10];
	int i,j,z,number,captchasize;
	char file_name[6];
	char captcha[30];

	file_name[5]='\0';

	printf("Enter the captcha:");
	scanf("%s",captcha);
	captchasize=strlen(captcha);
	for(i=0;i<captchasize;i++)
	{
		file_name[0]=captcha[i];
		strcat(file_name,".bmp");
		file_input[i] = fopen(file_name,"r");
		perror("Input file");
		fread(&image[i].type, 2, 1, file_input[i]);
		fread(&image[i].size, 4, 1, file_input[i]);
		fread(&image[i].reserved, 4, 1, file_input[i]);
		fread(&image[i].head_end, 4, 1, file_input[i]);
		fread(&image[i].header_size, 4, 1, file_input[i]);
		fread(&image[i].weight, 4, 1, file_input[i]);
		fread(&image[i].height, 4, 1, file_input[i]);
		fread(image[i].end, 4, 7, file_input[i]);
		memset(file_name,0,sizeof(file_name));
	}

	int (*padding)=malloc(sizeof(int)*captchasize);
	BYTE pad_array[captchasize][20];
	BYTE ***rastr_captcha=(BYTE***)malloc(image[0].height*sizeof(BYTE**));

	for(i=0;i<image[0].height;i++)
	{
		rastr_captcha[i]=(BYTE**)malloc((image[0].weight*captchasize)*sizeof(BYTE*));
		for(j=0;j<image[0].weight*captchasize;j++)
		{
			rastr_captcha[i][j]=(BYTE*)malloc(3*sizeof(BYTE));
		}
	}

	int weight_captcha=0;

	for(number=0;number<captchasize;number++)
	{
		BYTE ***rastr=(BYTE***)malloc(image[0].height*sizeof(BYTE**));
		for(i=0;i<image[0].height;i++)
		{
			rastr[i]=(BYTE**)malloc(image[0].weight*sizeof(BYTE*));
			for(z=j;j<image[0].weight;j++)
			{
				rastr[i][j]=(BYTE*)malloc(3*sizeof(BYTE));
			}
		}
		padding[number] = (image[0].size - image[0].head_end - image[0].height*image[number].weight * 3) / image[number].height;
		for(i=0;i<image[0].height;i++)
		{
			for(j=0;j<image[number].weight;j++)
			{
				fread(rastr[i][j], 3, 1, file_input[number]);
			}
		fread(pad_array, padding[number], 1, file_input[number]);
		}

		for(i=0;i<image[0].height;i++)
		{
			for(j=weight_captcha;j<(image[0].weight+image[0].weight*number);j++)
			{
			for(z=0;z<3;z++)
				{
					rastr_captcha[i][j][z] = rastr[i][j-image[0].weight*number][z];
				}
			}
		}
		weight_captcha+=image[0].weight;
		for(i=0;i<image[0].height;i++)
		{
			for(j=0;j<image[0].weight;j++)
			{
				free(rastr[i][j]);
			}
			free(rastr[j]);
		}
		free(rastr);
	}

	FILE * file_output = fopen("captcha.bmp","w");
	fwrite(&image[0].type, 2, 1, file_output);
	fwrite(&image[0].size, 4, 1, file_output);
	fwrite(&image[0].reserved, 4, 1, file_output);
	fwrite(&image[0].head_end, 4, 1, file_output);
	fwrite(&image[0].header_size, 4, 1, file_output);
	fwrite(&weight_captcha, 4, 1, file_output);
	fwrite(&image[0].height, 4, 1, file_output);
	fwrite(image[0].end, 4, 7, file_output);
	for(i=0;i<image[0].height; i++)
	{
		for (j=0;j<image[0].weight*captchasize; j++)
		fwrite(rastr_captcha[i][j], 3, 1, file_output);
		fwrite(pad_array[0], padding[0], 1, file_output);
	}
	free(padding);
	fclose(file_output);
	return 0;
}
